#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/math/timer.hpp"

// One 0x3AC-byte sprite of the player manager's pools; built by 0x00402050
// and destroyed by 0x00401FF0.
struct PlayerManagerSprite_00408910 {
    unsigned char storage[0x3AC];

    __declspec(noinline) PlayerManagerSprite_00408910();
    __declspec(noinline) ~PlayerManagerSprite_00408910();
};

// The manager's frame timer starts out unregistered.
struct PlayerManagerTimer_00408910 : FrameTimer {
    PlayerManagerTimer_00408910() { flags &= ~1u; }
};

// The 0x37B0-byte player manager, as its constructor lays it out.
struct PlayerManager_00408910 {
    unsigned int flags;
    unsigned char reserved_0004[0x10 - 0x04];
    PlayerManagerSprite_00408910 sprites_0010[2];
    unsigned char reserved_0768[0x778 - 0x768];
    PlayerManagerSprite_00408910 sprites_0778[8];
    PlayerManagerSprite_00408910 sprites_24d8[5];
    PlayerManagerTimer_00408910 frame_timer;
    unsigned char reserved_3748[0x37B0 - 0x3748];

    __declspec(noinline) PlayerManager_00408910();    // 0x00408910
};
typedef char PlayerManagerSize_00408910[sizeof(PlayerManager_00408910) == 0x37B0 ? 1 : -1];
typedef char PlayerManagerTimerOffset_00408910[offsetof(PlayerManager_00408910, frame_timer) == 0x3734 ? 1 : -1];

extern "C" PlayerManager_00408910* data_004776f4;
