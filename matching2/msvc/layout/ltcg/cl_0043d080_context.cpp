// Compiler context only; never selected as recovered game code.
#include "../../src/platform/sound_preload_worker_0043d080.cpp"
#include "../../src/platform/fun_0044b360_0044b360.cpp"
#include "../../src/platform/text_log.cpp"

typedef void (__cdecl* ThreadRoutine)();

#pragma code_seg(".text$90context")
int __stdcall SoundPreloadContext_0043d080(ThreadRoutine* routine) {
    // The worker is only started through its address.
    *routine = Sound_PreloadWorker_0043d080;
    return 0;
}
#pragma code_seg()
