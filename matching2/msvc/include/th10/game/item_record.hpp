#pragma once
#include <stddef.h>
#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/game/item_velocity.hpp"
#include "th10/math/timer.hpp"

enum ItemMotionState {
    Inactive = 0,
    Falling = 1,
    Launching = 2,
    SeekingPlayer = 3,
    Attracted = 4,
    WaitingForScript = 5
};

struct ItemMotionData {
    Vector3 position;
    ItemVelocity velocity;
    int motion_counter;
    FrameTimer timer;
    int state;
    int kind;
    int display_kind;
    float magnet_speed;
    int variant;
};

struct Item : Entity {
    ItemMotionData motion;

    __declspec(noinline) Item();
    __declspec(noinline) ~Item();

    __forceinline void InitializeAnimation() {
        ClearRegistration(&flags_06C);
        ClearRegistration(&flags_0B0);
        ClearRegistration(&flags_0FC);
        ClearRegistration(&flags_128);
        ClearRegistration(&flags_174);
        ClearRegistration(&flags_1B0);
        ClearRegistration(&flags_1FC);
        ClearRegistration(&flags_228);
        ClearRegistration(&flags_378);
        memset(static_cast<Entity*>(this), 0, sizeof(Entity));
        SpriteIndex() = -1;
        // The motion timer is outside the cleared animation; preserve its other bits.
        ClearRegistration(&motion.timer.flags);
    }

private:
    static void ClearRegistration(uint32_t* flags) { *flags &= ~1u; }
};

typedef char ItemRecordSize[sizeof(Item) == 0x3F0 ? 1 : -1];
typedef char ItemPositionOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, position) == 0x3AC ? 1 : -1];
typedef char ItemDepthVelocityOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, velocity) + offsetof(ItemVelocity, z)
    == 0x3C0 ? 1 : -1];
typedef char ItemTimerOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, timer) == 0x3C8 ? 1 : -1];
typedef char ItemTimerFlagsOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, timer) + offsetof(FrameTimer, flags)
    == 0x3D8 ? 1 : -1];
typedef char ItemMotionStateOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, state) == 0x3DC ? 1 : -1];
typedef char ItemMagnetSpeedOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, magnet_speed) == 0x3E8 ? 1 : -1];
typedef char ItemVariantOffset[
    offsetof(Item, motion) + offsetof(ItemMotionData, variant) == 0x3EC ? 1 : -1];
