#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

// One sprite of the item manager: an Entity built by 0x00402050 and destroyed
// by 0x00401FF0.
struct FrontSprite : Entity {
    FrontSprite();
    __declspec(noinline) ~FrontSprite();
};

// The manager's frame timer starts out unregistered.
struct FrontTimer : FrameTimer {
    FrontTimer() { flags &= ~1u; }
};

// The 0x9ED0-byte item manager, as its constructor lays it out.
struct Front {
    unsigned int flags;
    unsigned char reserved_0004[0x10 - 0x04];
    FrontSprite sprites_0010[10];
    FrontSprite sprites_24c8[10];
    FrontSprite sprites_4980[9];
    FrontSprite sprites_6a8c[4];
    FrontSprite sprites_793c[2];
    FrontSprite sprites_8094[7];
    FrontSprite sprite_9a48;
    unsigned char reserved_9df4[0x9E60 - 0x9DF4];
    FrontTimer frame_timer;
    unsigned char reserved_9e74[0x9ED0 - 0x9E74];

    __declspec(noinline) Front();    // 0x00413810
};
typedef char ItemManagerSize_00413810[sizeof(Front) == 0x9ED0 ? 1 : -1];
typedef char FrontSpriteOffset[offsetof(Front, sprite_9a48) == 0x9A48 ? 1 : -1];
typedef char FrontTimerOffset[offsetof(Front, frame_timer) == 0x9E60 ? 1 : -1];

extern "C" Front* g_front;
