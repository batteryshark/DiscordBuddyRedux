#include <Windows.h>
#include <stdio.h>
#include "cJSON.h"
#include "DBUtil.h"
#include <curl/curl.h>

//#define _CURL_DEBUG



struct memory {
    char* response;
    size_t size;
};
static int is_curl_initialized = 0;


void GetAuthHeader(const char* token, char* header) {
    sprintf_s(header, 256, "Authorization: %s", token);
}

static size_t write_callback(void* data, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct memory* mem = (struct memory*)userp;

    char* ptr = (char*)realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0;  /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
}



void CurlShutdown() {
    curl_global_cleanup();
}



int HTTPSPostJSON(const char* url, const char* auth_header, cJSON* request_data, cJSON** response_data) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    struct memory chunk = { 0 };
#ifdef _CURL_DEBUG
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");

    if (auth_header) {
        headers = curl_slist_append(headers, auth_header);
    }

    if (curl) {
        char* rd = cJSON_PrintUnformatted(request_data);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, rd);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    }
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        DBG_printf("%s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return 0;
    }

    *response_data = cJSON_Parse(chunk.response);
    curl_easy_cleanup(curl);
    return 1;
}

int HTTPSGetJSON(const char* url, const char* auth_header, cJSON** response_data) {
    if (!is_curl_initialized) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        is_curl_initialized = 1;
    }
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    struct memory chunk = { 0 };
#ifdef _CURL_DEBUG
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");

    if (auth_header) {
        headers = curl_slist_append(headers, auth_header);
    }

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    }
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK) {
        OutputDebugStringA(curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return 0;
    }
    *response_data = cJSON_Parse(chunk.response);
    curl_easy_cleanup(curl);
    return 1;
}



int GetUserInfo(const char* user_info_url, const char* token, cJSON** info_response) {
    char auth_header[256] = { 0x00 };
    GetAuthHeader(token, auth_header);
    int res = HTTPSGetJSON(user_info_url, auth_header, info_response);
    memset(auth_header, 0, sizeof(auth_header));
    if (!res) {
        OutputDebugStringA("[DiscordBuddy] REST Error: GetUserInfo");
        return 0;
    }
    return 1;
}

int GetAppInfo(const char* app_info_url, unsigned long long application_id, const char* token, cJSON** info_response) {
    char url[128] = { 0x00 };
    char auth_header[256] = { 0x00 };
    sprintf(url, app_info_url, application_id);
    GetAuthHeader(token, auth_header);
    int res = HTTPSGetJSON(url, auth_header, info_response);
    memset(auth_header, 0, sizeof(auth_header));
    if (!res) {
        OutputDebugStringA("[DiscordBuddy] REST Error: GetAppInfo");
        return 0;
    }
    return 1;
}

int GetAppAssets(const char* assets_info_url, unsigned long long application_id, const char* token, cJSON** info_response) {
    char url[128] = { 0x00 };
    char auth_header[256] = { 0x00 };
    sprintf(url, assets_info_url, application_id);
    GetAuthHeader(token, auth_header);
    int res = HTTPSGetJSON(url, auth_header, info_response);
    memset(auth_header, 0, sizeof(auth_header));
    if (!res) {
        DBG_printf("[DiscordBuddy] REST Error: GetAppAssets");
        return 0;
    }

    return 1;
}

int GetAppIDToken(unsigned long long app_id, char* discord_token, char* app_token) {
    char token_url[256] = { 0x00 };
    GetURLAppToken(token_url, app_id);
    char auth_header[128] = { 0x00 };
    sprintf(auth_header, "Authorization: %s", discord_token);
    cJSON* token_request = cJSON_CreateObject();
    cJSON_AddStringToObject(token_request, "permissions", "0");
    cJSON_AddBoolToObject(token_request, "authorize", 1);
    cJSON* token_response;
    int res = HTTPSPostJSON(token_url, auth_header, token_request, &token_response);

    cJSON_Delete(token_request);
    if (!res) {
        DBG_printf("Error on Discord App Token Request\n");
        return 0;
    }

    char res_location[1024] = { 0x00 };
    // If the token is located here, we're done... also this means 2FA isn't enabled.
    if (cJSON_GetObjectItemCaseSensitive(token_response, "location")->valuestring) {
        strcpy_s(res_location, sizeof(res_location), cJSON_GetObjectItemCaseSensitive(token_response, "location")->valuestring);

        const char* at_start = strstr(res_location, "access_token=");
        if (!at_start) { return 0; }
        at_start += strlen("access_token=");

        const char* at_end = strstr(at_start, "&");
        size_t tok_len = at_end - at_start;

        memcpy(app_token, at_start, tok_len);

        return 1;
    }
    return 0;

}

int GetDiscordToken(char* discord_token) {
    char auth_login_url[128] = {0x00};
    char auth_totp_url[128] = {0x00};
    GetAuthLoginURL(auth_login_url);
    GetMFATotpURL(auth_totp_url);

    char discord_username[256] = { 0x00 };
    char discord_password[256] = { 0x00 };
    char discord_code[256] = { 0x00 };

    printf("Enter your Discord Email Address: ");
    fgets(discord_username, sizeof(discord_username), stdin);
    discord_username[strcspn(discord_username, "\n")] = 0;
    printf("Enter your Discord Password: ");
    fgets(discord_password, sizeof(discord_password), stdin);
    discord_password[strcspn(discord_password, "\n")] = 0;
  
    cJSON* login_request = cJSON_CreateObject();
    cJSON_AddStringToObject(login_request, "login", discord_username);
    cJSON_AddStringToObject(login_request, "password", discord_password);
    cJSON_AddBoolToObject(login_request, "undelete", 0);
    cJSON_AddNullToObject(login_request, "captcha_key");
    cJSON_AddNullToObject(login_request, "login_source");
    cJSON_AddNullToObject(login_request, "gift_code_sku_id");

    cJSON* login_response;
    int res = HTTPSPostJSON(auth_login_url, NULL, login_request, &login_response);
    cJSON_Delete(login_request);
    if (!res) {
        printf("Error on Discord Login Request\n");
        return 0;
    }

    if (!login_response) {
        printf("Error Parsing Login Response\n");
        return 0;
    }
 
    if (!cJSON_GetObjectItemCaseSensitive(login_response, "token")) {
        printf("Error Authenticating Login Credentials: Probably Invalid Username/Email + Password\n");
        return 0;
    }
    // If the token is located here, we're done... also this means 2FA isn't enabled.
    if (cJSON_GetObjectItemCaseSensitive(login_response, "token")->valuestring) {
        strcpy_s(discord_token, 256, cJSON_GetObjectItemCaseSensitive(login_response, "token")->valuestring);
    }
    else { // Otherwise, we need to to the TOTP Dance
        cJSON* totp_request = cJSON_CreateObject();
        cJSON_AddStringToObject(totp_request, "ticket", cJSON_GetObjectItemCaseSensitive(login_response, "ticket")->valuestring);
        cJSON_AddNullToObject(totp_request, "login_source");
        cJSON_AddNullToObject(totp_request, "gift_code_sku_id");
        cJSON_Delete(login_response);
        printf("Enter your Discord 2FA Code (NO SPACES): ");
        fgets(discord_code, sizeof(discord_code), stdin);
        discord_code[strcspn(discord_code, "\n")] = 0;
        cJSON_AddStringToObject(totp_request, "code", discord_code);
        cJSON* totp_response;
        int res = HTTPSPostJSON(auth_totp_url, NULL, totp_request, &totp_response);
        cJSON_Delete(totp_request);
        if (!res) {
            printf("Error on Discord TOTP Request\n");
            return 0;
        }

        if (!cJSON_GetObjectItemCaseSensitive(login_response, "token")) {
            printf("Error Validating 2FA Code: Probably Invalid Code.\n");
            return 0;
        }

        strcpy_s(discord_token, 256, cJSON_GetObjectItemCaseSensitive(totp_response, "token")->valuestring);
        cJSON_Delete(totp_response);
    }

    return 1;
}