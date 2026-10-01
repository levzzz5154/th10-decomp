// Compiler context only, never selected as game code.
#include "sound_wave_types.hpp"
#include "../../../src/platform/sound_worker.cpp"
#pragma code_seg(".text$05context")
extern "C" int __stdcall SoundEffectsContext(WaveSoundManager* manager, int count) {
    int sum = 0;
    for (int index = 0; index < count; ++index)
        sum += manager->InitializeEffects();
    return sum;
}
#pragma code_seg()
