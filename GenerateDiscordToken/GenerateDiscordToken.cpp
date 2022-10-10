#include <Windows.h>
#include <DBUtil.h>
#include <DiscordREST.h>
#include <stdio.h>


int main() {
    char discord_token[256] = { 0x00 };
    int res = GetDiscordToken(discord_token);
    if (!res) {
        printf("Failed to Get Discord Token :(\n");
        system("pause");
        return -1;
    }
    SaveToken(discord_token);
    printf("Token Saved Successfully to: %s!\n", CACHED_TOKEN_PATH);
    system("pause");
}
