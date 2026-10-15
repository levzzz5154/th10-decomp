// 0x0043CC40: stop both sound worker threads and close their handles.
//
// Retail receives the owning platform object in ESI and always returns 0:
//
//   L_0043cc40: mov   eax,[esi+5218h]  ; first worker thread handle
//               test  eax,eax
//               je    L_0043ccec        ; no worker running: report success
//               mov   ecx,[esi+5224h]   ; shutdown flag
//               test  ecx,ecx
//               jne   L_0043cc62
//               mov   dword ptr [esi+5224h],1
//   L_0043cc62: push  ebx / push edi
//               ... two "wait for the thread, sleeping a millisecond"
//               loops, then CloseHandle on both and clear the handles.
//
// The body is compiled in the native LTCG cluster of
// layout/ltcg/sound_worker.json, whose synthetic caller keeps the object
// pointer live in ESI across both wait loops.

typedef void* HANDLE;
typedef unsigned long DWORD;
typedef int BOOL;

extern "C" {
__declspec(dllimport) DWORD __stdcall WaitForSingleObject(HANDLE handle, DWORD milliseconds);
__declspec(dllimport) void __stdcall Sleep(DWORD milliseconds);
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);
}

// WAIT_TIMEOUT: the object stayed unsignalled for the whole wait.
static const DWORD kSoundWorkerWaitTimeout = 0x102;

struct SoundWorkerPair_0043cc40 {
    unsigned char reserved_00[0x5218];
    HANDLE first_thread;        // +0x5218
    HANDLE second_thread;       // +0x521C
    unsigned int reserved_5220; // +0x5220
    int stop_requested;         // +0x5224

    __declspec(noinline) int Stop();
};

#pragma code_seg(".text$01stop")
int SoundWorkerPair_0043cc40::Stop() {
    if (first_thread == 0) {
        return 0;
    }
    if (stop_requested == 0) {
        stop_requested = 1;
    }
    while (WaitForSingleObject(first_thread, 100) == kSoundWorkerWaitTimeout) {
        Sleep(1);
    }
    while (WaitForSingleObject(second_thread, 100) == kSoundWorkerWaitTimeout) {
        Sleep(1);
    }
    CloseHandle(first_thread);
    CloseHandle(second_thread);
    first_thread = 0;
    second_thread = 0;
    return 0;
}
#pragma code_seg()
