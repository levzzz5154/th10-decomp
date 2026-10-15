// Compiler context only: an unselected copy of the music launcher 0x0043D690
// (recovered in sound_music_launch.cpp) that gives the file-stream factory its
// direct caller. Native LTCG passes the manager in EAX.
#include "../../../layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include <string.h>
#pragma intrinsic(strcpy)

typedef unsigned int (__stdcall* MusicWorkerEntry)(void*);
extern "C" {
    // CreateEventA and CreateThread.
    extern void* (__stdcall* imp_CreateEventA)(void*, int, int, const char*);
    extern void* (__stdcall* imp_CreateThread)(void*, unsigned int, MusicWorkerEntry, void*,
        unsigned int, unsigned int*);
    extern void* data_00491c70;
    extern WaveGuidImage data_0046a67c;
    unsigned int __stdcall SoundStream_Worker_0043e3a0(void*);
}
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
    music_worker_event = imp_CreateEventA(0, 0, 0, 0);
    music_thread = imp_CreateThread(0, 0, SoundStream_Worker_0043e3a0, data_00491c70, 0,
        &music_thread_id);
    segment_bytes -= segment_bytes % align;
    if (reinterpret_cast<SoundDeviceOwner*>(device_owner)->CreateFileStream(
            reinterpret_cast<SoundStreamingState**>(&music_stream), 0x10100, name, data_0046a67c,
            16, segment_bytes, music_worker_event, record) < 0)
        return -1;
    return 0;
}
#pragma code_seg()
