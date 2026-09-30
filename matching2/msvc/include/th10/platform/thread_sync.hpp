#pragma once
#include <stddef.h>

struct CriticalSection { unsigned char storage[24]; };

// GameMain initializes seven contiguous Win32 critical sections at 0x492274,
// each with a nesting-depth byte after the array. The scheduler uses the first
// section and the text log the fourth.
struct ThreadSynchronization {
    CriticalSection critical_sections[7];
    unsigned char scheduler_lock_depth;     // depth of critical_sections[0]
    unsigned char lock_depth_1;
    unsigned char lock_depth_2;
    unsigned char text_log_lock_depth;      // depth of critical_sections[3]
};
extern ThreadSynchronization g_thread_synchronization;

typedef char ThreadSynchronization_depth_offset_must_be_168[
    offsetof(ThreadSynchronization, scheduler_lock_depth) == 168 ? 1 : -1];

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection*);
__declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection*);
}
