// Complete unselected caller model; retail launch remains assembly-owned.
// 0x0043D690: start streaming a track of the music file. Stops the previous
// stream and its worker, creates the notification event and the worker
// thread, then opens the track as a stream of sixteen quarter-second segments.
// Native LTCG passes the manager in EAX.
#include "../../layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include <string.h>
#pragma intrinsic(strcpy)

typedef unsigned int (__stdcall* MusicWorkerEntry)(void*);
extern "C" {
    // CreateEventA and CreateThread.
    extern void* (__stdcall* data_00466120)(void*, int, int, const char*);
    extern void* (__stdcall* data_00466118)(void*, unsigned int, MusicWorkerEntry, void*,
        unsigned int, unsigned int*);
    extern void* data_00491c70;
    extern WaveGuidImage data_0046a67c;
    unsigned int __stdcall SoundStream_Worker_0043e3a0(void*);
}
int __fastcall SoundStream_CreateFile_0044c8f0(SoundStreamingState** output, unsigned int flags,
    WaveDirectSoundDevice** owner, const char* name, WaveGuidImage algorithm,
    unsigned int segment_count, unsigned int segment_bytes, void* notification_event,
    MusicTrackRecord* record);

#pragma code_seg(".text$00launch")
int WaveSoundManager::LaunchMusic(const char* name) {
    strcpy(music_file_name, name);
    if (!device_owner)
        return -1;
    if (!device)
        return -1;
    StopMusicWorker();

    MusicTrackRecord* record = reinterpret_cast<MusicTrackRecord*>(loaded_music_data);
    unsigned int align = record->format.block_alignment;
    unsigned int segment_bytes = (record->format.sample_rate * align * 4) >> 4;
    music_worker_event = data_00466120(0, 0, 0, 0);
    music_thread = data_00466118(0, 0, SoundStream_Worker_0043e3a0, data_00491c70, 0,
        &music_thread_id);
    segment_bytes -= segment_bytes % align;
    if (SoundStream_CreateFile_0044c8f0(reinterpret_cast<SoundStreamingState**>(&music_stream),
            0x10100, device_owner, name, data_0046a67c, 16, segment_bytes,
            music_worker_event, record) < 0)
        return -1;
    return 0;
}
#pragma code_seg()
