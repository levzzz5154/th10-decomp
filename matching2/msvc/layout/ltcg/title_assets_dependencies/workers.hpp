#pragma once
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

