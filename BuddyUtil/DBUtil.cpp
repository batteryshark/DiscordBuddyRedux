#include <Windows.h>
#include <Windows.h>
#include <stdio.h>
#include "DBUtil.h"

#define CACHED_TOKEN_PATH ".dbtoken"
#define INI_PATH "discordbuddy.ini"

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

// Generic, load a text file stuff.
BOOL LoadTextData(const char* path, char** buffer) {
    FILE* fp = NULL;
    fopen_s(&fp, path, "r");
    if (!fp) { return FALSE; }

    fseek(fp, 0L, SEEK_END);
    size_t length = ftell(fp);
    rewind(fp);
    *buffer = (char*)malloc(length);
    if (!*buffer) { return FALSE; }
    fread(*buffer, length, 1, fp);
    fclose(fp);
    return TRUE;
}

void GetCachedToken(char* discord_token) {
    char token_path[1024] = { 0x00 };
    FILE* fp = fopen(CACHED_TOKEN_PATH, "rb");
    fgets(discord_token, 128, fp);
    fclose(fp);
}

void SaveToken(const char* discord_token) {
    FILE* fp = fopen(CACHED_TOKEN_PATH, "wb");
    fputs(discord_token, fp);
    fclose(fp);
}

void CheckAndCreateINI() {
    FILE* fp = fopen(INI_PATH, "r");
    if (fp) { fclose(fp); return; }

    fp = fopen(INI_PATH, "w");
    fputs("[GLOBAL]\n", fp);
    fputs("buddy_bypass=0\n", fp);
    fputs("\n", fp);
    fputs("[DISCORD_API]\n", fp);
    fputs("discord_api_version=9\n", fp);
    fputs("discord_api_baseurl=https://discord.com/api/v9\n", fp);
    fputs("discord_gateway_baseurl=wss://gateway.discord.gg\n", fp);
    fputs("\n", fp);
    fclose(fp);
}

void GetAPIBaseURL(char* base_url) {
    CheckAndCreateINI();
    GetPrivateProfileStringA("DISCORD_API", "discord_api_baseurl", "https://discord.com/api/v9", base_url, 128, INI_PATH);
}

void GetGatewayBaseURL(char* gateway_base_url) {
    CheckAndCreateINI();
    GetPrivateProfileStringA("DISCORD_API", "discord_gateway_baseurl", "wss://gateway.discord.gg", gateway_base_url, 128, INI_PATH);
    int api_version = GetAPIVersion();
    char api_cmd[64] = { 0x00 };
    sprintf(api_cmd, "/?v=%d&encoding=json", api_version);
    strcat(gateway_base_url, api_cmd);
}

int GetAPIVersion() {
    CheckAndCreateINI();
    return GetPrivateProfileIntA("DISCORD_API", "discord_api_version", 9, INI_PATH);
}

BOOL GetBypassEnabled() {
    CheckAndCreateINI();
    return GetPrivateProfileIntA("GLOBAL", "buddy_bypass", 0, INI_PATH);
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