// 0x0043D690: start streaming a track of the music file.
//
// Records the file name, stops the previous stream and its worker, creates the
// notification event and the worker thread, then opens the track as a stream
// of sixteen quarter-second segments. The manager arrives in EAX.
#include "../../../layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#include "th10/app/supervisor.hpp"
#include <string.h>
#pragma intrinsic(strcpy)

typedef unsigned int (__stdcall* MusicWorkerEntry)(void*);
extern "C" {
__declspec(dllimport) void* __stdcall CreateEventA(void* security, int manual_reset,
    int initial_state, const char* name);
__declspec(dllimport) void* __stdcall CreateThread(void* security, unsigned int stack_bytes,
    MusicWorkerEntry entry, void* argument, unsigned int flags, unsigned int* thread_id);
extern WaveGuidImage data_0046a67c;
unsigned int __stdcall SoundStream_Worker_0043e3a0(void*);
}

#pragma code_seg(".text$02launch")
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
    music_worker_event = CreateEventA(0, 0, 0, 0);
    music_thread = CreateThread(0, 0, SoundStream_Worker_0043e3a0, g_supervisor.window, 0,
        &music_thread_id);
    segment_bytes -= segment_bytes % align;
    if (reinterpret_cast<SoundDeviceOwner*>(device_owner)->CreateFileStream(
            reinterpret_cast<SoundStreamingState**>(&music_stream), 0x10100, name,
            data_0046a67c, 16, segment_bytes, music_worker_event, record) < 0)
        return -1;
    return 0;
}
#pragma code_seg()
