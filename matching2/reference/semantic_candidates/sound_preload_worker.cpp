// Behavioral recovery of the 107-byte producer at 0x0043D080. It publishes
// owned archive buffers for the sound initializer's pending-WAVE consumer.
#include "sound_wave_types.hpp"
#include "th10/platform/archive_file.hpp"

typedef void (__stdcall* SoundPreloadSleep)(unsigned int milliseconds);
extern "C" {
    extern WaveSoundManager g_wave_sound_manager;
    extern const char* g_sound_preload_names[37];
    extern char g_sound_preload_error[];
    extern SoundPreloadSleep g_sound_sleep;
}

extern "C" void __stdcall Sound_PreloadWorker_0043d080() {
    for (int index = 0; index < 37; ++index) {
        if (g_sound_shutdown_state == 2)
            return;
        unsigned char* data = reinterpret_cast<unsigned char*>(
            Archive_LoadFile(g_sound_preload_names[index], 0, 0));
        g_wave_sound_manager.pending_wave[index] = data;
        if (!data) {
            // A loader callback can replace the name used by the diagnostic.
            g_wave_error_log.Append(g_sound_preload_error, g_sound_preload_names[index]);
            return;
        }
    }
    if (!g_sound_shutdown_state) {
        const SoundPreloadSleep wait = g_sound_sleep;
        do {
            wait(1);
        } while (!g_sound_shutdown_state);
    }
}
