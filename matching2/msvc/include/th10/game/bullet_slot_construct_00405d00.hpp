#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

// Mark a timer or animation slot as not registered.
inline void BulletSlot_ClearRegistration(uint32_t* flags) { *flags &= ~1u; }

// A frame timer that starts out unregistered.
struct BulletSlotTimer_00405d00 : FrameTimer {
    BulletSlotTimer_00405d00() { flags &= ~1u; }
};

// The slot's sprite: an Entity with every animation slot unregistered, the
// block cleared and no sprite selected.
struct BulletSlotSprite_00405d00 : Entity {
    __forceinline BulletSlotSprite_00405d00() {
        BulletSlot_ClearRegistration(&flags_06C);
        BulletSlot_ClearRegistration(&flags_0B0);
        BulletSlot_ClearRegistration(&flags_0FC);
        BulletSlot_ClearRegistration(&flags_128);
        BulletSlot_ClearRegistration(&flags_174);
        BulletSlot_ClearRegistration(&flags_1B0);
        BulletSlot_ClearRegistration(&flags_1FC);
        BulletSlot_ClearRegistration(&flags_228);
        BulletSlot_ClearRegistration(&flags_378);
        memset(this, 0, sizeof(Entity));
        SpriteIndex() = -1;
    }
};

// One of the slot's nine 0x34-byte timed steps.
struct BulletSlotStep_00405d00 {
    BulletSlotTimer_00405d00 timer;
    unsigned char reserved_14[0x34 - 0x14];
};

// One 0x7F0-byte bullet of the bullet manager's pool.
struct BulletSlot_00405d00 {
    unsigned char reserved_000[8];
    BulletSlotSprite_00405d00 sprite;           // +0x008
    unsigned char reserved_3b4[0x3F8 - 0x3B4];
    BulletSlotTimer_00405d00 timer_3f8;
    BulletSlotTimer_00405d00 timer_40c;
    unsigned char reserved_420[0x614 - 0x420];
    BulletSlotStep_00405d00 steps[9];           // +0x614
    unsigned char reserved_7e8[0x7F0 - 0x7E8];

    __declspec(noinline) BulletSlot_00405d00();     // 0x00405D00
};
typedef char BulletSlotSize_00405d00[sizeof(BulletSlot_00405d00) == 0x7F0 ? 1 : -1];
typedef char BulletSlotSteps_00405d00[offsetof(BulletSlot_00405d00, steps) == 0x614 ? 1 : -1];
