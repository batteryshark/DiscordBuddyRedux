#pragma once

void DBG_printf(const char* format, ...);
BOOL LoadTextData(const char* path, char** buffer);
void DBG_print_buffer(unsigned char* data, size_t size);
void GetCachedToken(char* discord_token);
void SaveToken(const char* discord_token);
void GetAPIBaseURL(char* base_url);
BOOL GetBypassEnabled();
int GetAPIVersion();
void GetGatewayBaseURL(char* gateway_base_url);
void GetURLUserInfo(char* url_user_info);
void GetURLAssetInfo(char* url_asset_info, unsigned long long app_id);
void GetURLAppInfo(char* url_app_info, unsigned long long app_id);
void GetURLAppToken(char* url_app_token, unsigned long long app_id);