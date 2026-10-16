// 0x0043D080: sound-effect preload thread. Loads the 37 sound-effect files
// from the archive and publishes each buffer for the sound manager; a missing
// file is logged and ends the thread. Once everything is loaded it waits for
// the sound system to leave its initial state. A state of 2 (shutdown) stops
// loading early.
#include "th10/platform/archive_file.hpp"
#include "th10/platform/text_log.hpp"
#include "th10/platform/windows_types.hpp"

enum { kSoundEffectCount = 37, kSoundThreadShutdown = 2 };

extern "C" {
// Same real Sleep import slot0x4660AC, named here to avoid the
// independent minimal Windows header declaration.
__declspec(dllimport) void __stdcall SoundThread_Sleep(DWORD milliseconds);
extern const char* g_sound_effect_files[kSoundEffectCount];     // "se_plst00.wav", ...
extern char* g_pending_sound_effects[kSoundEffectCount];
extern volatile int g_sound_thread_state;
extern char g_sound_load_error_format[];   // "error : Sound file could not be read. Check the data %s\r\n"
extern TextLog4 g_text_log;
}

#pragma code_seg(".text$03fn")
extern "C" __declspec(noinline) void __cdecl Sound_PreloadWorker() {
    for (int index = 0; index < kSoundEffectCount; ++index) {
        if (g_sound_thread_state == kSoundThreadShutdown)
            return;
        g_pending_sound_effects[index] = Archive_LoadFile(g_sound_effect_files[index], 0, 0);
        if (!g_pending_sound_effects[index]) {
            g_text_log.Append(g_sound_load_error_format, g_sound_effect_files[index]);
            return;
        }
    }
    while (!g_sound_thread_state)
        SoundThread_Sleep(1);
}
#pragma code_seg()
