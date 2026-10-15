#pragma once
#include <stddef.h>
#include "th10/game/pause_result_open_004231d0/open_animation.hpp"
#include "th10/game/pause_result_open_004231d0/descriptor.hpp"
#include "th10/game/pause_result_open_004231d0/music.hpp"
extern "C" float g_game_speed;
struct OpenTimer {
    int previous_frame;
    int current_frame;
    float elapsed;
    const float* speed;
    unsigned flags;
    __forceinline void Set(int frame) {
        if (!(flags & 1)) {
            current_frame = 0;
            previous_frame = -999999;
            elapsed = 0.0f;
            speed = &g_game_speed;
            flags |= 1;
        }
        current_frame = frame;
        elapsed = (float)frame;
        previous_frame = frame - 1;
    }
};
struct OpenRuntime {
    unsigned char reserved[0x58];
    unsigned flags;
    int replay_mode;
};
struct OpenGameThread {
    unsigned char reserved[0x8998];
    AnimationBank* cursor_resource;
};
struct OpenResources {
    unsigned char reserved[0x9EC8];
    AnimationBank* result_resource;
};
struct OpenMusicProgress {
    unsigned char reserved[0x1D8A3];
    unsigned char result_track_heard;
};
extern "C" OpenRuntime* g_game;
extern "C" unsigned int g_app_flags;
extern "C" int g_main_state;
extern "C" OpenGameThread* g_ascii_manager;
extern "C" OpenResources* g_front;
extern "C" unsigned char g_sound_flags;
extern "C" OpenMusicProgress* g_score;
extern "C" char str_bgm_th10_17_wav[];
extern "C" char str_dummy[];
struct PauseOpenState {
    int reserved_00;
    int phase;
    unsigned char reserved_08[8];
    OpenTimer timer;
    unsigned char reserved_24[0x1D4 - 0x24];
    AnimationScriptId background;
    AnimationScriptId cursor_animation;
    AnimationScriptId pause_animation;
    unsigned char reserved_1e0[4];
    int result_flag;
    unsigned char reserved_1e8[0x2C0 - 0x1E8];
    float saved_speed;
    AnimationBank* current_resource;
    __forceinline void Open(bool result);
    __declspec(noinline) void OpenPause();
    __declspec(noinline) void OpenResult();
};
extern "C" PauseOpenState* g_pause;
typedef char OpenTimerOffset[offsetof(PauseOpenState,timer)==0x10?1:-1];
typedef char OpenBackgroundOffset[offsetof(PauseOpenState,background)==0x1D4?1:-1];
typedef char OpenResultFlagOffset[offsetof(PauseOpenState,result_flag)==0x1E4?1:-1];
typedef char OpenSavedSpeedOffset[offsetof(PauseOpenState,saved_speed)==0x2C0?1:-1];
typedef char OpenResourceOffset[offsetof(PauseOpenState,current_resource)==0x2C4?1:-1];
