// 0x0044DD40 (194 bytes) and 0x0044DE10 (202 bytes): memory/file music cursor.
// Explicit stdcall candidates; retail uses ESI/AL for rewind and EAX/EDX plus
// two stack arguments for read. Native private-ABI matching is outstanding.
#include "sound_wave_types.hpp"
#include "sound_memory_words.hpp"

typedef unsigned int (__stdcall* CursorSeekFile)(void*, int, int*, unsigned int);
typedef int (__stdcall* CursorReadFile)(void*, void*, unsigned int, unsigned int*, void*);
extern "C" {
    extern CursorSeekFile g_music_seek_file;
    extern CursorReadFile g_music_read_file;
    extern unsigned int g_music_file_base;
}

extern "C" int __stdcall MusicCursor_Rewind_0044dd40(MusicReadCursor* cursor, unsigned char loop_start) {
    if (cursor->buffered) {
        unsigned int begin = reinterpret_cast<unsigned int>(cursor->buffer_begin);
        MusicTrackRecord* record = cursor->record;
        cursor->position = reinterpret_cast<unsigned char*>(begin);
        if (record->loop_end > 0)
            cursor->memory_end = static_cast<unsigned int>(record->loop_end);
        if (loop_start && record->loop_start > 0)
            cursor->position = reinterpret_cast<unsigned char*>(begin + static_cast<unsigned int>(record->loop_start));
        return 0;
    }
    void* file = cursor->file;
    if (!file)
        return static_cast<int>(0x800401f0u);
    if (loop_start) {
        MusicTrackRecord* record = cursor->record;
        if (record->loop_start > 0) {
            unsigned int offset = record->file_offset + static_cast<unsigned int>(record->loop_start) + g_music_file_base;
            g_music_seek_file(file, static_cast<int>(offset), 0, 0);
            record = cursor->record;
            cursor->file_remaining = static_cast<unsigned int>(record->loop_end) -
                static_cast<unsigned int>(record->loop_start);
            return 0;
        }
    }
    MusicTrackRecord* record = cursor->record;
    g_music_seek_file(file, static_cast<int>(record->file_offset + g_music_file_base), 0, 0);
    cursor->file_remaining = static_cast<unsigned int>(cursor->record->loop_end);
    return 0;
}

extern "C" int __stdcall MusicCursor_Read_0044de10(MusicReadCursor* cursor,
        unsigned int requested, unsigned char* destination, unsigned int* received) {
    if (cursor->buffered) {
        if (!cursor->position)
            return static_cast<int>(0x800401f0u);
        if (received)
            *received = 0;
        // Reload after clearing received: that output may alias cursor fields.
        unsigned int limit = cursor->memory_end;
        unsigned int begin = reinterpret_cast<unsigned int>(cursor->buffer_begin);
        unsigned int position = reinterpret_cast<unsigned int>(cursor->position);
        if (position + requested > begin + limit)
            requested = begin - position + limit;
        CopySoundWords(reinterpret_cast<unsigned int>(destination), position, requested);
        // The copy can itself overwrite the position field. Retail adds to
        // the current stored value, rather than to the earlier source pointer.
        cursor->position = reinterpret_cast<unsigned char*>(
            reinterpret_cast<unsigned int>(cursor->position) + requested);
        if (received)
            *received = requested;
        return 0;
    }
    void* file = cursor->file;
    if (!file)
        return static_cast<int>(0x800401f0u);
    if (!destination || !received)
        return static_cast<int>(0x80070057u);
    unsigned int remaining = cursor->file_remaining;
    if (requested > remaining)
        requested = remaining;
    cursor->file_remaining = remaining - requested;
    // Retail reuses the destination argument's stack slot as the API count
    // output. If ReadFile leaves it unwritten, the pointer bits are returned.
    unsigned int actual = reinterpret_cast<unsigned int>(destination);
    g_music_read_file(file, destination, requested, &actual, 0);
    *received = actual;
    return 0;
}
