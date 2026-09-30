// 0x0043D950, 298 retail bytes. Retail takes ESI manager and EAX slot, plain
// RET. This explicit stdcall candidate still needs native private-ABI matching.
#include "sound_wave_types.hpp"

struct PlatformD790ArchiveOwner;
struct PathName_0043d2a0 {
    char text[1];
    int SelectArchiveEntry(PlatformD790ArchiveOwner*);
};

typedef unsigned int (__stdcall* CachedMusicWorkerEntry)(void*);
typedef void* (__stdcall* CachedMusicCreateEvent)(void*, int, int, const char*);
typedef void* (__stdcall* CachedMusicCreateThread)(void*, unsigned int, CachedMusicWorkerEntry, void*, unsigned int, unsigned int*);
extern "C" {
    extern volatile unsigned char g_music_enabled;
    extern volatile unsigned char g_sound_mode_flags;
    extern CachedMusicCreateEvent g_music_create_event;
    extern CachedMusicCreateThread g_music_create_thread;
    extern void* g_music_worker_argument;
    extern unsigned int g_music_stream_algorithm[4];
    unsigned int __stdcall SoundStream_Worker_0043e3a0(void*);
    int __stdcall SoundStream_CreateMemory_0044cbf0(SoundStreamingState**, unsigned int,
        WaveDirectSoundDevice**, unsigned char*, unsigned int, MusicTrackRecord*,
        unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, void*);
}

namespace {
template<class T> T& CachedMusicSlot(T* first, unsigned int index) {
    return *reinterpret_cast<T*>(reinterpret_cast<unsigned int>(first) + index * sizeof(T));
}
}

extern "C" int __stdcall SoundStream_LaunchCached_0043d950(WaveSoundManager* manager, unsigned int index) {
    if (!manager->device_owner || !g_music_enabled || !manager->device)
        return -1;
    if (!(g_sound_mode_flags & 0x10)) {
        unsigned int name = reinterpret_cast<unsigned int>(manager) + 0x4108 + index * 256;
        return reinterpret_cast<PathName_0043d2a0*>(name)->SelectArchiveEntry(
            reinterpret_cast<PlatformD790ArchiveOwner*>(manager));
    }
    if (!CachedMusicSlot(manager->cached_music_data, index))
        return -1;

    MusicTrackRecord* record = CachedMusicSlot(manager->cached_music_records, index);
    unsigned int alignment = record->format.block_alignment;
    unsigned int segment_bytes = (record->format.sample_rate * alignment << 2) >> 4;
    manager->music_worker_event = g_music_create_event(0, 0, 0, 0);
    void* thread = g_music_create_thread(0, 0, SoundStream_Worker_0043e3a0,
        g_music_worker_argument, 0, &manager->music_thread_id);
    void* event = manager->music_worker_event;
    manager->music_thread = thread;
    segment_bytes -= segment_bytes % alignment;

    // Format sizing was cached before callbacks, but the PCM range and record
    // argument come from the current slots after event/thread creation.
    int result = SoundStream_CreateMemory_0044cbf0(
        reinterpret_cast<SoundStreamingState**>(&manager->music_stream), 0x10100,
        manager->device_owner, CachedMusicSlot(manager->music_read_cursors, index),
        CachedMusicSlot(manager->music_remaining_bytes, index), CachedMusicSlot(manager->cached_music_records, index),
        g_music_stream_algorithm[0], g_music_stream_algorithm[1], g_music_stream_algorithm[2], g_music_stream_algorithm[3],
        16, segment_bytes, event);
    if (result < 0)
        return -1;
    manager->selected_music_slot = index;
    return 0;
}
