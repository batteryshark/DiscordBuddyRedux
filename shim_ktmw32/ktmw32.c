#include <Windows.h>
#include <stubcaller.h>
#include <stdio.h>
#include <DBUtil.h>

// Our KTMW32 Stubs
BOOL fake_CommitTransaction(
    HANDLE TransactionHandle
) {
    static LRESULT(WINAPI * funcp)(HANDLE a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "CommitTransaction");
    return (*funcp)(TransactionHandle);
}

HANDLE fake_CreateTransaction(
    LPSECURITY_ATTRIBUTES lpTransactionAttributes,
    LPGUID UOW,
    DWORD CreateOptions,
    DWORD IsolationLevel,
    DWORD IsolationFlags,
    DWORD Timeout,
    LPWSTR Description
) {
    static LRESULT(WINAPI * funcp)(LPSECURITY_ATTRIBUTES lpTransactionAttributes,
        LPGUID UOW,
        DWORD CreateOptions,
        DWORD IsolationLevel,
        DWORD IsolationFlags,
        DWORD Timeout,
        LPWSTR Description) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "CreateTransaction");
    return (*funcp)(lpTransactionAttributes, UOW, CreateOptions, IsolationLevel, IsolationFlags, Timeout, Description);
}

// The Discord Stuff
typedef int tDiscordCreate(int version, void* params, void* result);
static tDiscordCreate* dbDiscordCreate = NULL;

void patch_discord_sdk() {
    // Avoid even loading our discordbuddy dll if bypass is enabled.
    if (!IsBuddyEnabled()) {
        OutputDebugStringA("DiscordBuddy Bypass -- Using Real Discord SDK.");
        return; 
    }
    OutputDebugStringA("DiscordBuddy Initializing...");
    HMODULE db = LoadLibraryA("discordbuddy.dll");
    LoadLibraryA("discord_game_sdk.dll");
    dbDiscordCreate = (tDiscordCreate*)GetProcAddress(db, "DiscordCreate");
    if (Hook_IAT_Name("discord_game_sdk.dll", "DiscordCreate", dbDiscordCreate)) {
        OutputDebugStringA("Discord Buddy Hooked!\n");
    }
    else {
        OutputDebugStringA("Discord Buddy Not Hooked!\n");
    }
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

    if (fdwReason == DLL_PROCESS_ATTACH) {
        printf("Starting Db Shim...\n");
        patch_discord_sdk();
    }
    return TRUE;
}