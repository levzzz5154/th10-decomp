// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/platform_find_available.cpp"

#pragma code_seg(".text$03context")
WaveSecondaryBufferStatus* __stdcall PlatformFindAvailable0044D370CompilerContext(
        SoundBufferPool** states, int count) {
    WaveSecondaryBufferStatus* result = 0;
    while (count-- > 0)
        result = (*states++)->GetFreeBuffer();
    return result;
}
#pragma code_seg()
