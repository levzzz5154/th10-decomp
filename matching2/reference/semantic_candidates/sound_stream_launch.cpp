// 0x0043D690, 241 retail bytes: replace the music worker and open a file stream.
// Retail takes EAX manager plus filename on the stack (RET 4). This explicit
// stdcall candidate has two arguments; native matching remains pending.
#include "sound_wave_types.hpp"

typedef unsigned int (__stdcall* MusicWorkerEntry)(void*);
typedef void* (__stdcall* MusicCreateEvent)(void*, int, int, const char*);
typedef void* (__stdcall* MusicCreateThread)(void*, unsigned int, MusicWorkerEntry, void*, unsigned int, unsigned int*);
extern "C" {
    extern MusicCreateEvent g_music_create_event;
    extern MusicCreateThread g_music_create_thread;
    extern void* g_music_worker_argument;
    extern unsigned int g_music_stream_algorithm[4];
    unsigned int __stdcall SoundStream_Worker_0043e3a0(void*);
    int __stdcall SoundStream_CreateFile_0044c8f0(SoundStreamingState**, unsigned int flags,
        WaveDirectSoundDevice**, const char*, unsigned int, unsigned int, unsigned int, unsigned int,
        unsigned int segment_count, unsigned int segment_bytes, void*, MusicTrackRecord*);
}

extern "C" int __stdcall SoundStream_LaunchFile_0043d690(WaveSoundManager* manager, const char* filename) {
    unsigned int source = reinterpret_cast<unsigned int>(filename);
    unsigned int destination = reinterpret_cast<unsigned int>(manager) + 0x5108;
    unsigned char byte;
    do {
        byte = *reinterpret_cast<const volatile unsigned char*>(source++);
        *reinterpret_cast<volatile unsigned char*>(destination++) = byte;
    } while (byte);
    if (!manager->device_owner || !manager->device)
        return -1;
    Sound_StopMusicWorker_0043dab0(manager);

    MusicTrackRecord* record = reinterpret_cast<MusicTrackRecord*>(manager->loaded_music_data);
    unsigned int alignment = record->format.block_alignment;
    unsigned int segment_bytes = (record->format.sample_rate * alignment << 2) >> 4;
    manager->music_worker_event = g_music_create_event(0, 0, 0, 0);
    void* thread = g_music_create_thread(0, 0, SoundStream_Worker_0043e3a0,
        g_music_worker_argument, 0, &manager->music_thread_id);
    void* event = manager->music_worker_event;
    manager->music_thread = thread;
    // The modulus (and possible zero-divisor fault) occurs only after both
    // handles have been published. High product bits were discarded above.
    segment_bytes -= segment_bytes % alignment;
    int result = SoundStream_CreateFile_0044c8f0(
        reinterpret_cast<SoundStreamingState**>(&manager->music_stream), 0x10100,
        manager->device_owner, filename, g_music_stream_algorithm[0], g_music_stream_algorithm[1],
        g_music_stream_algorithm[2], g_music_stream_algorithm[3], 16, segment_bytes, event, record);
    return result < 0 ? -1 : 0;
}
