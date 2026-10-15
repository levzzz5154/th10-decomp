#pragma once
#include <stddef.h>
#include "th10/render/position_setter_pair.hpp"
#include "th10/game/item_spawn_0041bb00.hpp"

struct PlayfieldPoint {
    float x, y;
    __declspec(noinline) int OutsideBounds(float horizontal_margin, float vertical_margin) const;
};

// A complete record occupies 0x7F0 bytes. The collision loop visits every one
// of the 2000 records, beginning at manager+0x60.
struct CollisionRecord_00408100 {
    unsigned int flags;
    int countdown;
    unsigned char reserved_008[0x30C - 0x008];
    unsigned short animation_state;
    unsigned char reserved_30E[0x3B4 - 0x30E];
    PositionVector_004492f0 position;
    unsigned char reserved_3C0[0x3F0 - 0x3C0];
    float collision_diameter;
    unsigned int reserved_3F4;
    int timer_previous;
    int timer_current;
    float timer_elapsed;
    const float* timer_speed;
    unsigned int timer_flags;
    unsigned char reserved_40C[0x438 - 0x40C];
    int animation_index;
    unsigned char reserved_43C[0x446 - 0x43C];
    unsigned short state;
    unsigned char reserved_448[0x7F0 - 0x448];
    __declspec(noinline) int Activate();
};
struct CollisionEngine_00408100 {
    unsigned char reserved_000[0x60];
    CollisionRecord_00408100 records[2000];
    unsigned char reserved_after_records[0x3E0B50 - 0x60 - 2000 * 0x7F0];
    void* item_animation;
    __declspec(noinline) int Check(const PositionVector_004492f0* point,
        float radius, int spawn_item, int filter_countdown);
    __declspec(noinline) void ActivateAll(int idle_only);
};
extern "C" CollisionEngine_00408100* data_004776f0;
extern "C" ItemSpawnManager_0041bb00* data_00477818;
extern "C" float g_game_speed;
extern "C" float data_00470b0c;
typedef char CollisionRecordSize[sizeof(CollisionRecord_00408100) == 0x7F0 ? 1 : -1];
typedef char CollisionRecordPosition[offsetof(CollisionRecord_00408100, position) == 0x3B4 ? 1 : -1];
typedef char CollisionRecordRadius[offsetof(CollisionRecord_00408100, collision_diameter) == 0x3F0 ? 1 : -1];
typedef char CollisionRecordStatus[offsetof(CollisionRecord_00408100, state) == 0x446 ? 1 : -1];
typedef char CollisionAnimationResource[offsetof(CollisionEngine_00408100, item_animation) == 0x3E0B50 ? 1 : -1];
