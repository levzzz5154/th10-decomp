// 0x0043CC40 is already maintained C++. This typed behavioral candidate makes
// retail import capture explicit for callback/reentrancy comparisons. Retail
// receives ESI; this candidate has a one-argument stdcall/RET 4 interface.
#include "sound_wave_types.hpp"

typedef unsigned int (__stdcall* PreloadWait)(void*, unsigned int);
typedef void (__stdcall* PreloadSleep)(unsigned int);
typedef int (__stdcall* PreloadClose)(void*);
extern "C" {
    extern PreloadWait g_sound_wait_for_object;
    extern PreloadSleep g_sound_sleep;
    extern PreloadClose g_sound_close_handle;
}

extern "C" int __stdcall Sound_StopPreloadWorkers_0043cc40(WaveSoundManager* manager) {
    void* first = manager->first_sound_worker;
    if (!first)
        return 0;
    if (!manager->preload_stop_requested)
        manager->preload_stop_requested = 1;
    const PreloadWait wait = g_sound_wait_for_object;
    unsigned int result = wait(first, 100);
    // The first Wait callback precedes capture of Sleep. Both imports then
    // remain cached across both loops, while their handle arguments reload.
    const PreloadSleep sleep = g_sound_sleep;
    while (result == 0x102) {
        sleep(1);
        result = wait(manager->first_sound_worker, 100);
    }
    result = wait(manager->second_sound_worker, 100);
    while (result == 0x102) {
        sleep(1);
        result = wait(manager->second_sound_worker, 100);
    }
    const PreloadClose close = g_sound_close_handle;
    close(manager->first_sound_worker);
    close(manager->second_sound_worker);
    manager->first_sound_worker = 0;
    manager->second_sound_worker = 0;
    return 0;
}
