#include <Windows.h>
#include <stdio.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "DBUtil.h"
#include "DiscordRest.h"

#include "DiscordHandler.h"


// Static Defines
static DiscordGateway* gateway = nullptr;

static void HandleError(const WsClientLib::WSError& err, void* pUserData) {
	// Will also be thrown when closed, so...
	DBG_printf("[DiscordGateway] Websockets Error: %s [%d]\n", err.message.c_str(), err.code);
	MessageBoxA(NULL, "DiscordBuddy Error: Websocket Error - Likely Invalid Discord Token", "DiscordBuddy", MB_ICONERROR | MB_OK);
	exit(-1);
}

static void HandleReceivedMessage(const std::string& message, void* pUserData) {
	if (message.empty()) { return; }

	cJSON* msg = cJSON_Parse(message.c_str());
	if (cJSON_GetObjectItemCaseSensitive(msg, "op")) {
		int op = cJSON_GetObjectItemCaseSensitive(msg, "op")->valueint;
		switch (op) {
		case OP_DISPATCH:
			gateway->ProcessDispatchPacket(msg);
			break;
		case OP_HEARTBEAT:
			gateway->SendHeartbeat();
			break;
		case OP_RECONNECT:
			gateway->ProcessReconnectPacket(msg);
			break;
		case OP_INVALID:
			gateway->ProcessInvalidSessionPacket(msg);
			break;
		case OP_HELLO:
			//printf("Got Hello Message\n");
			gateway->ProcessHelloPacket(msg);
			// We'll also Send an Identify Packet at this Point.
			//printf("[DiscordGateway] Sending Identify Packet\n");
			gateway->SendIdentify();

			break;
		case OP_HEARTBEAT_ACK:
			//printf("Heartbeat ACK\n");
			break;
		default:
			DBG_printf("Unhandled Message Operation: %d\n", op);
		}
	}

	if (msg) {
		//cJSON_Delete(msg);
	}

}

// Periodically Sends a Heartbeat at the Discretion of the Server
static void HeartBeatThread() {
	while (!gateway) {}
	while (gateway->IsRunning()) {
		while (!gateway->GetHeartbeat()) {}
		Sleep(gateway->GetHeartbeat());
		gateway->SendHeartbeat();
	}
}

// Master Thread - Processes Recieved Packets and Keeps a Sending Channel Open
static void GatewayThread() {
	while (!gateway) {}
	while (gateway->IsRunning()) {
		gateway->Connect();
		while (gateway->GetState() != WsClientLib::WebSocket::readyStateValues::CLOSED) {
			if (!gateway->IsRunning()) { return; }
			gateway->Transact(HandleError, HandleReceivedMessage);
		}
		MessageBoxA(NULL, "DiscordBuddy Error: Probably Invalid Discord Token", "RPC Gateway Closed Due to an Error", MB_ICONERROR | MB_OK);
		exit(-1);
		Sleep(1000);
	}
}


DiscordHandler::DiscordHandler() {
	memset(&this->_user, 0, sizeof(struct DiscordUser));
	memset(&this->_activity, 0, sizeof(struct DiscordActivity));
	this->_bypass = 1;
	this->_running = 1;
	this->_backend = -1;

}

DiscordHandler::~DiscordHandler() {
	CurlShutdown();
	this->ClearActivity();
	this->_running = 0;
	if (gateway) {
		delete gateway;
	}
}

void DiscordHandler::PrintCurrentUser() {
	DBG_printf("-------------------------------");
	DBG_printf("[DiscordHandler] Current User");
	DBG_printf("[%llu] %s#%s (Bot: %d) (Avatar: %s)", this->_user.id, this->_user.username, this->_user.discriminator, this->_user.bot, this->_user.avatar);
	DBG_printf("-------------------------------");
}

void DiscordHandler::PrintCurrentActivity() {
	DBG_printf("-------------------------------");
	DBG_printf("[DiscordHandler] Current Activity");
	DBG_printf("AppId: %llu", this->_activity.application_id);
	DBG_printf("Name: %s", this->_activity.name);
	DBG_printf("Details: %s", this->_activity.details);
	DBG_printf("State: %s", this->_activity.state);
	DBG_printf("Assets: Large Image %s Large Text %s Small Image %s Small Text %s", this->_activity.assets.large_image, this->_activity.assets.large_text, this->_activity.assets.small_image, this->_activity.assets.small_text);
	DBG_printf("-------------------------------");
}

void DiscordHandler::SetApplicationId(unsigned long long application_id) {
	this->_application_id = application_id;
	this->_activity.application_id = application_id;
}

void DiscordHandler::SetApplicationName(const char* application_name) {
	strcpy_s(this->_activity.name, sizeof(this->_activity.name), application_name);
	strcpy_s(this->_application_name, sizeof(this->_application_name), application_name);
}

void DiscordHandler::GetAppToken(char* app_token) {
	;
	GetAppIDToken(this->_application_id, this->_token, app_token);
}

void DiscordHandler::SetUser(struct DiscordUser* user) {
	memcpy(&this->_user, user, sizeof(struct DiscordUser));
}

void DiscordHandler::GetCurrentUser(struct DiscordUser* user) {
	memcpy(user, &this->_user, sizeof(struct DiscordUser));
	this->PrintCurrentUser();
}

int DiscordHandler::InitCurrentUser() {
	cJSON* info_response;
	this->_user.bot = 0;
	char url_user_info[128] = { 0x00 };
	GetURLUserInfo(url_user_info);
	if (!GetUserInfo(url_user_info, this->_token, &info_response)) { return 0; }
	this->_user.id = (unsigned long long)atoll(cJSON_GetObjectItemCaseSensitive(info_response, "id")->valuestring);
	strcpy_s(this->_user.username, sizeof(this->_user.username), cJSON_GetObjectItemCaseSensitive(info_response, "username")->valuestring);
	strcpy_s(this->_user.avatar, sizeof(this->_user.avatar), cJSON_GetObjectItemCaseSensitive(info_response, "avatar")->valuestring);
	strcpy_s(this->_user.discriminator, sizeof(this->_user.discriminator), cJSON_GetObjectItemCaseSensitive(info_response, "discriminator")->valuestring);
	if (cJSON_GetObjectItemCaseSensitive(info_response, "bot")) {
		this->_user.bot = cJSON_GetObjectItemCaseSensitive(info_response, "bot")->valueint;
	}
	return 1;
}

void DiscordHandler::SetApplicationInfo(unsigned long long client_id) {
	this->SetApplicationId(client_id);

	// For the Real Deal, We Need More Stuff
	cJSON* asset_response;
	char url_asset_info[128] = { 0x00 };
	char url_app_info[128] = { 0x00 };

	GetURLAssetInfo(url_asset_info, this->_application_id);
	GetURLAppInfo(url_app_info, this->_application_id);

	GetAppAssets(url_asset_info, this->_application_id, this->_token, &asset_response);
	this->_assets = asset_response;
	cJSON* app_info_response;
	GetAppInfo(url_app_info, this->_application_id, this->_token, &app_info_response);
	this->SetApplicationName(cJSON_GetObjectItemCaseSensitive(app_info_response, "name")->valuestring);
}

void DiscordHandler::PrintApplicationInfo() {
	DBG_printf("-------------------------------");
	DBG_printf("[DiscordHandler] Application: %s (%llu)", this->_application_name, this->_application_id);
	DBG_printf("-------------------------------");
}

void DiscordHandler::SetBypassMode(int mode) {
	this->_bypass = mode;
}

int DiscordHandler::IsBypassMode() {
	return this->_bypass;
}

void DiscordHandler::SetBackend(int backend) {
	this->_backend = backend;
}

int DiscordHandler::GetBackend() {
	return this->_backend;
}


void DiscordHandler::SetToken(const char* token) {
	strcpy_s(this->_token, sizeof(this->_token), token);
}


// Functions for the Fake Backend
void DiscordHandler::Fake_SetActivity(struct DiscordActivity* activity) {
}

void DiscordHandler::Fake_ClearActivity() {
	this->PrintCurrentActivity();
}


void DiscordHandler::ClearActivity() {
	ZeroMemory(&this->_activity, sizeof(DiscordActivity));
	gateway->SendClearActivity();
}

// Maps the asset table to the appropriate id
void DiscordHandler::MapIdToAsset(const char* asset_name, char* asset_id) {
	if (!asset_name) { return; }
	cJSON* jassets = (cJSON*)this->_assets;
	cJSON* asset_item;
	cJSON_ArrayForEach(asset_item, jassets) {
		const char* name = cJSON_GetObjectItemCaseSensitive(asset_item, "name")->valuestring;
		if (!strcmp(name, asset_name)) {
			strcpy(asset_id, cJSON_GetObjectItemCaseSensitive(asset_item, "id")->valuestring);
		}
	}

}

void DiscordHandler::SetActivity(struct DiscordActivity* activity) {
	memcpy(&this->_activity, activity, sizeof(struct DiscordActivity));
	this->_activity.application_id = this->_application_id;
	this->MapIdToAsset(this->_activity.assets.small_text, this->_activity.assets.small_image);
	this->MapIdToAsset(this->_activity.assets.large_text, this->_activity.assets.large_image);
	strcpy_s(this->_activity.name, sizeof(this->_activity.name), this->_application_name);
	this->PrintCurrentActivity();
	gateway->SetActivity(this->_activity.name, this->_activity.state, this->_activity.details, this->_activity.application_id, this->_activity.assets.large_image, this->_activity.assets.large_text);
}




void InitDiscordHandler(DiscordHandler** handler) {

	DiscordHandler* h = new DiscordHandler();
	*handler = h;


	// If bypass is enabled, there's nothing for us to do.
	h->SetBypassMode(!IsBuddyEnabled());
	if (h->IsBypassMode()) { return; }

	// Get our Cached Token - Error and Bypass if not found or invalid.
	char token[128] = { 0x00 };
	GetCachedToken(token);
	if (!strlen(token)) {
		h->SetBypassMode(1);
		OutputDebugStringA("[DiscordBuddy] Discord Token Not Found - Please generate token with utility.");
		return;
	}
	// Set up Our WebSocket Gateway
	char websocket_gateway_url[128] = { 0x00 };
	GetGatewayBaseURL(websocket_gateway_url);
	gateway = new DiscordGateway(websocket_gateway_url, token, &HeartBeatThread, &GatewayThread);
	gateway->Start();
	h->SetToken(token);
	ZeroMemory(token, sizeof(token));
	// Get Real User Data with our Token
	if (!h->InitCurrentUser()) {
		h->SetBypassMode(1);
		OutputDebugStringA("[DiscordBuddy] Discord Token Not Valid - Please generate token with utility.");
		return;
	}
}
