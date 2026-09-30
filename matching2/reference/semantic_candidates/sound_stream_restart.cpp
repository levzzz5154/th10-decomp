// 0x0044DAD0, 213 retail bytes. Retail takes an EDI receiver and returns with
// plain RET. This explicit stdcall candidate awaits native ABI/byte matching.
#include "sound_wave_types.hpp"

typedef unsigned int (__stdcall* RestartSeekFile)(void*, int, int*, unsigned int);
extern "C" {
    extern RestartSeekFile g_music_seek_file;
    extern unsigned int g_music_file_base;
    int __stdcall SoundStream_FillBuffer_0044d110(SoundStream*, WaveSecondaryBuffer*, unsigned int);
}

extern "C" int __stdcall SoundStream_Restart_0044dad0(SoundStreamingState* stream) {
    // Retail dereferences the array before checking its first buffer.
    if (!stream->buffers[0] || !stream->reader)
        return static_cast<int>(0x800401f0u);
    stream->last_play_position = 0;
    stream->played_bytes = 0;
    stream->write_offset = 0;
    stream->end_of_stream = 0;

    unsigned int restored;
    int result = stream->buffers[0]->RestoreIfLost(&restored);
    if (result < 0)
        return result;
    if (restored) {
        result = SoundStream_FillBuffer_0044d110(stream, stream->buffers[0], 0);
        if (result < 0)
            return result;
    }

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
            g_music_seek_file(file, static_cast<int>(reader->record->file_offset + g_music_file_base), 0, 0);
            reader->file_remaining = static_cast<unsigned int>(reader->record->loop_end);
        }
    }
    WaveSecondaryBuffer* buffer = stream->buffers[0];
    return buffer->methods->set_position(buffer, 0);
}
