// Background-music requests.  Both post commands to the music thread's
// request table at 0x00492590 through the table insert at 0x0043E460 (the
// type is still named after the animation-table layout it was first
// recovered from), always under the placeholder track name "dummy".
//
// When the streamed-music option (bit 4 of the configuration flags) is on,
// an extra command 4 is queued: before starting a new track, and in place
// of command 3 when stopping.
//
// The insert takes the table in EAX and the name in EDX, so both bodies are
// compiled in the cluster layout/ltcg/animation_resource_registrar_0043e460.json.
struct AnimationManager_0043e460 {
    __declspec(noinline) char* RegisterResource(const char* name, int resource, int parameter);
};

struct MusicProgress_00420b10 {
    unsigned char reserved_00000[0x1D892];
    unsigned char track_heard[1];                    // +0x1D892, one byte per track
};

extern AnimationManager_0043e460 g_music_requests;   // 0x00492590
extern unsigned char g_config_flags;                 // 0x00491D78
extern MusicProgress_00420b10* g_music_progress;     // 0x0047783C

enum {
    kConfigStreamedMusic = 0x10,
    kMusicCommandPlay = 2,
    kMusicCommandStop = 3,
    kMusicCommandStreamedReset = 4
};

// 0x00420B10: start `track` and remember that `heard_index` has been played
// (for the music room).
#pragma code_seg(".text$00b_play")
__declspec(noinline) int __stdcall Music_Play(int track, int heard_index) {
    if (g_config_flags & kConfigStreamedMusic)
        g_music_requests.RegisterResource("dummy", kMusicCommandStreamedReset, 0);
    g_music_requests.RegisterResource("dummy", kMusicCommandPlay, track);
    g_music_progress->track_heard[heard_index] = 1;
    return 0;
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
