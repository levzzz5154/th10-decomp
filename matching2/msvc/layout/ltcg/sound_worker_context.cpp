// Compiler context only; never selected as recovered game code.
#include "../../src/platform/sound_worker.cpp"

#pragma code_seg(".text$03context")
int __stdcall SoundWorkerCompilerContext(SoundWorkerPair_0043cc40** states, int count) {
    SoundWorkerPair_0043cc40* state = *states;
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result += state->Stop();
    }
    return result;
}
#pragma code_seg()
