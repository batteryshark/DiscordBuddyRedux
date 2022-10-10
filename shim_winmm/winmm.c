#include <Windows.h>
#include <stubcaller.h>
#include <DBUtil.h>




LRESULT WINAPI fake_CloseDriver(HDRVR a0, LONG a1, LONG a2)
{
    static LRESULT(WINAPI * funcp)(HDRVR a0, LONG a1, LONG a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "CloseDriver");
    return (*funcp)(a0, a1, a2);
}

HDRVR WINAPI fake_OpenDriver(LPCWSTR a0, LPCWSTR a1, LONG a2)
{
    static HDRVR(WINAPI * funcp)(LPCWSTR a0, LPCWSTR a1, LONG a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "OpenDriver");
    return (*funcp)(a0, a1, a2);
}

LRESULT WINAPI fake_SendDriverMessage(HDRVR a0, UINT a1, LONG a2, LONG a3)
{
    static LRESULT(WINAPI * funcp)(HDRVR a0, UINT a1, LONG a2, LONG a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "SendDriverMessage");
    return (*funcp)(a0, a1, a2, a3);
}

HMODULE WINAPI fake_DrvGetModuleHandle(HDRVR a0)
{
    static HMODULE(WINAPI * funcp)(HDRVR a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "DrvGetModuleHandle");
    return (*funcp)(a0);
}

HMODULE WINAPI fake_GetDriverModuleHandle(HDRVR a0)
{
    static HMODULE(WINAPI * funcp)(HDRVR a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "GetDriverModuleHandle");
    return (*funcp)(a0);
}

LRESULT WINAPI fake_DefDriverProc(DWORD a0, HDRVR a1, UINT a2, LPARAM a3, LPARAM a4)
{
    static LRESULT(WINAPI * funcp)(DWORD a0, HDRVR a1, UINT a2, LPARAM a3, LPARAM a4) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "DefDriverProc");
    return (*funcp)(a0, a1, a2, a3, a4);
}

UINT WINAPI fake_mmsystemGetVersion()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmsystemGetVersion");
    return (*funcp)();
}

BOOL WINAPI fake_sndPlaySoundA(LPCSTR a0, UINT a1)
{
    static BOOL(WINAPI * funcp)(LPCSTR a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "sndPlaySoundA");
    return (*funcp)(a0, a1);
}

BOOL WINAPI fake_sndPlaySoundW(LPCWSTR a0, UINT a1)
{
    static BOOL(WINAPI * funcp)(LPCWSTR a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "sndPlaySoundW");
    return (*funcp)(a0, a1);
}

BOOL WINAPI fake_PlaySound(LPCSTR a0, HMODULE a1, DWORD a2)
{
    static BOOL(WINAPI * funcp)(LPCSTR a0, HMODULE a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "PlaySound");
    return (*funcp)(a0, a1, a2);
}

BOOL WINAPI fake_PlaySoundA(LPCSTR a0, HMODULE a1, DWORD a2)
{
    static BOOL(WINAPI * funcp)(LPCSTR a0, HMODULE a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "PlaySoundA");
    return (*funcp)(a0, a1, a2);
}

BOOL WINAPI fake_PlaySoundW(LPCWSTR a0, HMODULE a1, DWORD a2)
{
    static BOOL(WINAPI * funcp)(LPCWSTR a0, HMODULE a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "PlaySoundW");
    return (*funcp)(a0, a1, a2);
}

UINT WINAPI fake_waveOutGetNumDevs()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_waveOutGetDevCapsA(UINT a0, LPWAVEOUTCAPSA a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPWAVEOUTCAPSA a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetDevCapsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutGetDevCapsW(UINT a0, LPWAVEOUTCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPWAVEOUTCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutGetVolume(HWAVEOUT a0, PDWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, PDWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetVolume");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutSetVolume(HWAVEOUT a0, DWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, DWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutSetVolume");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutGetErrorTextA(MMRESULT a0, LPSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetErrorTextA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutGetErrorTextW(MMRESULT a0, LPWSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetErrorTextW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_auxGetDevCapsA(UINT_PTR uDeviceID, LPAUXCAPS lpCaps, UINT cbCaps)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "auxGetDevCapsA");
    return (*funcp)(uDeviceID, lpCaps, cbCaps);
}

UINT WINAPI fake_auxGetNumDevs()
{
    static MMRESULT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "auxGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_auxGetVolume(UINT uDeviceID, LPDWORD lpdwVolume)
{

    static MMRESULT(WINAPI * funcp)(UINT uDeviceID, LPDWORD lpdwVolume) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "auxGetVolume");
    return (*funcp)(uDeviceID, lpdwVolume);

}

MMRESULT WINAPI fake_auxSetVolume(UINT uDeviceID, DWORD dwVolume)
{
    static MMRESULT(WINAPI * funcp)(UINT uDeviceID, DWORD dwVolume) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "auxSetVolume");
    return (*funcp)(uDeviceID, dwVolume);
}

MCIERROR WINAPI fake_mciSendStringA(LPCTSTR cmd, LPTSTR ret, UINT cchReturn, HANDLE hwndCallback)
{
    static MMRESULT(WINAPI * funcp)(LPCTSTR cmd, LPTSTR ret, UINT cchReturn, HANDLE hwndCallback) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciSendStringA");
    return (*funcp)(cmd, ret, cchReturn, hwndCallback);
}

MCIERROR WINAPI fake_mciSendCommandA(MCIDEVICEID IDDevice, UINT uMsg, DWORD_PTR fdwCommand, DWORD_PTR dwParam)
{
    static MMRESULT(WINAPI * funcp)(MCIDEVICEID IDDevice, UINT uMsg, DWORD_PTR fdwCommand, DWORD_PTR dwParam) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciSendCommandA");
    return (*funcp)(IDDevice, uMsg, fdwCommand, dwParam);
}

MMRESULT WINAPI fake_waveOutOpen(LPHWAVEOUT a0, UINT a1, LPCWAVEFORMATEX a2, DWORD a3, DWORD a4, DWORD a5)
{
    static MMRESULT(WINAPI * funcp)(LPHWAVEOUT a0, UINT a1, LPCWAVEFORMATEX a2, DWORD a3, DWORD a4, DWORD a5) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutOpen");
    return (*funcp)(a0, a1, a2, a3, a4, a5);
}

MMRESULT WINAPI fake_waveOutClose(HWAVEOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutClose");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveOutPrepareHeader(HWAVEOUT a0, LPWAVEHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, LPWAVEHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutPrepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutUnprepareHeader(HWAVEOUT a0, LPWAVEHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, LPWAVEHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutUnprepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutWrite(HWAVEOUT a0, LPWAVEHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, LPWAVEHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutWrite");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutPause(HWAVEOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutPause");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveOutRestart(HWAVEOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutRestart");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveOutReset(HWAVEOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutReset");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveOutBreakLoop(HWAVEOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutBreakLoop");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveOutGetPosition(HWAVEOUT a0, LPMMTIME a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, LPMMTIME a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetPosition");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveOutGetPitch(HWAVEOUT a0, PDWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, PDWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetPitch");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutSetPitch(HWAVEOUT a0, DWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, DWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutSetPitch");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutGetPlaybackRate(HWAVEOUT a0, PDWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, PDWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetPlaybackRate");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutSetPlaybackRate(HWAVEOUT a0, DWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, DWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutSetPlaybackRate");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutGetID(HWAVEOUT a0, LPUINT a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, LPUINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutGetID");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveOutMessage(HWAVEOUT a0, UINT a1, DWORD a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(HWAVEOUT a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveOutMessage");
    return (*funcp)(a0, a1, a2, a3);
}

UINT WINAPI fake_waveInGetNumDevs()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_waveInGetDevCapsA(UINT a0, LPWAVEINCAPSA a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPWAVEINCAPSA a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetDevCapsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInGetDevCapsW(UINT a0, LPWAVEINCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPWAVEINCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInGetErrorTextA(MMRESULT a0, LPSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetErrorTextA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInGetErrorTextW(MMRESULT a0, LPWSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetErrorTextW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInOpen(LPHWAVEIN a0, UINT a1, LPCWAVEFORMATEX a2, DWORD a3, DWORD a4, DWORD a5)
{
    static MMRESULT(WINAPI * funcp)(LPHWAVEIN a0, UINT a1, LPCWAVEFORMATEX a2, DWORD a3, DWORD a4, DWORD a5) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInOpen");
    return (*funcp)(a0, a1, a2, a3, a4, a5);
}

MMRESULT WINAPI fake_waveInClose(HWAVEIN a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInClose");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveInPrepareHeader(HWAVEIN a0, LPWAVEHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0, LPWAVEHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInPrepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInUnprepareHeader(HWAVEIN a0, LPWAVEHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0, LPWAVEHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInUnprepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInAddBuffer(HWAVEIN a0, LPWAVEHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0, LPWAVEHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInAddBuffer");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInStart(HWAVEIN a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInStart");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveInStop(HWAVEIN a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInStop");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveInReset(HWAVEIN a0)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInReset");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_waveInGetPosition(HWAVEIN a0, LPMMTIME a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0, LPMMTIME a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetPosition");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_waveInGetID(HWAVEIN a0, LPUINT a1)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0, LPUINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInGetID");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_waveInMessage(HWAVEIN a0, UINT a1, DWORD a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(HWAVEIN a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "waveInMessage");
    return (*funcp)(a0, a1, a2, a3);
}

UINT WINAPI fake_midiOutGetNumDevs()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_midiStreamOpen(LPHMIDISTRM a0, LPUINT a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5)
{
    static MMRESULT(WINAPI * funcp)(LPHMIDISTRM a0, LPUINT a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamOpen");
    return (*funcp)(a0, a1, a2, a3, a4, a5);
}

MMRESULT WINAPI fake_midiStreamClose(HMIDISTRM a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamClose");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiStreamProperty(HMIDISTRM a0, LPBYTE a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0, LPBYTE a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamProperty");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiStreamPosition(HMIDISTRM a0, LPMMTIME a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0, LPMMTIME a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamPosition");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiStreamOut(HMIDISTRM a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamOut");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiStreamPause(HMIDISTRM a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamPause");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiStreamRestart(HMIDISTRM a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamRestart");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiStreamStop(HMIDISTRM a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDISTRM a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiStreamStop");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiConnect(HMIDI a0, HMIDIOUT a1, PVOID a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDI a0, HMIDIOUT a1, PVOID a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiConnect");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiDisconnect(HMIDI a0, HMIDIOUT a1, PVOID a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDI a0, HMIDIOUT a1, PVOID a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiDisconnect");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutGetDevCapsA(UINT a0, LPMIDIOUTCAPSA a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPMIDIOUTCAPSA a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetDevCapsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutGetDevCapsW(UINT a0, LPMIDIOUTCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPMIDIOUTCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutGetVolume(HMIDIOUT a0, PDWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, PDWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetVolume");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_midiOutSetVolume(HMIDIOUT a0, DWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, DWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutSetVolume");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_midiOutGetErrorTextA(MMRESULT a0, LPSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetErrorTextA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutGetErrorTextW(MMRESULT a0, LPWSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetErrorTextW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutOpen(LPHMIDIOUT a0, UINT a1, DWORD a2, DWORD a3, DWORD a4)
{
    static MMRESULT(WINAPI * funcp)(LPHMIDIOUT a0, UINT a1, DWORD a2, DWORD a3, DWORD a4) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutOpen");
    return (*funcp)(a0, a1, a2, a3, a4);
}

MMRESULT WINAPI fake_midiOutClose(HMIDIOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutClose");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiOutPrepareHeader(HMIDIOUT a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutPrepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutUnprepareHeader(HMIDIOUT a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutUnprepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutShortMsg(HMIDIOUT a0, DWORD a1)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, DWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutShortMsg");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_midiOutLongMsg(HMIDIOUT a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutLongMsg");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiOutReset(HMIDIOUT a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutReset");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiOutCachePatches(HMIDIOUT a0, UINT a1, LPWORD a2, UINT a3)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, UINT a1, LPWORD a2, UINT a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutCachePatches");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_midiOutCacheDrumPatches(HMIDIOUT a0, UINT a1, LPWORD a2, UINT a3)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, UINT a1, LPWORD a2, UINT a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutCacheDrumPatches");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_midiOutGetID(HMIDIOUT a0, LPUINT a1)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, LPUINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutGetID");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_midiOutMessage(HMIDIOUT a0, UINT a1, DWORD a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(HMIDIOUT a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiOutMessage");
    return (*funcp)(a0, a1, a2, a3);
}

UINT WINAPI fake_midiInGetNumDevs()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_midiInGetDevCapsA(UINT a0, LPMIDIINCAPSA a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPMIDIINCAPSA a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInGetDevCapsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInGetDevCapsW(UINT a0, LPMIDIINCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPMIDIINCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInGetErrorTextA(MMRESULT a0, LPSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInGetErrorTextA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInGetErrorTextW(MMRESULT a0, LPWSTR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(MMRESULT a0, LPWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInGetErrorTextW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInOpen(LPHMIDIIN a0, UINT a1, DWORD a2, DWORD a3, DWORD a4)
{
    static MMRESULT(WINAPI * funcp)(LPHMIDIIN a0, UINT a1, DWORD a2, DWORD a3, DWORD a4) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInOpen");
    return (*funcp)(a0, a1, a2, a3, a4);
}

MMRESULT WINAPI fake_midiInClose(HMIDIIN a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInClose");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiInPrepareHeader(HMIDIIN a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInPrepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInUnprepareHeader(HMIDIIN a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInUnprepareHeader");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInAddBuffer(HMIDIIN a0, LPMIDIHDR a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0, LPMIDIHDR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInAddBuffer");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_midiInStart(HMIDIIN a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInStart");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiInStop(HMIDIIN a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInStop");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiInReset(HMIDIIN a0)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInReset");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_midiInGetID(HMIDIIN a0, LPUINT a1)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0, LPUINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInGetID");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_midiInMessage(HMIDIIN a0, UINT a1, DWORD a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(HMIDIIN a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "midiInMessage");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_auxGetDevCapsW(UINT a0, LPAUXCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPAUXCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "auxGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_auxOutMessage(UINT a0, UINT a1, DWORD a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "auxOutMessage");
    return (*funcp)(a0, a1, a2, a3);
}

UINT WINAPI fake_mixerGetNumDevs()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_mixerGetDevCapsA(UINT a0, LPMIXERCAPSA a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPMIXERCAPSA a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetDevCapsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetDevCapsW(UINT a0, LPMIXERCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPMIXERCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerOpen(LPHMIXER a0, UINT a1, DWORD a2, DWORD a3, DWORD a4)
{
    static MMRESULT(WINAPI * funcp)(LPHMIXER a0, UINT a1, DWORD a2, DWORD a3, DWORD a4) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerOpen");
    return (*funcp)(a0, a1, a2, a3, a4);
}

MMRESULT WINAPI fake_mixerClose(HMIXER a0)
{
    static MMRESULT(WINAPI * funcp)(HMIXER a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerClose");
    return (*funcp)(a0);
}

DWORD WINAPI fake_mixerMessage(HMIXER a0, UINT a1, DWORD a2, DWORD a3)
{
    static DWORD(WINAPI * funcp)(HMIXER a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerMessage");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_mixerGetLineInfoA(HMIXEROBJ a0, LPMIXERLINEA a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERLINEA a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetLineInfoA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetLineInfoW(HMIXEROBJ a0, LPMIXERLINEW a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERLINEW a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetLineInfoW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetID(HMIXEROBJ a0, PUINT a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, PUINT a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetID");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetLineControlsA(HMIXEROBJ a0, LPMIXERLINECONTROLSA a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERLINECONTROLSA a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetLineControlsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetLineControlsW(HMIXEROBJ a0, LPMIXERLINECONTROLSW a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERLINECONTROLSW a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetLineControlsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetControlDetailsA(HMIXEROBJ a0, LPMIXERCONTROLDETAILS a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERCONTROLDETAILS a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetControlDetailsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerGetControlDetailsW(HMIXEROBJ a0, LPMIXERCONTROLDETAILS a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERCONTROLDETAILS a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerGetControlDetailsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mixerSetControlDetails(HMIXEROBJ a0, LPMIXERCONTROLDETAILS a1, DWORD a2)
{
    static MMRESULT(WINAPI * funcp)(HMIXEROBJ a0, LPMIXERCONTROLDETAILS a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mixerSetControlDetails");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_timeGetSystemTime(LPMMTIME a0, UINT a1)
{
    static MMRESULT(WINAPI * funcp)(LPMMTIME a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeGetSystemTime");
    return (*funcp)(a0, a1);
}

DWORD WINAPI fake_timeGetTime()
{
    static DWORD(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeGetTime");
    return (*funcp)();
}

MMRESULT WINAPI fake_timeSetEvent(UINT a0, UINT a1, LPTIMECALLBACK a2, DWORD a3, UINT a4)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, UINT a1, LPTIMECALLBACK a2, DWORD a3, UINT a4) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeSetEvent");
    return (*funcp)(a0, a1, a2, a3, a4);
}

MMRESULT WINAPI fake_timeKillEvent(UINT a0)
{
    static MMRESULT(WINAPI * funcp)(UINT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeKillEvent");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_timeGetDevCaps(LPTIMECAPS a0, UINT a1)
{
    static MMRESULT(WINAPI * funcp)(LPTIMECAPS a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeGetDevCaps");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_timeBeginPeriod(UINT a0)
{
    static MMRESULT(WINAPI * funcp)(UINT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeBeginPeriod");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_timeEndPeriod(UINT a0)
{
    static MMRESULT(WINAPI * funcp)(UINT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "timeEndPeriod");
    return (*funcp)(a0);
}

UINT WINAPI fake_joyGetNumDevs()
{
    static UINT(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyGetNumDevs");
    return (*funcp)();
}

MMRESULT WINAPI fake_joyGetDevCapsA(UINT a0, LPJOYCAPSA a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPJOYCAPSA a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyGetDevCapsA");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_joyGetDevCapsW(UINT a0, LPJOYCAPSW a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPJOYCAPSW a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyGetDevCapsW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_joyGetPos(UINT a0, LPJOYINFO a1)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPJOYINFO a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyGetPos");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_joyGetPosEx(UINT a0, LPJOYINFOEX a1)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPJOYINFOEX a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyGetPosEx");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_joyGetThreshold(UINT a0, LPUINT a1)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, LPUINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyGetThreshold");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_joyReleaseCapture(UINT a0)
{
    static MMRESULT(WINAPI * funcp)(UINT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyReleaseCapture");
    return (*funcp)(a0);
}

MMRESULT WINAPI fake_joySetCapture(HWND a0, UINT a1, UINT a2, BOOL a3)
{
    static MMRESULT(WINAPI * funcp)(HWND a0, UINT a1, UINT a2, BOOL a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joySetCapture");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_joySetThreshold(UINT a0, UINT a1)
{
    static MMRESULT(WINAPI * funcp)(UINT a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joySetThreshold");
    return (*funcp)(a0, a1);
}

FOURCC WINAPI fake_mmioStringToFOURCCA(LPCSTR a0, UINT a1)
{
    static FOURCC(WINAPI * funcp)(LPCSTR a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioStringToFOURCCA");
    return (*funcp)(a0, a1);
}

FOURCC WINAPI fake_mmioStringToFOURCCW(LPCWSTR a0, UINT a1)
{
    static FOURCC(WINAPI * funcp)(LPCWSTR a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioStringToFOURCCW");
    return (*funcp)(a0, a1);
}

LPMMIOPROC WINAPI fake_mmioInstallIOProcA(FOURCC a0, LPMMIOPROC a1, DWORD a2)
{
    static LPMMIOPROC(WINAPI * funcp)(FOURCC a0, LPMMIOPROC a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioInstallIOProcA");
    return (*funcp)(a0, a1, a2);
}

LPMMIOPROC WINAPI fake_mmioInstallIOProcW(FOURCC a0, LPMMIOPROC a1, DWORD a2)
{
    static LPMMIOPROC(WINAPI * funcp)(FOURCC a0, LPMMIOPROC a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioInstallIOProcW");
    return (*funcp)(a0, a1, a2);
}

HMMIO WINAPI fake_mmioOpenA(LPSTR a0, LPMMIOINFO a1, DWORD a2)
{
    static HMMIO(WINAPI * funcp)(LPSTR a0, LPMMIOINFO a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioOpenA");
    return (*funcp)(a0, a1, a2);
}

HMMIO WINAPI fake_mmioOpenW(LPWSTR a0, LPMMIOINFO a1, DWORD a2)
{
    static HMMIO(WINAPI * funcp)(LPWSTR a0, LPMMIOINFO a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioOpenW");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mmioRenameA(LPCSTR a0, LPCSTR a1, LPCMMIOINFO a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(LPCSTR a0, LPCSTR a1, LPCMMIOINFO a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioRenameA");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_mmioRenameW(LPCWSTR a0, LPCWSTR a1, LPCMMIOINFO a2, DWORD a3)
{
    static MMRESULT(WINAPI * funcp)(LPCWSTR a0, LPCWSTR a1, LPCMMIOINFO a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioRenameW");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_mmioClose(HMMIO a0, UINT a1)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioClose");
    return (*funcp)(a0, a1);
}

LONG WINAPI fake_mmioRead(HMMIO a0, HPSTR a1, LONG a2)
{
    static LONG(WINAPI * funcp)(HMMIO a0, HPSTR a1, LONG a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioRead");
    return (*funcp)(a0, a1, a2);
}

LONG WINAPI fake_mmioWrite(HMMIO a0, LPCSTR a1, LONG a2)
{
    static LONG(WINAPI * funcp)(HMMIO a0, LPCSTR a1, LONG a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioWrite");
    return (*funcp)(a0, a1, a2);
}

LONG WINAPI fake_mmioSeek(HMMIO a0, LONG a1, int a2)
{
    static LONG(WINAPI * funcp)(HMMIO a0, LONG a1, int a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioSeek");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mmioGetInfo(HMMIO a0, LPMMIOINFO a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPMMIOINFO a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioGetInfo");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mmioSetInfo(HMMIO a0, LPCMMIOINFO a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPCMMIOINFO a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioSetInfo");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mmioSetBuffer(HMMIO a0, LPSTR a1, LONG a2, UINT a3)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPSTR a1, LONG a2, UINT a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioSetBuffer");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_mmioFlush(HMMIO a0, UINT a1)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, UINT a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioFlush");
    return (*funcp)(a0, a1);
}

MMRESULT WINAPI fake_mmioAdvance(HMMIO a0, LPMMIOINFO a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPMMIOINFO a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioAdvance");
    return (*funcp)(a0, a1, a2);
}

LRESULT WINAPI fake_mmioSendMessage(HMMIO a0, UINT a1, LPARAM a2, LPARAM a3)
{
    static LRESULT(WINAPI * funcp)(HMMIO a0, UINT a1, LPARAM a2, LPARAM a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioSendMessage");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_mmioDescend(HMMIO a0, LPMMCKINFO a1, const MMCKINFO* a2, UINT a3)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPMMCKINFO a1, const MMCKINFO * a2, UINT a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioDescend");
    return (*funcp)(a0, a1, a2, a3);
}

MMRESULT WINAPI fake_mmioAscend(HMMIO a0, LPMMCKINFO a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPMMCKINFO a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioAscend");
    return (*funcp)(a0, a1, a2);
}

MMRESULT WINAPI fake_mmioCreateChunk(HMMIO a0, LPMMCKINFO a1, UINT a2)
{
    static MMRESULT(WINAPI * funcp)(HMMIO a0, LPMMCKINFO a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmioCreateChunk");
    return (*funcp)(a0, a1, a2);
}

MCIERROR WINAPI fake_mciSendCommandW(MCIDEVICEID a0, UINT a1, DWORD a2, DWORD a3)
{
    static MCIERROR(WINAPI * funcp)(MCIDEVICEID a0, UINT a1, DWORD a2, DWORD a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciSendCommandW");
    return (*funcp)(a0, a1, a2, a3);
}

MCIERROR WINAPI fake_mciSendStringW(LPCWSTR a0, LPWSTR a1, UINT a2, HWND a3)
{
    static MCIERROR(WINAPI * funcp)(LPCWSTR a0, LPWSTR a1, UINT a2, HWND a3) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciSendStringW");
    return (*funcp)(a0, a1, a2, a3);
}

MCIDEVICEID WINAPI fake_mciGetDeviceIDA(LPCSTR a0)
{
    static MCIDEVICEID(WINAPI * funcp)(LPCSTR a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetDeviceIDA");
    return (*funcp)(a0);
}

MCIDEVICEID WINAPI fake_mciGetDeviceIDW(LPCWSTR a0)
{
    static MCIDEVICEID(WINAPI * funcp)(LPCWSTR a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetDeviceIDW");
    return (*funcp)(a0);
}

MCIDEVICEID WINAPI fake_mciGetDeviceIDFromElementIDA(DWORD a0, LPCSTR a1)
{
    static MCIDEVICEID(WINAPI * funcp)(DWORD a0, LPCSTR a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetDeviceIDFromElementIDA");
    return (*funcp)(a0, a1);
}

MCIDEVICEID WINAPI fake_mciGetDeviceIDFromElementIDW(DWORD a0, LPCWSTR a1)
{
    static MCIDEVICEID(WINAPI * funcp)(DWORD a0, LPCWSTR a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetDeviceIDFromElementIDW");
    return (*funcp)(a0, a1);
}

BOOL WINAPI fake_mciGetErrorStringA(MCIERROR a0, LPSTR a1, UINT a2)
{
    static BOOL(WINAPI * funcp)(MCIERROR a0, LPSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetErrorStringA");
    return (*funcp)(a0, a1, a2);
}

BOOL WINAPI fake_mciGetErrorStringW(MCIERROR a0, LPWSTR a1, UINT a2)
{
    static BOOL(WINAPI * funcp)(MCIERROR a0, LPWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetErrorStringW");
    return (*funcp)(a0, a1, a2);
}

BOOL WINAPI fake_mciSetYieldProc(MCIDEVICEID a0, YIELDPROC a1, DWORD a2)
{
    static BOOL(WINAPI * funcp)(MCIDEVICEID a0, YIELDPROC a1, DWORD a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciSetYieldProc");
    return (*funcp)(a0, a1, a2);
}

HTASK WINAPI fake_mciGetCreatorTask(MCIDEVICEID a0)
{
    static HTASK(WINAPI * funcp)(MCIDEVICEID a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetCreatorTask");
    return (*funcp)(a0);
}

YIELDPROC WINAPI fake_mciGetYieldProc(MCIDEVICEID a0, PDWORD a1)
{
    static YIELDPROC(WINAPI * funcp)(MCIDEVICEID a0, PDWORD a1) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciGetYieldProc");
    return (*funcp)(a0, a1);
}

BOOL WINAPI fake_mciExecute(LPCSTR a0)
{
    static BOOL(WINAPI * funcp)(LPCSTR a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciExecute");
    return (*funcp)(a0);
}

BOOL WINAPI fake_DriverCallback(DWORD a0, DWORD a1, HDRVR a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6)
{
    static BOOL(WINAPI * funcp)(DWORD a0, DWORD a1, HDRVR a2, DWORD a3, DWORD a4, DWORD a5, DWORD a6) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "DriverCallback");
    return (*funcp)(a0, a1, a2, a3, a4, a5, a6);
}

BOOL WINAPI fake_NotifyCallbackData(DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4)
{
    static BOOL(WINAPI * funcp)(DWORD a0, DWORD a1, DWORD a2, DWORD a3, DWORD a4) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "NotifyCallbackData");
    return (*funcp)(a0, a1, a2, a3, a4);
}

MMRESULT WINAPI fake_joyConfigChanged(DWORD a0)
{
    static MMRESULT(WINAPI * funcp)(DWORD a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "joyConfigChanged");
    return (*funcp)(a0);
}

BOOL WINAPI fake_mciFreeCommandResource(UINT a0)
{
    static BOOL(WINAPI * funcp)(UINT a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciFreeCommandResource");
    return (*funcp)(a0);
}

UINT WINAPI fake_mciLoadCommandResource(HANDLE a0, LPCWSTR a1, UINT a2)
{
    static UINT(WINAPI * funcp)(HANDLE a0, LPCWSTR a1, UINT a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mciLoadCommandResource");
    return (*funcp)(a0, a1, a2);
}

DWORD WINAPI fake_mmGetCurrentTask()
{
    static DWORD(WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmGetCurrentTask");
    return (*funcp)();
}

void WINAPI fake_mmTaskBlock(DWORD a0)
{
    static void (WINAPI * funcp)(DWORD a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmTaskBlock");
    return (*funcp)(a0);
}

typedef VOID(*LPTASKCALLBACK)(DWORD dwInst);

UINT WINAPI fake_mmTaskCreate(LPTASKCALLBACK a0, HANDLE* a1, DWORD_PTR a2)
{
    static UINT(WINAPI * funcp)(LPTASKCALLBACK a0, HANDLE * a1, DWORD_PTR a2) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmTaskCreate");
    return (*funcp)(a0, a1, a2);
}

BOOL WINAPI fake_mmTaskSignal(DWORD a0)
{
    static BOOL(WINAPI * funcp)(DWORD a0) = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmTaskSignal");
    return (*funcp)(a0);
}

void WINAPI fake_mmTaskYield()
{
    static void (WINAPI * funcp)() = NULL;
    if (funcp == NULL)
        funcp = (void*)GetProcAddress(load_real_dll(), "mmTaskYield");
    return (*funcp)();
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
        printf("Starting DB Shim...\n");
        patch_discord_sdk();
    }
    return TRUE;
}