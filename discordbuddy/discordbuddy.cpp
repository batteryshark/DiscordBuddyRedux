#include <Windows.h>
#include "discord_game_sdk.h"
#include "DiscordHandler.h"
#include "DBUtil.h"

typedef enum EDiscordResult __cdecl tDiscordCreate(DiscordVersion version, struct DiscordCreateParams* params, struct IDiscordCore** result);
static tDiscordCreate* real_DiscordCreate = NULL;


class User final {
public:
    void SetId(void* id);
    void* GetId() const;
    void SetUsername(char const* username);
    char const* GetUsername() const;
    void SetDiscriminator(char const* discriminator);
    char const* GetDiscriminator() const;
    void SetAvatar(char const* avatar);
    char const* GetAvatar() const;
    void SetBot(bool bot);
    bool GetBot() const;

private:
    DiscordUser internal_;
};


typedef struct _eventry {
    int is_active;
    int* callback_command;
    unsigned char* stuff;
    unsigned char* stuff2;
    void* pptr_thing;
}eventry;

struct Application {
    struct IDiscordCore* core;
    eventry e0;
    eventry e1;
    eventry e2;
};
static struct Application* app;
struct IDiscordUserManager umanager;
static struct IDiscordActivityManager actmanager;
static struct DiscordCreateParams cparams;
static struct IDiscordApplicationManager appmanager;
static void* pptr_GetCurrentUser = NULL;
static int first_callback = 1;
static int user_callback = 0;
static int app_callback = 0;

static DiscordHandler* discord_handler;
enum EDiscordResult GetCurrentUser(struct IDiscordUserManager* manager, struct DiscordUser* current_user);

void SetLogHook(struct IDiscordCore* core, enum EDiscordLogLevel min_level, void* hook_data, void (*hook)(void* hook_data, enum EDiscordLogLevel level, const char* message)) {/* TODO*/ }
struct IDiscordActivityManager* GetActivityManager(struct IDiscordCore* core) { return &actmanager; }
struct IDiscordUserManager* GetUserManager(struct IDiscordCore* core) { return &umanager; }
struct IDiscordApplicationManager* GetApplicationManager(struct IDiscordCore* core) { return &appmanager; }
void CoreDestroy(struct IDiscordCore* core) { delete discord_handler; }
enum EDiscordResult RunCallbacks(struct IDiscordCore* core) {
    if (!pptr_GetCurrentUser) {

        app->e0.is_active = 1;
        pptr_GetCurrentUser = &GetCurrentUser;
        *app->e0.callback_command = (int)&pptr_GetCurrentUser;
        cparams.user_events->on_current_user_update(app);
        first_callback = 0;
    }

    if (app_callback) {

        app->e1.is_active = 1;
        app->e2.is_active = 1;
        pptr_GetCurrentUser = &GetCurrentUser;


        app_callback = 0;
    }

    return DiscordResult_Ok;
}

enum EDiscordResult GetCurrentUser(struct IDiscordUserManager* manager, struct DiscordUser* current_user) {

    discord_handler->GetCurrentUser(current_user);
    return DiscordResult_Ok;
}

void GetOAuth2Token(struct IDiscordApplicationManager* manager, void* callback_data, void (*callback)(void* callback_data, enum EDiscordResult result, struct DiscordOAuth2Token* oauth2_token)) {

    DiscordOAuth2Token tok;
    memset(tok.access_token, 0x00,sizeof(tok.access_token));
    discord_handler->GetAppToken(tok.access_token);
    tok.expires = 0;
    strcpy(tok.scopes, "identify");
    app_callback = 1;

    callback(callback_data, DiscordResult_Ok, &tok);

}

void UpdateActivity(struct IDiscordActivityManager* manager, struct DiscordActivity* activity, void* callback_data, void (*callback)(void* callback_data, enum EDiscordResult result)) {
    discord_handler->SetActivity(activity);
}
void ClearActivity(struct IDiscordActivityManager* manager, void* callback_data, void (*callback)(void* callback_data, enum EDiscordResult result)) {
    discord_handler->ClearActivity();
}

extern "C"  enum EDiscordResult __declspec(dllexport) __cdecl DiscordCreate(DiscordVersion version, struct DiscordCreateParams* params, struct IDiscordCore** result) {
    InitDiscordHandler(&discord_handler);
    if (discord_handler->IsBypassMode()) {
        return real_DiscordCreate(version, params, result);
    }
    discord_handler->SetApplicationInfo(params->client_id);
    discord_handler->ClearActivity();
    struct IDiscordCore* dcore = (struct IDiscordCore*)calloc(1, sizeof(struct IDiscordCore));
    if (dcore == NULL) { return DiscordResult_InternalError; }
    app = (struct Application*)result;

    dcore->set_log_hook = SetLogHook;
    dcore->destroy = CoreDestroy;
    dcore->run_callbacks = RunCallbacks;
    dcore->get_activity_manager = GetActivityManager;
    dcore->get_user_manager = GetUserManager;
    dcore->get_application_manager = GetApplicationManager;

    memcpy(&cparams, params, sizeof(struct DiscordCreateParams));
    *result = dcore;

    return DiscordResult_Ok;
}


void shutdown_library() {
    delete discord_handler;
}
BOOL init_library() {
    real_DiscordCreate = (tDiscordCreate*)GetProcAddress(LoadLibraryA("discord_game_sdk.dll"), "DiscordCreate");

    umanager.get_current_user = GetCurrentUser;
    actmanager.clear_activity = ClearActivity;
    actmanager.update_activity = UpdateActivity;
    appmanager.get_oauth2_token = GetOAuth2Token;
    return TRUE;
}

// Entry-Point Function
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        OutputDebugStringA("Starting DiscordBuddy...\n");
        return init_library();
    }
    if (fdwReason == DLL_PROCESS_DETACH) {
        shutdown_library();
    }
    return TRUE;

}