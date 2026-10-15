#pragma once
#include <stddef.h>
struct ItemPolarVelocity_0041bb00 {
    float x, y;
    __declspec(noinline) ItemPolarVelocity_0041bb00* SetPolar(float angle, float speed);
};
struct SpawnItem {
    unsigned char animation[0x2fc];
    int identifier;
    unsigned char reserved_300[0x3ac-0x300];
    float position[3];
    ItemPolarVelocity_0041bb00 velocity;
    int motion_state;
    int motion_counter;
    int timer_previous;
    int timer_current;
    float timer_elapsed;
    const float* timer_speed;
    unsigned int timer_flags;
    int state;
    int kind;
    int display_kind;
    int reserved_3e8;
    int variant;
};
struct ItemSpawnManager {
    unsigned char reserved_000[0x14];
    SpawnItem normal[150];
    SpawnItem special[2048];
    int reserved_21ceb4;
    int special_cursor;
    int special_count;
    __declspec(noinline) int Spawn(const float* position,
        int kind,int identifier,float angle,float speed);
    // 0x0041BA50: turn the live items of kinds 1 and 4 into kind 9.
    __declspec(noinline) int ConvertItems();
};
typedef char ItemSizeCheck[sizeof(SpawnItem)==0x3f0?1:-1];
typedef char ItemStateOffsetCheck[offsetof(SpawnItem,state)==0x3dc?1:-1];
typedef char ItemSpecialOffsetCheck[offsetof(ItemSpawnManager,special)==0x24eb4?1:-1];
typedef char ItemCursorOffsetCheck[offsetof(ItemSpawnManager,special_cursor)==0x21ceb8?1:-1];
