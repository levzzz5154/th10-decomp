// 0x0043DAB0, 176 bytes. Retail receives the manager in ESI and returns
// with plain RET. This explicit stdcall candidate is for behavioral recovery.
#include "sound_wave_types.hpp"

typedef int (__stdcall* SoundPostThreadMessage)(unsigned int thread_id,
    unsigned int message, unsigned int wparam, unsigned int lparam);
typedef unsigned int (__stdcall* SoundWaitForObject)(void* handle, unsigned int milliseconds);
typedef int (__stdcall* SoundCloseHandle)(void* handle);

extern "C" {
    int __fastcall Sound_AggregateInterfaces_0044d550(SoundStream*);
    extern SoundPostThreadMessage g_sound_post_thread_message;
    extern SoundWaitForObject g_sound_wait_for_object;
    extern SoundCloseHandle g_sound_close_handle;
}

extern "C" void __stdcall Sound_StopMusicWorker_0043dab0(WaveSoundManager* manager) {
    if (!manager->music_stream)
        return;

    Sound_AggregateInterfaces_0044d550(manager->music_stream);
    if (manager->music_thread) {
        const SoundPostThreadMessage post = g_sound_post_thread_message;
        post(manager->music_thread_id, 0x12, 0, 0);
        // The first Post callback precedes capture of the Wait import.
        const SoundWaitForObject wait = g_sound_wait_for_object;
        unsigned int result = wait(manager->music_thread, 0x100);
        while (result != 0) {
            post(manager->music_thread_id, 0x12, 0, 0);
            result = wait(manager->music_thread, 0x100);
        }
        const SoundCloseHandle close = g_sound_close_handle;
        close(manager->music_thread);
        close(manager->music_worker_event);
        manager->music_thread = 0;
    }
    SoundStream* output = manager->music_stream;
    if (output) {
        output->methods->destroy(output, 1);
        manager->music_stream = 0;
    }
}
