#include <Windows.h>
#include "global.h"


typedef int tDiscordCreate(int version, void* params, void* result);
static tDiscordCreate* dbDiscordCreate = NULL;

void patch_discord_sdk() {   

    HMODULE db = LoadLibraryA("discordbuddy.dll");
    LoadLibraryA("discord_game_sdk.dll");
    dbDiscordCreate = (tDiscordCreate*)GetProcAddress(db, "DiscordCreate");
    if (Hook_IAT_Name("discord_game_sdk.dll", "DiscordCreate", dbDiscordCreate)) {
        printf("Discord Buddy Hooked!\n");
    }
    else {
        printf("Discord Buddy Not Hooked!\n");
    }
}




BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved){

    if (fdwReason == DLL_PROCESS_ATTACH) {
        printf("Starting WinMM Shim...\n");
        patch_discord_sdk();
    }
    return TRUE;
}