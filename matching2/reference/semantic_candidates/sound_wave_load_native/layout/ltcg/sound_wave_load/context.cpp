// Synthetic compiler caller only; not selected as recovered game code.
#include "../../../src/platform/sound_wave_load.cpp"
#include "chunks.cpp"
#include "log.cpp"
#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) int __stdcall SoundWaveLoadContext(WaveSoundManager* manager, int* indices, const char** files, int count) {
    int result = 0;
    while (count--) result |= SoundWave_LoadPending_0043d390(*indices++, manager, *files++);
    return result;
}
#pragma code_seg()
