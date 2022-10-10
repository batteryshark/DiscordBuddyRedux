#pragma once
#include "cJSON.h"

int GetUserInfo(const char *user_info_url, const char *token, cJSON **info_response);
int GetAppAssets(const char *assets_info_url, unsigned long long application_id, const char *token, cJSON **info_response);
int GetAppInfo(const char *assets_info_url, unsigned long long application_id, const char *token, cJSON **info_response);
int GetDiscordToken(char *discord_token);
int GetAppIDToken(unsigned long long app_id, char *discord_token, char *app_token);
void CurlShutdown();
