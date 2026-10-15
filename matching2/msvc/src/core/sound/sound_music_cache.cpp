// 0x0043D7D0: read one track of the music file into a memory slot.
//
// A slot that already holds the named track is left alone. Otherwise the name
// is recorded in the global manager's slot table, and, when music is enabled
// and a sound device exists, the track's bytes are read whole from the music
// file into a fresh buffer. Returns -1 when the file cannot be opened or the
// buffer cannot be allocated, otherwise 0. The manager arrives in ESI and the
// name in EAX.
//
// The name is copied with source and destination declared in this order, and
// the track size is read through an inline accessor: as a call argument it is
// evaluated ahead of the other ReadFile arguments, which is what gives retail
// its register order there.
#include "../../../build_support/layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include "th10/app/supervisor.hpp"
#include <string.h>
#pragma intrinsic(strcmp)

extern "C" {
extern WaveSoundManager g_wave_sound_manager;
__declspec(dllimport) void* __stdcall CreateFileA(const char* name, unsigned int access,
    unsigned int share, void* security, unsigned int disposition, unsigned int flags,
    void* template_file);
__declspec(dllimport) unsigned int __stdcall SetFilePointer(void* file, int distance,
    int* distance_high, unsigned int method);
__declspec(dllimport) int __stdcall ReadFile(void* file, void* buffer, unsigned int bytes,
    unsigned int* received, void* overlapped);
__declspec(dllimport) int __stdcall CloseHandle(void* handle);
void* __cdecl asm_malloc_00452706(unsigned int bytes);
void __cdecl asm_free_00452422(void* memory);
}

// 0x0043D2A0: index of the track whose name is the path's basename.
struct PathName {
    int FindBasenameSlot(void* owner);
};

// The byte count of a track of the loaded music table.
static inline unsigned int TrackBytes(WaveSoundManager* manager, int index) {
    return reinterpret_cast<MusicTrackRecord*>(manager->loaded_music_data)[index].data_bytes;
}

#pragma code_seg(".text$03cache")
int WaveSoundManager::CacheMusic(int slot, const char* name) {
    if (cached_music_data[slot] && strcmp(name, cached_music_names[slot]) == 0)
        return 0;

    const char* source = name;
    char* destination = g_wave_sound_manager.cached_music_names[slot];
    while ((*destination++ = *source++) != 0)
        ;

    if (!(g_supervisor.flags & 0x10))
        return 0;
    if (!device_owner)
        return 0;

    if (cached_music_data[slot]) {
        asm_free_00452422(cached_music_data[slot]);
        cached_music_data[slot] = 0;
    }
    void* file = CreateFileA(music_file_name, 0x80000000, 1, 0, 3, 0x08000080, 0);
    if (file == reinterpret_cast<void*>(-1))
        return -1;

    int index = reinterpret_cast<PathName*>(const_cast<char*>(name))
        ->FindBasenameSlot(this);
    SetFilePointer(file, reinterpret_cast<MusicTrackRecord*>(loaded_music_data)[index].file_offset,
        0, 0);
    unsigned char* data =
        static_cast<unsigned char*>(asm_malloc_00452706(TrackBytes(this, index)));
    if (!data) {
        CloseHandle(file);
        return -1;
    }
    unsigned int received;
    ReadFile(file, data, TrackBytes(this, index), &received, 0);
    CloseHandle(file);

    cached_music_records[slot] = &reinterpret_cast<MusicTrackRecord*>(loaded_music_data)[index];
    cached_music_data[slot] = data;
    music_read_cursors[slot] = data;
    music_remaining_bytes[slot] = cached_music_records[slot]->data_bytes;
    return 0;
}
#pragma code_seg()
