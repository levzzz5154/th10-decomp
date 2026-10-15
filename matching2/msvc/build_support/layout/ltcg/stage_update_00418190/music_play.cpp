// Background-music requests.  They post commands to the music thread's
// request table at 0x00492590 through the table insert at 0x0043E460 (the
// type is still named after the animation-table layout it was first
// recovered from), always under the placeholder track name "dummy".
//
// When the streamed-music option (bit 4 of the configuration flags) is on,
// command 4 is queued: before starting a new track and in place of command 3
// when stopping.
//
// The insert takes the table in EAX and the name in EDX, so the body is
// compiled in the cluster build_support/layout/ltcg/animation_resource_registrar.json.
#include <string.h>

#include "th10/render/resource_registrar_0043e460.hpp"

extern AnimationManager_0043e460 g_music_requests;   // 0x00492590
extern unsigned char g_config_flags;                 // 0x00491D78
extern float g_game_speed;                           // 0x00476F78

struct MusicProgress {
    unsigned char reserved_00000[0x1D892];
    unsigned char track_heard[1];                    // +0x1D892, one byte per track
};
extern MusicProgress* g_music_progress;     // 0x0047783C

enum {
    kConfigStreamedMusic = 0x10,
    kMusicCommandLoad = 1,
    kMusicCommandPlay = 2,
    kMusicCommandStop = 3,
    kMusicCommandStreamedReset = 4,
    kMusicCommandFadeOut = 5,
    kMusicCommandPause = 6,
    kMusicCommandUnpause = 7,
    kMusicCommandSetVolume = 8
};

// 0x00420B10: start `track` and remember that `heard_index` has been played
// (for the music room). The progress pointer is loaded before the index
// only when the link sees a direct caller, which the cluster context supplies.
#pragma code_seg(".text$00420b10_fn")
__declspec(noinline) int __stdcall Music_Play(int track, int heard_index) {
    if (g_config_flags & kConfigStreamedMusic)
        g_music_requests.RegisterResource("dummy", kMusicCommandStreamedReset, 0);
    g_music_requests.RegisterResource("dummy", kMusicCommandPlay, track);
    g_music_progress->track_heard[heard_index] = 1;
    return 0;
}
#pragma code_seg()

