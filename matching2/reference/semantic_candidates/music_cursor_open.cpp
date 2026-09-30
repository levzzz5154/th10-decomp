// 0x0044DBF0, 173 retail bytes. Retail receives ESI cursor, EAX mode, ECX
// filename and EDX music record, then plain RET. Explicit stdcall candidate.
#include "sound_wave_types.hpp"

typedef void* (__stdcall* MusicCreateFile)(const char*, unsigned int, unsigned int, void*, unsigned int, unsigned int, void*);
typedef unsigned int (__stdcall* MusicSeekFile)(void*, int, int*, unsigned int);
extern "C" {
    extern MusicCreateFile g_music_create_file;
    extern MusicSeekFile g_music_seek_file;
    extern unsigned int g_music_file_base;
}

extern "C" int __stdcall MusicCursor_Open_0044dbf0(MusicReadCursor* cursor, unsigned int mode,
        const char* filename, MusicTrackRecord* record) {
    cursor->open_mode = mode;
    cursor->buffered = 0;
    if (mode != 1)
        return 0;
    if (!filename)
        return static_cast<int>(0x80070057u);
    void* file = g_music_create_file(filename, 0x80000000u, 1, 0, 3, 0x08000080u, 0);
    cursor->file = file;
    if (file == reinterpret_cast<void*>(0xffffffffu))
        return static_cast<int>(0x80004005u);

    unsigned int buffered = cursor->buffered;
    cursor->record = record;
    // Although this function initially clears buffered, CreateFile callbacks
    // can change it before this branch. Retail tests the current flag.
    if (buffered) {
        cursor->position = cursor->buffer_begin;
        if (record->loop_end > 0)
            cursor->memory_end = static_cast<unsigned int>(record->loop_end);
    } else if (file) {
        g_music_seek_file(file, static_cast<int>(record->file_offset + g_music_file_base), 0, 0);
        cursor->file_remaining = static_cast<unsigned int>(cursor->record->loop_end);
    }
    cursor->total_pcm_bytes = cursor->file_remaining;
    return 0;
}
