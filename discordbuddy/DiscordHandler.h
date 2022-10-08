#pragma once
#include "discord_game_sdk.h"
#include "DiscordGateway.h"
class DiscordHandler {
private:
	struct DiscordUser _user;
	struct DiscordActivity _activity;
	DiscordGateway* gateway;
	unsigned long long _application_id;
	char _application_name[128];
	char _token[128];
	void* _assets;
	int _running;
	int _bypass;
	int _backend;
public:
	DiscordHandler();
	~DiscordHandler();
	int IsBypassMode();
	void SetBypassMode(int mode);
	void SetBackend(int backend);
	int GetBackend();
	void SetToken(const char* token);
	void GetAppToken(char* app_token);
	void SetApplicationId(unsigned long long application_id);
	void SetApplicationName(const char* application_name);
	void SetApplicationInfo(unsigned long long client_id);
	void PrintApplicationInfo();
	int  InitCurrentUser();
	void GetCurrentUser(struct DiscordUser* user);
	void SetActivity(struct DiscordActivity* activity);
	void Fake_SetActivity(struct DiscordActivity* activity);
	void Fake_ClearActivity();
	void SetUser(struct DiscordUser* user);
	void ClearActivity();
	void PrintCurrentActivity();
	void PrintCurrentUser();
	void MapIdToAsset(const char* asset_name, char* asset_id);
};




void InitDiscordHandler(DiscordHandler** handler);