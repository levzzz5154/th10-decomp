#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

// One sprite of the item manager: an Entity built by 0x00402050 and destroyed
// by 0x00401FF0.
struct HudSprite : Entity {
    HudSprite();
    __declspec(noinline) ~HudSprite();
};

// The manager's frame timer starts out unregistered.
struct HudTimer : FrameTimer {
    HudTimer() { flags &= ~1u; }
};

// The 0x9ED0-byte item manager, as its constructor lays it out.
struct Hud {
    unsigned int flags;
    unsigned char reserved_0004[0x10 - 0x04];
    HudSprite sprites_0010[10];
    HudSprite sprites_24c8[10];
    HudSprite sprites_4980[9];
    HudSprite sprites_6a8c[4];
    HudSprite sprites_793c[2];
    HudSprite sprites_8094[7];
    HudSprite sprite_9a48;
    unsigned char reserved_9df4[0x9E60 - 0x9DF4];
    HudTimer frame_timer;
    unsigned char reserved_9e74[0x9ED0 - 0x9E74];

    __declspec(noinline) Hud();    // 0x00413810
};
typedef char ItemManagerSize_00413810[sizeof(Hud) == 0x9ED0 ? 1 : -1];
typedef char HudSpriteOffset[offsetof(Hud, sprite_9a48) == 0x9A48 ? 1 : -1];
typedef char HudTimerOffset[offsetof(Hud, frame_timer) == 0x9E60 ? 1 : -1];

extern "C" Hud* data_0047770c;
