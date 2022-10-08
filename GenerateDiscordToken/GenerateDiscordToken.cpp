#include <Windows.h>
#include <stdio.h>
#include <string>
#include "DBUtil.h"
#include "DiscordREST.h"

int main(){
	char discord_base_api_url[128] = { 0x00 };
	GetAPIBaseURL(discord_base_api_url);

	std::string login_url = discord_base_api_url + std::string("/auth/login");
	std::string totp_url = discord_base_api_url + std::string("/auth/mfa/totp");
	
	char discord_token[256] = { 0x00 };
	int res = GetToken(login_url.c_str(), totp_url.c_str(), discord_token);
	if (!res) {
		printf("Failed to Get Discord Token :(\n");
		return -1;
	}
	SaveToken(discord_token);
	printf("Token Saved Successfully!\n");
}
