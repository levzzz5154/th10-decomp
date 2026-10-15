#include "sound_wave_types.hpp"
typedef void (__stdcall* StreamSleep)(unsigned int);
extern "C" { extern StreamSleep imp_Sleep; extern unsigned int g_bgm_data_offset; extern unsigned int (__stdcall* imp_SetFilePointer)(void*,int,int*,unsigned int); __declspec(dllimport) int __stdcall ReadFile(void*,void*,unsigned int,unsigned int*,void*); }
extern "C" __declspec(noinline) int __stdcall ArchiveRead(MusicReadCursor*,unsigned int,unsigned int,unsigned int*);
extern "C" __declspec(noinline) int __stdcall ArchiveRewind(MusicReadCursor*,bool);

#include <string.h>
#pragma intrinsic(memset)
#pragma code_seg(".text$03fill")
extern "C" __declspec(noinline) int __stdcall SoundStreamFill(SoundStream* stream,
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
        StreamSleep sleep = imp_Sleep;
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
        reader->position = reader->buffer_begin;
        if (reader->record->loop_end > 0)
            reader->memory_end = static_cast<unsigned int>(reader->record->loop_end);
    } else {
        void* file = reader->file;
        if (file) {
            MusicTrackRecord* record = reader->record;
            imp_SetFilePointer(file, static_cast<int>(record->file_offset + g_bgm_data_offset), 0, 0);
            reader->file_remaining = static_cast<unsigned int>(reader->record->loop_end);
        }
    }

    result = ArchiveRead(stream->reader, locked_bytes, (unsigned int)destination, &received);
    if (result < 0)
        return result;
    unsigned int total = received;
    if (total == 0) {
        unsigned char silence = stream->reader->record->format.bits_per_sample == 8 ? 0x80 : 0;
        memset(destination, silence, locked_bytes);
    } else if (total < locked_bytes) {
        if (repeat) {
            do {
                result = ArchiveRewind(stream->reader, 0);
                if (result < 0)
                    return result;
                unsigned int remaining = locked_bytes - total;
                result = ArchiveRead(stream->reader, remaining, (unsigned int)destination + total, &received);
                if (result < 0)
                    return result;
                total += received;
                // No zero-progress guard: retail can repeat forever here.
            } while (total < locked_bytes);
        } else {
            unsigned char silence = stream->reader->record->format.bits_per_sample == 8 ? 0x80 : 0;
            memset((void*)((unsigned int)destination + total), silence, locked_bytes - total);
        }
    }
    buffer->methods->unlock(buffer, destination, locked_bytes, 0, 0);
    return 0;
}

#pragma code_seg()
