#pragma once
#include "runtime.hpp"

struct PlayfieldPoint {
    float x, y;
    __declspec(noinline) int OutsideBounds(float horizontal_margin, float vertical_margin) const;
};
struct PlayerCollisionRecord {
    unsigned int flags;
    int countdown;
    unsigned char reserved_008[0x30c-8];
    unsigned short animation_state;
    unsigned char reserved_30e[0x3b4-0x30e];
    Vec3 position;
    unsigned char reserved_3c0[0x3f0-0x3c0];
    float collision_diameter;
    unsigned int reserved_3f4;
    int timer_previous, timer_current;
    float timer_elapsed;
    const float* timer_speed;
    unsigned int timer_flags;
    unsigned char reserved_40c[0x438-0x40c];
    int animation_index;
    unsigned char reserved_43c[0x446-0x43c];
    unsigned short state;
    unsigned char reserved_448[0x7f0-0x448];
    __declspec(noinline) int Activate();
};
struct PlayerCollisionEngine {
    unsigned char reserved_000[0x60];
    PlayerCollisionRecord records[2000];
    unsigned char reserved_after_records[0x3e0b50-0x60-2000*0x7f0];
    void* item_animation;
    __declspec(noinline) int Check(const Vec3* point, float radius, int spawn_item, int filter_countdown);
};
struct PlayerItemManager;
extern "C" {
extern PlayerCollisionEngine* data_004776f0;
extern PlayerItemManager* data_00477818;
extern float data_00470b0c;
}
struct AnimationResource_0043e710 {
    unsigned short id;
    unsigned char reserved_002[0x11c-2];
    void** scripts;
    unsigned char reserved_120[4];
    int loading;
    __declspec(noinline) void* LoadScript(Entity* object, int index);
    __declspec(noinline) AnimationRef CreateOffset(int index, const Vector3* position);
};
typedef char CollisionRecordSize[sizeof(PlayerCollisionRecord)==0x7f0?1:-1];
typedef char CollisionRecordPosition[offsetof(PlayerCollisionRecord,position)==0x3b4?1:-1];
typedef char CollisionRecordRadius[offsetof(PlayerCollisionRecord,collision_diameter)==0x3f0?1:-1];
typedef char CollisionRecordStatus[offsetof(PlayerCollisionRecord,state)==0x446?1:-1];
typedef char CollisionAnimationResource[offsetof(PlayerCollisionEngine,item_animation)==0x3e0b50?1:-1];
