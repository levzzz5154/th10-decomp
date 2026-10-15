#pragma once


// 0x0042ADD0: maintained in src/game/score/score_settings_initialize_defaults_0042add0.cpp.


// 0x00447280..0x004472D1: Recovery_LoadCachedResource
// Return the resource cached for the given index, loading it through 0x004470C0
// when the slot is still empty. The load runs on a worker thread: the entry is
// flagged busy (+0x124) and this side waits a millisecond at a time until the
// worker clears the flag. A progress byte with its sign bit set at 0x00491FF4
// aborts the wait. The index arrives in ECX and the cache table in EDX, with the
// resource name on the stack, matching the retail __fastcall layout.
struct CachedResource {
    unsigned char unknown_000[0x124];
    int busy;                    // +0x124, one while a loader still owns the entry
};

typedef CachedResource* (__stdcall* ResourceLoadFn)(void* owner, int index, const char* name);
// kernel32!Sleep through the import slot the image keeps, loaded once.
typedef void (__stdcall* SleepFn)(unsigned long milliseconds);

