// 0x0044CE80: construct a streaming sound over a set of sound buffers. The
// buffer pointers are copied, the first buffer is filled from the reader and
// every buffer is rewound. Native LTCG passes the stream in ESI, the buffer
// count in EDI and the source array in EAX.
#include "th10/game/sound_stream_fill_model.hpp"

void* __cdecl operator new(unsigned int size);
extern "C" __declspec(noinline) int __stdcall SoundStreamFill(SoundStream* stream,
        WaveBuffer* buffer, unsigned int repeat);
// The streaming sound's dispatch table.
extern "C" void* data_004705d8;

#pragma code_seg(".text$00construct")
extern "C" __declspec(noinline) SoundStreamState* __stdcall SoundStream_Construct_0044ce80(
        SoundStreamState* stream, WaveBuffer** buffers, unsigned int count,
        unsigned int buffer_bytes, MusicCursor* reader) {
    stream->methods = &data_004705d8;
    stream->buffers = new WaveBuffer*[count];
    unsigned int i;
    for (i = 0; i < count; ++i)
        stream->buffers[i] = buffers[i];
    stream->buffer_bytes = buffer_bytes;
    stream->buffer_count = count;
    stream->reader = reader;
    SoundStreamFill(stream, stream->buffers[0], 0);
    for (i = 0; i < count; ++i)
        stream->buffers[i]->methods->set_current_position(stream->buffers[i], 0);
    stream->last_play_position = 0;
    return stream;
}
#pragma code_seg()
