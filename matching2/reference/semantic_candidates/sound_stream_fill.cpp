// 0x0044D110, 483 retail bytes: restore, refill, and pad a DirectSound buffer.
// Retail receives the stream in EAX and two stack arguments (RET 8). This
// explicit stdcall candidate has three arguments; native matching is pending.
#include "sound_wave_types.hpp"
#include "sound_memory_words.hpp"

typedef void (__stdcall* StreamSleep)(unsigned int);
typedef unsigned int (__stdcall* StreamSeekFile)(void*, int, int*, unsigned int);
extern "C" {
    extern StreamSleep g_stream_sleep;
    extern StreamSeekFile g_music_seek_file;
    extern unsigned int g_music_file_base;
}

extern "C" int __stdcall SoundStream_FillBuffer_0044d110(SoundStream* stream,
        WaveSecondaryBuffer* buffer, unsigned int repeat) {
    unsigned char* destination = 0;
    unsigned int locked_bytes = 0;
    unsigned int received = 0;
    if (!buffer)
        return static_cast<int>(0x800401f0u);

    unsigned int status;
    int result = buffer->methods->get_status(buffer, &status);
    if (result < 0)
        return result;
    if (status & 2) {
        StreamSleep sleep = g_stream_sleep;
        do {
            if (buffer->methods->restore(buffer) == static_cast<int>(0x88780096u))
                sleep(10);
            result = buffer->methods->restore(buffer);
        } while (result != 0);
    }
    result = buffer->methods->lock(buffer, 0, stream->buffer_bytes,
        &destination, &locked_bytes, 0, 0, 0);
    if (result < 0)
        return result;

    // The initial reset is inlined in retail. A missing file handle skips
    // seeking here; the subsequent read supplies the error instead.
    MusicReadCursor* reader = stream->reader;
    if (reader->buffered) {
        unsigned char* begin = reader->buffer_begin;
        MusicTrackRecord* record = reader->record;
        reader->position = begin;
        if (record->loop_end > 0)
            reader->memory_end = static_cast<unsigned int>(record->loop_end);
    } else {
        void* file = reader->file;
        if (file) {
            MusicTrackRecord* record = reader->record;
            g_music_seek_file(file, static_cast<int>(record->file_offset + g_music_file_base), 0, 0);
            reader->file_remaining = static_cast<unsigned int>(reader->record->loop_end);
        }
    }

    result = MusicCursor_Read_0044de10(stream->reader, locked_bytes, destination, &received);
    if (result < 0)
        return result;
    unsigned int total = received;
    if (total == 0) {
        unsigned char silence = stream->reader->record->format.bits_per_sample == 8 ? 0x80 : 0;
        FillSoundBytes(reinterpret_cast<unsigned int>(destination), locked_bytes, silence);
    } else if (total < locked_bytes) {
        if (repeat) {
            do {
                result = MusicCursor_Rewind_0044dd40(stream->reader, 0);
                if (result < 0)
                    return result;
                result = MusicCursor_Read_0044de10(stream->reader, locked_bytes - total,
                    reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(destination) + total), &received);
                if (result < 0)
                    return result;
                total += received;
                // No zero-progress guard: retail can repeat forever here.
            } while (total < locked_bytes);
        } else {
            unsigned char silence = stream->reader->record->format.bits_per_sample == 8 ? 0x80 : 0;
            FillSoundBytes(reinterpret_cast<unsigned int>(destination) + total, locked_bytes - total, silence);
        }
    }
    buffer->methods->unlock(buffer, destination, locked_bytes, 0, 0);
    return 0;
}
