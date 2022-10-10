#include <Windows.h>

// near the top of your CPP file
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

static HINSTANCE real_handle = NULL;
HINSTANCE get_cached_handle(){
    return real_handle;
}

void ExitMonitor(LPVOID DLLHandle){
    WaitForSingleObject(DLLHandle, INFINITE);
    FreeLibrary(get_cached_handle());
}

void* load_real_dll(){
    if (real_handle)
        return real_handle;

    char dll_filename[512 + 1] = { 0 };
    GetModuleFileNameA((HINSTANCE)&__ImageBase, dll_filename, _MAX_PATH);

    char dll_path[MAX_PATH];

    GetSystemDirectoryA(dll_path, MAX_PATH);
    strncat(dll_path, "\\", 1);
    strncat(dll_path, dll_filename, MAX_PATH);
    OutputDebugStringA("[stubcaller::load_real_dll]");
    OutputDebugStringA(dll_path);

    real_handle = LoadLibraryA(dll_path);

    //start watcher thread to close the library
    CreateThread(NULL, 500, (LPTHREAD_START_ROUTINE)ExitMonitor, GetCurrentThread(), 0, NULL);

    return real_handle;
}