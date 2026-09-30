// Behavioral recovery of 0x0043D7D0, 369 bytes. Retail takes the requested
// name in EAX, manager in ESI and slot on the stack (RET 4).
#include "sound_wave_types.hpp"

// Same source-level interface as the maintained basename lookup in path.cpp.
struct PathName_0043d2a0 {
    char text[1];
    int FindBasenameSlot_0043d2a0(void* owner);
};

typedef void* (__stdcall* MusicCreateFile)(const char*, unsigned int, unsigned int,
    void*, unsigned int, unsigned int, void*);
typedef unsigned int (__stdcall* MusicSeekFile)(void*, int, int*, unsigned int);
typedef int (__stdcall* MusicReadFile)(void*, void*, unsigned int, unsigned int*, void*);
typedef int (__stdcall* MusicCloseFile)(void*);
extern "C" {
    extern WaveSoundManager g_wave_sound_manager;
    extern volatile unsigned char g_sound_mode_flags;
    extern MusicCreateFile g_music_create_file;
    extern MusicSeekFile g_music_seek_file;
    extern MusicReadFile g_music_read_file;
    extern MusicCloseFile g_music_close_file;
    void* __cdecl asm_malloc_00452706(unsigned int);
    void __cdecl entry_free_00452422(void*);
}

namespace {
// Retail slots are unchecked and address calculations wrap at 32 bits.
template<class T> T& Slot(T* first, int index) {
    unsigned int address = reinterpret_cast<unsigned int>(first) +
        static_cast<unsigned int>(index) * sizeof(T);
    return *reinterpret_cast<T*>(address);
}

char* SlotName(WaveSoundManager* manager, int index) {
    unsigned int address = reinterpret_cast<unsigned int>(manager) +
        offsetof(WaveSoundManager, cached_music_names) + static_cast<unsigned int>(index) * 256;
    return reinterpret_cast<char*>(address);
}

bool SameName(const char* left, const char* right) {
    const volatile unsigned char* a = reinterpret_cast<const volatile unsigned char*>(left);
    const volatile unsigned char* b = reinterpret_cast<const volatile unsigned char*>(right);
    for (;;) {
        unsigned char first = *a++;
        unsigned char second = *b++;
        if (first != second)
            return false;
        if (!first)
            return true;
    }
}

void CopyName(char* destination, const char* source) {
    volatile char* to = destination;
    const volatile char* from = source;
    char byte;
    do {
        byte = *from++;
        *to++ = byte;
    } while (byte);
}

MusicTrackRecord* Record(WaveSoundManager* manager, unsigned int byte_offset) {
    return reinterpret_cast<MusicTrackRecord*>(
        reinterpret_cast<unsigned int>(manager->loaded_music_data) + byte_offset);
}
}

extern "C" int __stdcall Sound_CacheMusic_0043d7d0(
        const char* name, WaveSoundManager* manager, int index) {
    if (Slot(manager->cached_music_data, index) && SameName(name, SlotName(manager, index)))
        return 0;

    // The destination is global, even when the supplied manager is different.
    CopyName(SlotName(&g_wave_sound_manager, index), name);
    if (!(g_sound_mode_flags & 0x10) || !manager->device_owner)
        return 0;
    unsigned char* previous = Slot(manager->cached_music_data, index);
    if (previous) {
        entry_free_00452422(previous);
        Slot(manager->cached_music_data, index) = 0;
    }

    void* file = g_music_create_file(manager->music_file_name, 0x80000000, 1, 0, 3, 0x08000080, 0);
    if (file == reinterpret_cast<void*>(-1))
        return -1;
    PathName_0043d2a0* path = reinterpret_cast<PathName_0043d2a0*>(const_cast<char*>(name));
    unsigned int offset = static_cast<unsigned int>(path->FindBasenameSlot_0043d2a0(manager)) * 52;
    g_music_seek_file(file, static_cast<int>(Record(manager, offset)->file_offset), 0, 0);
    unsigned char* data = static_cast<unsigned char*>(asm_malloc_00452706(Record(manager, offset)->data_bytes));
    if (!data) {
        g_music_close_file(file);
        return -1;
    }
    unsigned int bytes_read;
    g_music_read_file(file, data, Record(manager, offset)->data_bytes, &bytes_read, 0);
    g_music_close_file(file);
    // Metadata is reloaded after callbacks, including Close. The BOOL, actual
    // byte count and Seek result do not determine publication success.
    MusicTrackRecord* record = Record(manager, offset);
    Slot(manager->cached_music_records, index) = record;
    Slot(manager->cached_music_data, index) = data;
    Slot(manager->music_read_cursors, index) = data;
    Slot(manager->music_remaining_bytes, index) = record->data_bytes;
    return 0;
}
