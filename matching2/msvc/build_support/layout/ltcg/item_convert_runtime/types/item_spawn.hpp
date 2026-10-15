#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"
struct AnimationResourceFile;
__declspec(noinline) void __stdcall Entity_StartScript(AnimationResourceFile* resource, Entity* entity, int script);
struct ItemPolarVelocity_0041bb00 {
    float x, y, z;
    __declspec(noinline) ItemPolarVelocity_0041bb00* SetPolar(float angle, float speed);
};
struct SpawnItem {
    Entity animation;
    Vector3 position;
    ItemPolarVelocity_0041bb00 velocity;
    int motion_counter;
    FrameTimer timer;
    int state;
    int kind;
    int display_kind;
    float magnet_speed;
    int variant;
};
struct ItemSpawnManager {
    unsigned char reserved_000[0x14];
    SpawnItem items[2198];
    int live_count;
    int special_cursor;
    int special_count;
    __declspec(noinline) int Spawn(const Vector3* position,
        int kind,int identifier,float angle,float speed);
    // 0x0041BA50: turn the live items of kinds 1 and 4 into kind 9.
    __declspec(noinline) int ConvertItems();
};
typedef char ItemSizeCheck[sizeof(SpawnItem)==0x3f0?1:-1];
typedef char ItemStateOffsetCheck[offsetof(SpawnItem,state)==0x3dc?1:-1];
typedef char ItemSpecialOffsetCheck[offsetof(ItemSpawnManager,items)+150*sizeof(SpawnItem)==0x24eb4?1:-1];
typedef char ItemCursorOffsetCheck[offsetof(ItemSpawnManager,special_cursor)==0x21ceb8?1:-1];

typedef char SpawnItemAnimationOffset[offsetof(SpawnItem,animation)==0?1:-1];
typedef char SpawnItemPositionOffset[offsetof(SpawnItem,position)==0x3AC?1:-1];
typedef char SpawnItemTimerOffset[offsetof(SpawnItem,timer)==0x3C8?1:-1];

typedef char SpawnItemVerticalVelocityOffset[offsetof(SpawnItem,velocity)+offsetof(ItemPolarVelocity_0041bb00,z)==0x3C0?1:-1];
typedef char SpawnItemMagnetSpeedOffset[offsetof(SpawnItem,magnet_speed)==0x3E8?1:-1];
typedef char ItemLiveCountOffset[offsetof(ItemSpawnManager,live_count)==0x21CEB4?1:-1];
