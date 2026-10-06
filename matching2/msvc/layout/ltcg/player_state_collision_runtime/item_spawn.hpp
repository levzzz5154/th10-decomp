#pragma once
#include <stddef.h>
#include "collision.hpp"
#include "timer.hpp"
struct AnimationResource_0043e710;
__declspec(noinline) void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource, Entity* entity, int script);
struct ItemPolarVelocity_0041bb00 {
    float x, y;
    __declspec(noinline) ItemPolarVelocity_0041bb00* SetPolar(float angle, float speed);
};
struct SpawnItem_0041bb00 {
    Entity animation;
    Vector3 position;
    ItemPolarVelocity_0041bb00 velocity;
    int motion_state;
    int motion_counter;
    FrameTimer timer;
    int state;
    int kind;
    int display_kind;
    int reserved_3e8;
    int variant;
};
struct PlayerItemManager {
    unsigned char reserved_000[0x14];
    SpawnItem_0041bb00 normal[150];
    SpawnItem_0041bb00 special[2048];
    int reserved_21ceb4;
    int special_cursor;
    int special_count;
    __declspec(noinline) int Spawn(const Vector3* position,
        int kind,int identifier,float angle,float speed);
    // 0x0041BA50: turn the live items of kinds 1 and 4 into kind 9.
    __declspec(noinline) int ConvertItems();
};
typedef char ItemSizeCheck_0041bb00[sizeof(SpawnItem_0041bb00)==0x3f0?1:-1];
typedef char ItemStateOffsetCheck_0041bb00[offsetof(SpawnItem_0041bb00,state)==0x3dc?1:-1];
typedef char ItemSpecialOffsetCheck_0041bb00[offsetof(PlayerItemManager,special)==0x24eb4?1:-1];
typedef char ItemCursorOffsetCheck_0041bb00[offsetof(PlayerItemManager,special_cursor)==0x21ceb8?1:-1];

typedef char SpawnItemAnimationOffset[offsetof(SpawnItem_0041bb00,animation)==0?1:-1];
typedef char SpawnItemPositionOffset[offsetof(SpawnItem_0041bb00,position)==0x3AC?1:-1];
typedef char SpawnItemTimerOffset[offsetof(SpawnItem_0041bb00,timer)==0x3C8?1:-1];
