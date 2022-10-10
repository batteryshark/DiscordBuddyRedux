#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <exception>
#include <string>

#include "cJSON.h"
#include "DBUtil.h"
#include "WsClientLib.hpp"

#include "DiscordGateway.h"

static WsClientLib::WebSocket::pointer websocket = nullptr;

DiscordGateway::DiscordGateway(const char* url, const char* token, void* heartbeat_thread_func, void* gateway_thread_func) {
	strcpy_s(this->_token, sizeof(this->_token), token);
	strcpy_s(this->_url, sizeof(this->_url), url);
	websocket = WsClientLib::WebSocket::from_url(this->_url, "");
	this->_heartbeat = 0;
	this->_running = 0;
	memset(this->_session_id, 0x00, sizeof(this->_session_id));
	this->_last_seq = 0;
	this->_heartbeat_thread_func = heartbeat_thread_func;
	this->_gateway_thread_func = gateway_thread_func;
	this->_can_resume = 0;


}

DiscordGateway::~DiscordGateway() {
	this->Stop();
}

int DiscordGateway::Restart() {
	this->Stop();
	this->Start();
	return 1;
}

int DiscordGateway::Start() {
	this->SetRunning(TRUE);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->_gateway_thread_func, NULL, 0, NULL);

	return 1;
}

int DiscordGateway::Stop() {
	DBG_printf("DiscordGateway Stop");
	this->_running = 0;
	this->_heartbeat = 0;
	this->_last_seq = 0;
	return 1;
}

int DiscordGateway::Connect() {
	websocket->connect();
	return 1;
}

int DiscordGateway::GetState() {
	return websocket->getReadyState();
}

int DiscordGateway::IsRunning() {
	return this->_running;
}

void DiscordGateway::SetRunning(int val) {
	this->_running = val;
}

int DiscordGateway::GetHeartbeat() {
	return this->_heartbeat;
}
int DiscordGateway::GetLastSeq() {
	return this->_last_seq;
}
void DiscordGateway::SetHeartbeat(int val) {
	this->_heartbeat = val;
}
void DiscordGateway::SetLastSeq(int val) {
	this->_last_seq = val;
}

void DiscordGateway::SendHeartbeat() {
	cJSON* hbp;
	hbp = CreateHeartbeatPacket();
	this->SendPacket(hbp);
	//cJSON_Delete(hbp);
}

void DiscordGateway::SendIdentify() {

	cJSON* id = CreateIdentifyPacket(this->_token);
	std::string id_packet = cJSON_PrintUnformatted(id);
	if (id_packet.empty()) {
		return;
	}
	websocket->send(id_packet);
	//	cJSON_Delete(id);
}


// 0 Dispatch Receive An event was dispatched.
void DiscordGateway::ProcessDispatchPacket(cJSON* packet) {

	if (cJSON_GetObjectItemCaseSensitive(packet, "s")) {
		this->_last_seq = cJSON_GetObjectItemCaseSensitive(packet, "s")->valueint;
	}

	if (cJSON_GetObjectItemCaseSensitive(packet, "session_id")) {
		strcpy(this->_session_id, cJSON_GetObjectItemCaseSensitive(packet, "session_id")->valuestring);
	}
	if (cJSON_GetObjectItemCaseSensitive(packet, "t")) {
		if (!strcmp(cJSON_GetObjectItemCaseSensitive(packet, "t")->valuestring, "READY")) {
		}
	//	DBG_printf("[GatewayProtocol] Dispatch: %s\n", cJSON_GetObjectItemCaseSensitive(packet, "t")->valuestring);
	}
	//DBG_printf(cJSON_PrintUnformatted(packet));
}

// 7 Reconnect Receive You should attempt to reconnect and resume immediately.
void DiscordGateway::ProcessReconnectPacket(cJSON* packet) {
	cJSON* resume_packet = CreateResumePacket(this->_token, this->_session_id, this->_last_seq);
}

// 9 Invalid Session Receive The session has been invalidated.You should reconnect and identify / resume accordingly.
void DiscordGateway::ProcessInvalidSessionPacket(cJSON* packet) {
	this->_can_resume = cJSON_GetObjectItemCaseSensitive(packet, "d")->valueint;
	this->Restart(); // We'll cheat for now.
}

// 10 Hello Receive Sent immediately after connecting, contains the heartbeat_interval to use.
void DiscordGateway::ProcessHelloPacket(cJSON* packet) {
	cJSON* d = cJSON_GetObjectItemCaseSensitive(packet, "d");
	this->_heartbeat = cJSON_GetObjectItemCaseSensitive(d, "heartbeat_interval")->valueint;
	DBG_printf("[DiscordGateway] Heartbeat Interval Set to: %d\n", this->_heartbeat);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->_heartbeat_thread_func, NULL, 0, NULL);
}

// 11 Heartbeat ACK Receive Sent in response to receiving a heartbeat to acknowledge that it has been received.
void DiscordGateway::ProcessHeartbeatAckPacket(cJSON* packet) {
	DBG_printf("[GatewayProtocol] Heartbeat ACK:\n");
	DBG_printf(cJSON_Print(packet));
}

void DiscordGateway::SendClearActivity() {
	cJSON* clp = CreateClearActivityPacket();
	//DBG_printf(cJSON_PrintUnformatted(clp));
	this->SendPacket(clp);
	//cJSON_Delete(clp);
}

void DiscordGateway::SetActivity(const char* name, const char* state, const char* details, unsigned long long app_id, const char* large_image, const char* large_text) {
	cJSON* sap = CreateActivityPacket(name, state, details, app_id, large_image, large_text);
	//DBG_printf(cJSON_PrintUnformatted(sap));
	this->SendPacket(sap);
	//cJSON_Delete(sap);
}

void DiscordGateway::SendPacket(cJSON* packet) {
	// We'll wait if our websocket isn't currently connected.
	websocket->send(cJSON_PrintUnformatted(packet));

	return;
}

void DiscordGateway::Transact(void* handle_err_func, void* handle_receive_func) {

	websocket->poll(0, (WsClientLib::WebSocket::WSErrorCallback)handle_err_func, nullptr);
	websocket->dispatch((WsClientLib::WebSocket::WSMessageCallback)handle_receive_func, (WsClientLib::WebSocket::WSErrorCallback)handle_err_func, nullptr);
}

// The Rest of the Protocol


// 1 Heartbeat Send/Receive Fired periodically by the client to keep the connection alive.
cJSON* CreateHeartbeatPacket() {
	cJSON* packet = cJSON_CreateObject();
	cJSON_AddNumberToObject(packet, "op", OP_HEARTBEAT);
	cJSON_AddNumberToObject(packet, "d", 2);
	return packet;
}

// 2 Identify Send Starts a new session during the initial handshake.
cJSON* CreateIdentifyPacket(const char* token) {
	cJSON* packet = cJSON_CreateObject();
	cJSON* d = cJSON_CreateObject();
	cJSON* properties = cJSON_CreateObject();
	cJSON_AddStringToObject(properties, "$os", "windows");
	cJSON_AddStringToObject(properties, "$browser", "Discord");
	cJSON_AddStringToObject(properties, "$device", "desktop");
	cJSON_AddItemToObject(d, "properties", properties);
	cJSON_AddStringToObject(d, "token", token);
	cJSON_AddNumberToObject(packet, "op", OP_IDENTIFY);
	cJSON_AddItemToObject(packet, "d", d);
	return packet;
}
// 3 Presence Update Send Update the client's presence.
cJSON* CreateActivityPacket(const char* name, const char* state, const char* details, unsigned long long app_id, const char* large_image, const char* large_text) {
	cJSON* packet = cJSON_CreateObject();

	char app_id_str[32] = { 0x00 };
	sprintf_s(app_id_str, 32, "%llu", app_id);

	cJSON* activity = cJSON_CreateObject();
	cJSON_AddNumberToObject(activity, "type", PLAYING);
	cJSON_AddStringToObject(activity, "name", name);
	cJSON_AddStringToObject(activity, "state", state);
	cJSON_AddStringToObject(activity, "details", details);
	cJSON_AddStringToObject(activity, "application_id", app_id_str);
	cJSON* timestamps = cJSON_CreateObject();
	cJSON_AddNumberToObject(timestamps, "start", (int)time(NULL));
	cJSON_AddItemToObject(activity, "timestamps", timestamps);
	cJSON* assets = cJSON_CreateObject();
	cJSON_AddStringToObject(assets, "large_image", large_image);
	cJSON_AddStringToObject(assets, "large_text", large_text);
	cJSON_AddItemToObject(activity, "assets", assets);

	cJSON* d = cJSON_CreateObject();
	cJSON_AddNumberToObject(d, "since", 999999999);
	cJSON* activities = cJSON_CreateArray();
	cJSON_AddItemToArray(activities, activity);
	cJSON_AddItemToObject(d, "activities", activities);
	cJSON_AddStringToObject(d, "status", "online");
	cJSON_AddBoolToObject(d, "afk", 0);
	cJSON_AddNumberToObject(packet, "op", OP_PRESENCE);
	cJSON_AddItemToObject(packet, "d", d);
	return packet;
}

cJSON* CreateClearActivityPacket() {
	cJSON* packet = cJSON_CreateObject();
	cJSON* activity = cJSON_CreateObject();
	cJSON_AddNumberToObject(activity, "type", PLAYING);
	cJSON_AddNullToObject(activity, "name");
	cJSON_AddNullToObject(activity, "state");
	cJSON_AddNullToObject(activity, "details");
	cJSON* d = cJSON_CreateObject();
	cJSON_AddNumberToObject(d, "since", 999999999);
	cJSON* activities = cJSON_CreateArray();
	cJSON_AddItemToArray(activities, activity);
	cJSON_AddItemToObject(d, "activities", activities);
	cJSON_AddStringToObject(d, "status", "online");
	cJSON_AddBoolToObject(d, "afk", 0);
	cJSON_AddNumberToObject(packet, "op", OP_PRESENCE);
	cJSON_AddItemToObject(packet, "d", d);
	return packet;
}

// 4 Voice State Update	Send Used to join/leave or move between voice channels.
cJSON* CreateUpdateVoiceStatePacket() {
	return nullptr;
}

// 6 Resume Send Resume a previous session that was disconnected.
cJSON* CreateResumePacket(const char* token, const char* session_id, int last_seq) {
	cJSON* packet = cJSON_CreateObject();
	cJSON* d = cJSON_CreateObject();

	cJSON_AddStringToObject(d, "token", token);
	cJSON_AddStringToObject(d, "session_id", session_id);
	cJSON_AddNumberToObject(d, "seq", last_seq);

	cJSON_AddNumberToObject(packet, "op", OP_RESUME);
	cJSON_AddItemToObject(packet, "d", d);

	return packet;
}

// 8 Request Guild Members Send Request information about offline guild members in a large guild.
cJSON* CreateGuildInfoPacket() {
	return nullptr;
}