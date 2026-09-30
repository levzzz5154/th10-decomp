// Complete segment-servicing routine: 0x0044D850 (413 bytes) and 0x0044D9F0
// (221 bytes). Retail and candidate both take two stdcall stack arguments.
// Callee private ABIs and native MSVC bytes still require matching.
#include "sound_wave_types.hpp"
#include "sound_memory_words.hpp"

extern "C" int __stdcall SoundStream_FillBuffer_0044d110(SoundStream*, WaveSecondaryBuffer*, unsigned int);

extern "C" int __stdcall SoundStream_Service_0044d850(SoundStreamingState* stream, unsigned int repeat) {
    if (!stream->buffers || !stream->reader)
        return static_cast<int>(0x800401f0u);

    unsigned int initial_play_position;
    unsigned int write_position;
    WaveSecondaryBuffer* buffer = stream->buffers[0];
    buffer->methods->get_position(buffer, &initial_play_position, &write_position);
    if (stream->write_offset >= write_position - stream->segment_bytes && stream->write_offset < write_position)
        return static_cast<int>(0x800401f0u);

    unsigned int received;
    int result = stream->buffers[0]->RestoreIfLost(&received);
    if (result < 0)
        return result;
    if (received) {
        result = SoundStream_FillBuffer_0044d110(stream, stream->buffers[0], 0);
        return result < 0 ? result : 0;
    }

    unsigned char* destination = 0;
    unsigned char* second = 0;
    // Retail reuses its stream argument's stack slot as Lock's first count
    // output; an unwritten output therefore retains the stream pointer bits.
    unsigned int locked_bytes = reinterpret_cast<unsigned int>(stream);
    unsigned int second_bytes;
    buffer = stream->buffers[0];
    result = buffer->methods->lock(buffer, stream->write_offset, stream->segment_bytes,
        &destination, &locked_bytes, &second, &second_bytes, 0);
    if (result < 0)
        return result;
    if (second)
        return static_cast<int>(0x8000ffffu);

    if (stream->end_of_stream) {
        unsigned char silence = stream->reader->record->format.bits_per_sample == 8 ? 0x80 : 0;
        FillSoundBytes(reinterpret_cast<unsigned int>(destination), locked_bytes, silence);
    } else {
        result = MusicCursor_Read_0044de10(stream->reader, locked_bytes, destination, &received);
        if (result < 0)
            return result;
        unsigned int total = received;
        if (total < locked_bytes) {
            if (repeat) {
                do {
                    result = MusicCursor_Rewind_0044dd40(stream->reader, 1);
                    if (result < 0)
                        return result;
                    result = MusicCursor_Read_0044de10(stream->reader, locked_bytes - total,
                        reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(destination) + total), &received);
                    if (result < 0)
                        return result;
                    total += received;
                } while (total < locked_bytes);
            } else {
                unsigned char silence = stream->reader->record->format.bits_per_sample == 8 ? 0x80 : 0;
                FillSoundBytes(reinterpret_cast<unsigned int>(destination) + total, locked_bytes - total, silence);
                stream->end_of_stream = 1;
            }
        }
    }
    buffer = stream->buffers[0];
    buffer->methods->unlock(buffer, destination, locked_bytes, 0, 0);
    buffer = stream->buffers[0];
    unsigned int play_position;
    result = buffer->methods->get_position(buffer, &play_position, 0);
    if (result < 0)
        return result;

    unsigned int previous = stream->last_play_position;
    unsigned int advanced = play_position < previous ?
        stream->buffer_bytes - previous + play_position : play_position - previous;
    unsigned int played = stream->played_bytes + advanced;
    stream->last_play_position = play_position;
    stream->played_bytes = played;
    if (stream->end_of_stream && played >= stream->reader->total_pcm_bytes) {
        buffer = stream->buffers[0];
        buffer->methods->stop(buffer);
    }
    // Stop can change both operands; reload them after the callback.
    stream->write_offset = (stream->write_offset + locked_bytes) % stream->buffer_bytes;
    return 0;
}
