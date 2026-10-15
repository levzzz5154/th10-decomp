// 0x0043D950: start playing a cached music slot.
//
// Without the in-memory music option the slot's name is looked up in the music
// file and the running stream is pointed at that track. With it, a worker
// thread and its event are created and the slot's buffer is opened as a stream
// of sixteen quarter-second segments. The manager arrives in ESI and the slot
// in EAX.
//
// The stream factory is a member of the device owner whose parameters follow
// the DirectX sample's CreateStreaming; that order is what places the output
// slot's address ahead of the owner in the argument sequence.
#include "../../../layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include "th10/app/supervisor.hpp"

typedef unsigned int (__stdcall* MusicWorkerEntry)(void*);
extern "C" {
__declspec(dllimport) void* __stdcall CreateEventA(void* security, int manual_reset,
    int initial_state, const char* name);
__declspec(dllimport) void* __stdcall CreateThread(void* security, unsigned int stack_bytes,
    MusicWorkerEntry entry, void* argument, unsigned int flags, unsigned int* thread_id);
extern WaveGuidImage data_0046a67c;
unsigned int __stdcall SoundStream_Worker_0043e3a0(void*);
}
// 0x0043D790: point the running stream at the track a path names.
struct PlatformD790ArchiveOwner;
struct PathName_0043d2a0 {
    int SelectArchiveEntry(PlatformD790ArchiveOwner* owner);
};

#pragma code_seg(".text$01play")
int WaveSoundManager::PlayCachedMusic(int slot) {
    if (!device_owner)
        return -1;
    if (!g_supervisor.music_mode)
        return -1;
    if (!device)
        return -1;
    if (!(g_supervisor.flags & 0x10))
        return reinterpret_cast<PathName_0043d2a0*>(cached_music_names[slot])
            ->SelectArchiveEntry(reinterpret_cast<PlatformD790ArchiveOwner*>(this));
    if (!cached_music_data[slot])
        return -1;

    MusicTrackRecord* record = cached_music_records[slot];
    unsigned int align = record->format.block_alignment;
    unsigned int segment_bytes = (record->format.sample_rate * align * 4) >> 4;
    music_worker_event = CreateEventA(0, 0, 0, 0);
    music_thread = CreateThread(0, 0, SoundStream_Worker_0043e3a0, g_supervisor.window, 0,
        &music_thread_id);
    segment_bytes -= segment_bytes % align;
    if (reinterpret_cast<SoundDeviceOwner*>(device_owner)->CreateMemoryStream(
            reinterpret_cast<SoundStreamingState**>(&music_stream),
            music_read_cursors[slot], music_remaining_bytes[slot], cached_music_records[slot],
            0x10100, data_0046a67c, 16, segment_bytes, music_worker_event) < 0)
        return -1;
    selected_music_slot = slot;
    return 0;
}
#pragma code_seg()
