// Unselected native ABI anchor from src/core/zwave/sound_stream_fill_model.cpp.
// Only the shared type view and placement section differ.
#include "th10/game/sound_stream_service.hpp"
#include <string.h>
#pragma intrinsic(memset)
#pragma code_seg(".text$01fill")
extern "C" __declspec(noinline) int __stdcall SoundStreamFill(SoundStream* stream,
        WaveBuffer* buffer, unsigned int repeat) {
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
    MusicCursor* reader = stream->reader;
    if (reader->buffered) {
        reader->position = reader->base;
        if (reader->record->end > 0)
            reader->memory_end = static_cast<unsigned int>(reader->record->end);
    } else {
        void* file = reader->file;
        if (file) {
            MusicRecord* record = reader->record;
            imp_SetFilePointer(file, static_cast<int>(record->offset + g_bgm_data_offset), 0, 0);
            reader->remaining = static_cast<unsigned int>(reader->record->end);
        }
    }

    result = ArchiveRead(stream->reader, locked_bytes, (unsigned int)destination, &received);
    if (result < 0)
        return result;
    unsigned int total = received;
    if (total == 0) {
        unsigned char silence = stream->reader->record->bits == 8 ? 0x80 : 0;
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
            unsigned char silence = stream->reader->record->bits == 8 ? 0x80 : 0;
            memset((void*)((unsigned int)destination + total), silence, locked_bytes - total);
        }
    }
    buffer->methods->unlock(buffer, destination, locked_bytes, 0, 0);
    return 0;
}

#pragma code_seg()
