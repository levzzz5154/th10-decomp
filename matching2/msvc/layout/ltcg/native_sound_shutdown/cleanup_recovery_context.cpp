// Compiler caller only; not selected as recovered game code.
#include "th10/platform/native_sound_shutdown.hpp"
#include "../../../src/platform/midi_worker_stop.cpp"
#pragma code_seg(".text$a06context")
extern "C" __declspec(noinline) int __stdcall SoundCleanupContext(WaveSoundManager** managers, int count) {
    int result = 0;
    while (count--) result |= (*managers++)->Cleanup();
    return result;
}
#pragma code_seg()
