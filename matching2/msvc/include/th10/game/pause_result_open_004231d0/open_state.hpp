#pragma once
#include <stddef.h>
#include "th10/game/pause_result_open_004231d0/open_animation.hpp"
#include "th10/game/pause_result_open_004231d0/descriptor.hpp"
#include "th10/game/pause_result_open_004231d0/music.hpp"
extern "C" float data_00476f78;
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
            speed = &data_00476f78;
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
    AnimationResource_00449870* cursor_resource;
};
struct OpenResources {
    unsigned char reserved[0x9EC8];
    AnimationResource_00449870* result_resource;
};
struct OpenMusicProgress {
    unsigned char reserved[0x1D8A3];
    unsigned char result_track_heard;
};
extern "C" OpenRuntime* g_game;
extern "C" unsigned int data_00491ff4;
extern "C" int data_00491fb8;
extern "C" OpenGameThread* g_ascii_manager;
extern "C" OpenResources* g_front;
extern "C" unsigned char data_00491d78;
extern "C" OpenMusicProgress* data_0047783c;
extern "C" char data_0046e0d8[];
extern "C" char data_0046df98[];
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
    AnimationResource_00449870* current_resource;
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
