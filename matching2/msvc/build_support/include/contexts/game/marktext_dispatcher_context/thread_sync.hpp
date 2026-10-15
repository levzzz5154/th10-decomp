#pragma once
#include <stddef.h>

struct CriticalSection { unsigned char storage[24]; };

// GameMain initializes seven contiguous Win32 critical sections at 0x492274.
// The scheduler uses the first section and the depth byte immediately after them.
struct ThreadSynchronization {
    CriticalSection critical_sections[7];
    unsigned char scheduler_lock_depth;
};
extern ThreadSynchronization g_thread_synchronization;

typedef char ThreadSynchronization_depth_offset_must_be_168[
    offsetof(ThreadSynchronization, scheduler_lock_depth) == 168 ? 1 : -1];

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection*);
__declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection*);
}
