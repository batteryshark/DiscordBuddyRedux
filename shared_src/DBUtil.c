#include <Windows.h>
#include <stdio.h>
#include "DBUtil.h"


static char ini_path[1024] = { 0x00 };

void DBG_printf(const char* format, ...) {

    char* s = (char*)calloc(1, 32768);
    va_list args;
    va_start(args, format);
    vsnprintf(s, 32767, format, args);
    va_end(args);
    s[32767] = 0;
    OutputDebugStringA(s);
    free(s);

}

void DBG_print_buffer(unsigned char* data, size_t size) {
    size_t ansi_sz = (size * 2) + 1;
    char* a_buffer = NULL;
    a_buffer = (char*)calloc(1, ansi_sz);
    if (!a_buffer) { return; }
    for (unsigned int i = 0; i < size; i++) {
        snprintf(a_buffer + (i * 2), ansi_sz, "%02x", data[i]);
    }
    OutputDebugStringA(a_buffer);
    free(a_buffer);

}





void CheckAndCreateINI() {
    if (strlen(ini_path) < strlen(INI_FILENAME)) {
        GetCurrentDirectoryA(sizeof(ini_path), ini_path);
        strcat(ini_path, "\\");
        strcat(ini_path, INI_FILENAME);
    }
    
    FILE* fp = fopen(ini_path, "r");
    if (fp) { fclose(fp); return; }
    DBG_printf("discordbuddy.ini doesn't exist - creating...");
    fp = fopen(ini_path, "w");
    fputs("[GLOBAL]\n", fp);
    fputs("buddy_enabled=1\n", fp);
    fputs("rp_enabled=1\n", fp);
    fputs("discord_token=\n", fp);
    fputs("\n", fp);
    fputs("[DISCORD_API]\n", fp);
    fputs("discord_api_version=9\n", fp);
    fputs("discord_api_baseurl=https://discord.com/api/v9\n", fp);
    fputs("discord_gateway_baseurl=wss://gateway.discord.gg\n", fp);
    fputs("\n", fp);
    fclose(fp);
}

void GetCachedToken(char* discord_token) {
    CheckAndCreateINI();
    GetPrivateProfileStringA("GLOBAL", "discord_token", NULL, discord_token, 128, ini_path);
    if (discord_token == NULL) {
        MessageBoxA(NULL, "No Discord Token", "Error: Discord Token Not found in discordbuddy.ini", MB_ICONERROR | MB_OK);
        exit(-1);
    }
}

void SaveToken(const char* discord_token) {
    CheckAndCreateINI();
    WritePrivateProfileStringA("GLOBAL", "discord_token", discord_token, ini_path);
}


void GetAPIBaseURL(char* base_url) {
    CheckAndCreateINI();
    GetPrivateProfileStringA("DISCORD_API", "discord_api_baseurl", "https://discord.com/api/v9", base_url, 128, ini_path);
}

void GetGatewayBaseURL(char* gateway_base_url) {
    CheckAndCreateINI();
    GetPrivateProfileStringA("DISCORD_API", "discord_gateway_baseurl", "wss://gateway.discord.gg", gateway_base_url, 128, ini_path);
    int api_version = GetAPIVersion();
    char api_cmd[64] = { 0x00 };
    sprintf(api_cmd, "/?v=%d&encoding=json", api_version);
    strcat(gateway_base_url, api_cmd);
}

void GetAuthLoginURL(char* auth_login_url){
    GetAPIBaseURL(auth_login_url);
    strcat(auth_login_url,"/auth/login");
}

void GetMFATotpURL(char* mfa_totp_url){
    GetAPIBaseURL(mfa_totp_url);
    strcat(mfa_totp_url,"/auth/mfa/totp");
}

int GetAPIVersion() {
    CheckAndCreateINI();
    return GetPrivateProfileIntA("DISCORD_API", "discord_api_version", 9, ini_path);
}

int IsBuddyEnabled() {
    CheckAndCreateINI();
    int res = GetPrivateProfileIntA("GLOBAL", "buddy_enabled", 0, ini_path);
    DBG_printf("IsBuddyEnabled: %d\n", res);
    return res;
}

int IsRPEnabled() {
    CheckAndCreateINI();
    int res = GetPrivateProfileIntA("GLOBAL", "rp_enabled", 0, ini_path);
    DBG_printf("RPEnabled: %d\n", res);
    return res;
}

void GetURLUserInfo(char* url_user_info) {
    GetAPIBaseURL(url_user_info);
    strcat(url_user_info, "/users/@me");
}

void GetURLAssetInfo(char* url_asset_info,unsigned long long app_id) {
    char base_url[128] = { 0x00 };
    GetAPIBaseURL(base_url);
    sprintf(url_asset_info, "%s/oauth2/applications/%llu/assets", base_url, app_id);
}
void GetURLAppInfo(char* url_app_info, unsigned long long app_id) {
    char base_url[128] = { 0x00 };
    GetAPIBaseURL(base_url);
    sprintf(url_app_info, "%s/oauth2/applications/%llu/rpc", base_url, app_id);
}

void GetURLAppToken(char* url_app_token, unsigned long long app_id) {
    char base_url[128] = { 0x00 };
    GetAPIBaseURL(base_url);
    sprintf(url_app_token, "%s/oauth2/authorize?client_id=%llu&response_type=token&scope=identify", base_url, app_id);
}

