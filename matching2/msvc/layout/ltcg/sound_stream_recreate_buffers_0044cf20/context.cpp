// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/sound_stream_recreate_buffers_0044cf20.cpp"

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) int __stdcall SoundStreamRecreateContext(SoundStreamState** streams, int count) {
    int result = 0;
    while (count--)
        result |= SoundStream_RecreateBuffers_0044cf20(*streams++);
    return result;
}
#pragma code_seg()
