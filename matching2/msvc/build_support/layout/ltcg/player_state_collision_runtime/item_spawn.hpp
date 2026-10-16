#pragma once
#include <stddef.h>
#include "collision.hpp"
#include "timer.hpp"
struct AnimationResourceFile;
__declspec(noinline) void __stdcall Entity_StartScript(AnimationResourceFile* resource, Entity* entity, int script);
struct ItemPolarVelocity2 {
    float x, y;
    __declspec(noinline) ItemPolarVelocity2* SetPolar(float angle, float speed);
};
struct SpawnItem {
    Entity animation;
    Vector3 position;
    ItemPolarVelocity2 velocity;
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
    SpawnItem normal[150];
    SpawnItem special[2048];
    int reserved_21ceb4;
    int special_cursor;
    int special_count;
    __declspec(noinline) int Spawn(const Vector3* position,
        int kind,int identifier,float angle,float speed);
    // 0x0041BA50: turn the live items of kinds 1 and 4 into kind 9.
    __declspec(noinline) int ConvertItems();
};
typedef char ItemSizeCheck[sizeof(SpawnItem)==0x3f0?1:-1];
typedef char ItemStateOffsetCheck[offsetof(SpawnItem,state)==0x3dc?1:-1];
typedef char ItemSpecialOffsetCheck[offsetof(PlayerItemManager,special)==0x24eb4?1:-1];
typedef char ItemCursorOffsetCheck[offsetof(PlayerItemManager,special_cursor)==0x21ceb8?1:-1];

typedef char SpawnItemAnimationOffset[offsetof(SpawnItem,animation)==0?1:-1];
typedef char SpawnItemPositionOffset[offsetof(SpawnItem,position)==0x3AC?1:-1];
typedef char SpawnItemTimerOffset[offsetof(SpawnItem,timer)==0x3C8?1:-1];

// The game counters at 0x00474C40. The player update passes the object to
// its gauge routine, so its fields are re-read after unrelated stores.
struct PlayerScoreGauge {
    int high_score;
    int score;
    short power;
    unsigned char reserved_0a[0x28 - 0x0a];
    int character;
    int shot_type;
    int lives;
    unsigned char reserved_34[0x58 - 0x34];
    int rank;                         // 0x00474C98 (g_rank)
    __declspec(noinline) void AddWithMinimum(int amount);
};
extern "C" PlayerScoreGauge g_globals;
