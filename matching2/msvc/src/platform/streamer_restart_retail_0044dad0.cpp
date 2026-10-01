// 0x0044DAD0, complete 213-byte restart. Native LTCG passes the stream in
// EDI and emits plain RET; the exported spelling records the source prototype.
#include "th10/game/sound_start_context.hpp"
#include "../../layout/ltcg/sound_restart_dependencies/sound_wave_types.hpp"

typedef unsigned int (__stdcall* RestartSeekFile)(void*, int, int*, unsigned int);
extern "C" {
    extern RestartSeekFile data_004660c8;
    extern unsigned int data_004977a4;
}

#pragma code_seg(".text$07restart")
extern "C" __declspec(noinline) int __stdcall SoundStream_Restart_0044dad0(SoundStreamingState* stream) {
    // Retail dereferences the array before checking its first buffer.
    if (!stream->buffers[0] || !stream->reader)
        return static_cast<int>(0x800401f0u);
    stream->last_play_position = 0;
    stream->played_bytes = 0;
    stream->write_offset = 0;
    stream->end_of_stream = 0;

    unsigned int restored;
    int result = reinterpret_cast<PlatformD300Entry*>(stream->buffers[0])->Run(&restored);
    if (result < 0)
        return result;
    if (restored) {
        result = SoundStreamFill(reinterpret_cast<SoundStream*>(stream), reinterpret_cast<WaveBuffer*>(stream->buffers[0]), 0);
        if (result < 0)
            return result;
    }

    // Use the existing native cursor view. Reload it after restore/refill,
    // since callbacks can replace the stream reader and its metadata.
    MusicCursor* reader = reinterpret_cast<MusicCursor*>(stream->reader);
    if (reader->buffered) {
        unsigned char* begin = reader->base;
        MusicRecord* record = reader->record;
        reader->position = begin;
        if (record->end > 0)
            reader->memory_end = static_cast<unsigned int>(record->end);
    } else {
        void* file = reader->file;
        if (file) {
            data_004660c8(file, static_cast<int>(reader->record->offset + data_004977a4), 0, 0);
            reader->remaining = static_cast<unsigned int>(reader->record->end);
        }
    }
    WaveSecondaryBuffer* buffer = stream->buffers[0];
    return buffer->methods->set_position(buffer, 0);
}

#pragma code_seg()
