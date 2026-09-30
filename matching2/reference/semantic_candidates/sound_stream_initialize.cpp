// Complete initializers: 0x0044CE80 (118 bytes) and 0x0044D6A0 (109 bytes).
// Retail uses private EAX/ESI/EDI plus two stack args for the array initializer,
// and ESI plus four stack args for the streaming constructor. Explicit stdcall
// candidates preserve behavior but still need native ABI and byte matching.
#include "sound_wave_types.hpp"

extern "C" {
    void* __cdecl SoundBuffer_Allocate(unsigned int bytes);
    extern SoundStreamMethods g_sound_base_methods;
    extern SoundStreamMethods g_sound_streaming_methods;
    int __stdcall SoundStream_FillBuffer_0044d110(SoundStream*, WaveSecondaryBuffer*, unsigned int);
}

extern "C" SoundStream* __stdcall SoundStream_InitializeArray_0044ce80(SoundStream* stream,
        WaveSecondaryBuffer** source, unsigned int count, unsigned int bytes, MusicReadCursor* reader) {
    stream->methods = &g_sound_base_methods;
    stream->buffers = static_cast<WaveSecondaryBuffer**>(SoundBuffer_Allocate(count * 4));
    for (unsigned int index = 0; index < count; ++index) {
        // Copy one pointer at a time, loading the source before reloading the
        // destination array. Source/destination can overlap the stream itself.
        WaveSecondaryBuffer* value = reinterpret_cast<WaveSecondaryBuffer* volatile*>(source)[index];
        WaveSecondaryBuffer** destination = static_cast<volatile SoundStream*>(stream)->buffers;
        reinterpret_cast<WaveSecondaryBuffer* volatile*>(destination)[index] = value;
    }
    stream->buffer_bytes = bytes;
    stream->buffer_count = count;
    stream->reader = reader;
    // Even a zero count reads the first allocated slot. Neither the allocation
    // nor the refill/position return values are checked.
    SoundStream_FillBuffer_0044d110(stream, stream->buffers[0], 0);
    for (unsigned int index = 0; index < count; ++index) {
        WaveSecondaryBuffer* buffer = stream->buffers[index];
        buffer->methods->set_position(buffer, 0);
    }
    stream->playing = 0;
    return stream;
}

extern "C" SoundStreamingState* __stdcall SoundStream_InitializeSingle_0044d6a0(SoundStreamingState* stream,
        WaveSecondaryBuffer* buffer, unsigned int bytes, MusicReadCursor* reader, unsigned int segment_bytes) {
    stream->methods = &g_sound_base_methods;
    stream->buffers = static_cast<WaveSecondaryBuffer**>(SoundBuffer_Allocate(4));
    stream->buffers[0] = buffer;
    stream->reader = reader;
    stream->buffer_bytes = bytes;
    stream->buffer_count = 1;
    SoundStream_FillBuffer_0044d110(stream, stream->buffers[0], 0);
    buffer = stream->buffers[0];
    buffer->methods->set_position(buffer, 0);
    stream->playing = 0;
    stream->last_play_position = 0;
    stream->played_bytes = 0;
    stream->write_offset = 0;
    stream->end_of_stream = 0;
    stream->methods = &g_sound_streaming_methods;
    stream->segment_bytes = segment_bytes;
    return stream;
}
