// Compiler context only; never selected as recovered game code.
#include "../../../../src/core/zwave/sound_stream_construct_0044ce80.cpp"
#include "../../../../src/core/zwave/sound_stream_fill_model.cpp"
#include "../sound_fill_read.cpp"
#include "../sound_fill_rewind.cpp"

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) int __stdcall SoundStreamConstructContext(SoundStreamState** streams,
        WaveBuffer*** buffers, unsigned int* counts, unsigned int bytes, MusicCursor* reader, int count) {
    int result = 0;
    while (count--)
        result += SoundStream_Construct_0044ce80(*streams++, *buffers++, *counts++, bytes, reader) != 0;
    return result;
}
#pragma code_seg()
