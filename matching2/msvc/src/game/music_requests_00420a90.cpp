// Background-music requests.  They post commands to the music thread's
// request table at 0x00492590 through the table insert at 0x0043E460 (the
// type is still named after the animation-table layout it was first
// recovered from), always under the placeholder track name "dummy".
//
// When the streamed-music option (bit 4 of the configuration flags) is on,
// command 4 is queued: before starting a new track (Music_Play at 0x00420B10,
// still assembly: see reference/semantic_candidates/music_play_ltcg_00420b10.cpp,
// exact except for the base/index register order of its final store) and in
// place of command 3 when stopping.
//
// The insert takes the table in EAX and the name in EDX, so the body is
// compiled in the cluster layout/ltcg/animation_resource_registrar_0043e460.json.
#include <string.h>

#include "th10/render/resource_registrar_0043e460.hpp"

extern AnimationManager_0043e460 g_music_requests;   // 0x00492590
extern unsigned char g_config_flags;                 // 0x00491D78
extern float g_game_speed;                           // 0x00476F78

enum {
    kConfigStreamedMusic = 0x10,
    kMusicCommandLoad = 1,
    kMusicCommandStop = 3,
    kMusicCommandStreamedReset = 4,
    kMusicCommandFadeOut = 5
};

// 0x00420A90: queue `file_name` for loading into music slot `slot`, always
// as the .wav rendition of the named track.
#pragma code_seg(".text$00b_load")
__declspec(noinline) int __stdcall Music_Load(int slot, const char* file_name) {
    char path[256];
    strcpy(path, file_name);
    char* extension = strrchr(path, '.');
    extension[1] = 'w';
    extension[2] = 'a';
    extension[3] = 'v';
    g_music_requests.RegisterResource(path, kMusicCommandLoad, slot);
    return 1;
}
#pragma code_seg()

// 0x00420C00: stop the current track.
#pragma code_seg(".text$00d_stop")
__declspec(noinline) int __stdcall Music_Stop() {
    if (g_config_flags & kConfigStreamedMusic)
        g_music_requests.RegisterResource("dummy", kMusicCommandStreamedReset, 0);
    else
        g_music_requests.RegisterResource("dummy", kMusicCommandStop, 0);
    return 0;
}
#pragma code_seg()



#pragma code_seg(".text$00f_fade")
__declspec(noinline) int __stdcall Music_FadeOut(float frames) {
    // Keep the branch-specific integer conversions: the native compiler
    // merges their x87 conversion tail without preloading frames too early.
    int duration;
    if (g_game_speed == 0.0f) duration = (int)frames;
    else duration = (int)(g_game_speed > 1.0f ? frames : frames / g_game_speed);
    g_music_requests.RegisterResource("", kMusicCommandFadeOut, duration);
    return 0;
}
#pragma code_seg()
