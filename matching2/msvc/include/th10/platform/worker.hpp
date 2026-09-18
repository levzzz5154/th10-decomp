#pragma once
#include <stddef.h>

typedef unsigned int (__stdcall *PlatformWorkerEntry)(void*);

// Retail worker representation. StopNoDelete installs the base dispatch table
// before stopping the thread; the deleting destructor is a separate function.
struct PlatformWorker {
    const void* vtable;                // +0x00
    void* thread;                      // +0x04
    unsigned int thread_id;            // +0x08
    unsigned int stop_requested;       // +0x0c
    unsigned int running;              // +0x10
    unsigned int reserved_14;
    PlatformWorkerEntry entry;         // +0x18

    __declspec(noinline) void Start(void* context, PlatformWorkerEntry start);
    void StopNoDelete();
    void Stop();
    PlatformWorker* Destroy(unsigned int should_free);
};

typedef char PlatformWorker_entry_offset_must_be_24[
    offsetof(PlatformWorker, entry) == 0x18 ? 1 : -1];

extern char platform_worker_vtable;

extern "C" {
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*, unsigned long);
__declspec(dllimport) void __stdcall Sleep(unsigned long);
__declspec(dllimport) int __stdcall CloseHandle(void*);
}
