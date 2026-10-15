// Compiler context only; never selected as recovered game code.
#include "../../../src/core/sound/sound_worker.cpp"

#pragma code_seg(".text$03context")
int __stdcall SoundWorkerCompilerContext(SoundWorkerPair** states, int count) {
    SoundWorkerPair* state = *states;
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result += state->Stop();
    }
    return result;
}
#pragma code_seg()
