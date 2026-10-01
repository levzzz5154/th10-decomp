#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

// One sprite of the item manager: an Entity built by 0x00402050 and destroyed
// by 0x00401FF0.
struct ItemManagerSprite_00413810 : Entity {
    ItemManagerSprite_00413810();
    __declspec(noinline) ~ItemManagerSprite_00413810();
};

// The manager's frame timer starts out unregistered.
struct ItemManagerTimer_00413810 : FrameTimer {
    ItemManagerTimer_00413810() { flags &= ~1u; }
};

// The 0x9ED0-byte item manager, as its constructor lays it out.
struct ItemManager_00413810 {
    unsigned int flags;
    unsigned char reserved_0004[0x10 - 0x04];
    ItemManagerSprite_00413810 sprites_0010[10];
    ItemManagerSprite_00413810 sprites_24c8[10];
    ItemManagerSprite_00413810 sprites_4980[9];
    ItemManagerSprite_00413810 sprites_6a8c[4];
    ItemManagerSprite_00413810 sprites_793c[2];
    ItemManagerSprite_00413810 sprites_8094[7];
    ItemManagerSprite_00413810 sprite_9a48;
    unsigned char reserved_9df4[0x9E60 - 0x9DF4];
    ItemManagerTimer_00413810 frame_timer;
    unsigned char reserved_9e74[0x9ED0 - 0x9E74];

    __declspec(noinline) ItemManager_00413810();    // 0x00413810
};
typedef char ItemManagerSize_00413810[sizeof(ItemManager_00413810) == 0x9ED0 ? 1 : -1];
typedef char ItemManagerSpriteOffset_00413810[offsetof(ItemManager_00413810, sprite_9a48) == 0x9A48 ? 1 : -1];
typedef char ItemManagerTimerOffset_00413810[offsetof(ItemManager_00413810, frame_timer) == 0x9E60 ? 1 : -1];

extern "C" ItemManager_00413810* data_0047770c;
