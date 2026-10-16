#ifndef TH10_GAME_PLAYBACK_STATE_HPP
#define TH10_GAME_PLAYBACK_STATE_HPP

#include <stddef.h>
#include "th10/render/animation_stop_frame_handle.hpp"

struct PlaybackModeSource {
    unsigned char reserved_000[0x4474];
    int playback;
};

struct PlaybackState {
    unsigned char reserved_000[0x34];
    volatile int current_x;
    volatile int current_y;
    volatile int live_x;
    volatile int live_y;
    unsigned char reserved_044[8];
    volatile int saved_x;
    volatile int saved_y;
    unsigned char reserved_054[0x14];
    AnimationHandle11 animation;
    unsigned char reserved_06c[0x18];
    volatile int playback;
    __declspec(noinline) void SwitchPlaybackState();
};

typedef char PlaybackCurrentOffset[(offsetof(PlaybackState, current_x)==0x34)?1:-1];
typedef char PlaybackLiveOffset[(offsetof(PlaybackState, live_x)==0x3C)?1:-1];
typedef char PlaybackSavedOffset[(offsetof(PlaybackState, saved_x)==0x4C)?1:-1];
typedef char PlaybackAnimationOffset[(offsetof(PlaybackState, animation)==0x68)?1:-1];
typedef char PlaybackFlagOffset[(offsetof(PlaybackState, playback)==0x84)?1:-1];
typedef char PlaybackModeOffset[(offsetof(PlaybackModeSource, playback)==0x4474)?1:-1];

#endif
