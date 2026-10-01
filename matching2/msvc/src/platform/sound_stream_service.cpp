// 0x0044D850..0x0044DACC: service one streaming sound notification.
#include "th10/game/sound_stream_service.hpp"
#include <string.h>
#pragma intrinsic(memset)
extern "C" __declspec(noinline) int __stdcall SoundStreamFill(SoundStream*, WaveBuffer*, unsigned int);
#pragma code_seg(".text$05service")
extern "C" __declspec(noinline) int __stdcall SoundStream_Service_0044d850(
        SoundStreamState* stream, unsigned int repeat) {
    if (!stream->buffers || !stream->reader)
        return static_cast<int>(0x800401f0u);

    unsigned int initial_play_position;
    unsigned int write_position;
    WaveBuffer* buffer = stream->buffers[0];
    buffer->methods->get_position(buffer, &initial_play_position, &write_position);
    if (stream->write_offset >= write_position - stream->notify_bytes
            && stream->write_offset < write_position)
        return static_cast<int>(0x800401f0u);

    unsigned int restored;
    int result = reinterpret_cast<PlatformD300Entry*>(stream->buffers[0])->Run(&restored);
    if (result < 0)
        return result;
    if (restored) {
        result = SoundStreamFill(stream, stream->buffers[0], 0);
        return result < 0 ? result : 0;
    }

    unsigned char* destination = 0;
    unsigned char* second = 0;
    // Native compilation reuses the incoming stream stack slot for this count.
    // Leave it uninitialized, matching the output-only DirectSound contract.
    unsigned int locked_bytes;
    unsigned int second_bytes;
    result = stream->buffers[0]->methods->lock(stream->buffers[0],
        stream->write_offset, stream->notify_bytes,
        &destination, &locked_bytes, &second, &second_bytes, 0);
    if (result < 0)
        return result;
    if (second)
        return static_cast<int>(0x8000ffffu);

    unsigned int received;
    if (!stream->end_of_stream) {
        result = ArchiveRead(stream->reader, locked_bytes, reinterpret_cast<unsigned int>(destination), &received);
        if (result < 0) return result;
    } else {
        memset(destination,
            static_cast<unsigned char>(stream->reader->record->bits == 8 ? 0x80 : 0), locked_bytes);
        received = locked_bytes;
    }
    // A silent segment is already full. Keeping the short-read decision here
    // also preserves the native branch layout and aligned loop at 0x0044D9F0.
    if (received < locked_bytes) {
        if (!repeat) {
            memset(destination + received,
                static_cast<unsigned char>(stream->reader->record->bits == 8 ? 0x80 : 0),
                locked_bytes - received);
            stream->end_of_stream = 1;
        } else {
            unsigned int total = received;
            // Retail repeats until full, including its zero-progress behavior.
            while (total < locked_bytes) {
                result = ArchiveRewind(stream->reader, 1);
                if (result < 0) return result;
                unsigned int remaining = locked_bytes - total;
                result = ArchiveRead(stream->reader, remaining,
                    reinterpret_cast<unsigned int>(destination) + total, &received);
                if (result < 0) return result;
                total += received;
            }
        }
    }
    stream->buffers[0]->methods->unlock(stream->buffers[0], destination, locked_bytes, 0, 0);
    unsigned int play_position;
    result = stream->buffers[0]->methods->get_position(stream->buffers[0], &play_position, 0);
    if (result < 0)
        return result;

    unsigned int advanced;
    if (play_position < stream->previous_play_position)
        advanced = stream->buffer_bytes - stream->previous_play_position + play_position;
    else
        advanced = play_position - stream->previous_play_position;
    stream->played_bytes += advanced;
    stream->previous_play_position = play_position;
    if (stream->end_of_stream) {
        if (stream->played_bytes >= stream->reader->total_pcm_bytes)
            stream->buffers[0]->methods->stop(stream->buffers[0]);
    }
    // Stop can change both operands; reload them after the callback.
    stream->write_offset += locked_bytes;
    stream->write_offset %= stream->buffer_bytes;
    return 0;
}

#pragma code_seg()
