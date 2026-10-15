#pragma once
#include "th10/game/pause_result_open_004231d0/open_animation.hpp"
struct PlayfieldPoint {
    float x, y;
    __declspec(noinline) int OutsideBounds(float horizontal_margin, float vertical_margin) const;
};

// A complete record occupies 0x7F0 bytes. The collision loop visits every one
// of the 2000 records, beginning at manager+0x60.
struct StageCollisionRecord {
    unsigned int flags;
    int countdown;
    unsigned char reserved_008[0x30C - 0x008];
    unsigned short animation_state;
    unsigned char reserved_30E[0x3B4 - 0x30E];
    Vector3 position;
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
struct StageCollisionEngine {
    unsigned char reserved_000[0x60];
    StageCollisionRecord records[2000];
    unsigned char reserved_after_records[0x3E0B50 - 0x60 - 2000 * 0x7F0];
    void* item_animation;
    __declspec(noinline) int Check(const Vector3* point,
        float radius, int spawn_item, int filter_countdown);
    __declspec(noinline) void ActivateAll(int idle_only);
};
extern "C" StageCollisionEngine* g_bullet_manager;

struct SlotTimer {
    int previous, current;
    float elapsed;
    const float* speed;
    unsigned flags;
    SlotTimer() { flags &= ~1u; }
    void Set(int frame) {
        if (!(flags & 1)) {
            current = 0;
            previous = -999999;
            elapsed = 0.0f;
            speed = &g_game_speed;
            flags |= 1;
        }
        current = frame;
        elapsed = (float)frame;
        previous = frame - 1;
    }
};
struct SlotRef { unsigned value; SlotRef() {} SlotRef(unsigned v): value(v) {} };
struct SlotLists {
    unsigned char reserved[0x72DAD4];
    AnimationManagerNodeOpen* primary_head;
    AnimationManagerNodeOpen* primary_tail;
    unsigned char reserved_after[0x732454-0x72DADC];
    unsigned next_id;
    __declspec(noinline) SlotRef RegisterPrimaryBack(Entity* object);
};
struct SlotResources {
    unsigned char reserved[0x899C];
    AnimationBank* resource;
};
extern "C" SlotResources* g_ascii_manager;
struct SlotEffect {
    virtual void Reserved0() = 0;
    virtual void Reserved1() = 0;
    virtual void Reserved2() = 0;
    virtual void Reserved3() = 0;
    virtual void Reserved4() = 0;
    virtual void Release(int) = 0;
    unsigned reserved;
    SlotEffect* next;
    int kind;
};
struct SlotEffectManager { unsigned char reserved[0x18]; SlotEffect* first; };
extern "C" SlotEffectManager* g_laser_manager;
extern "C" void* g_enemy_ctrl;
extern "C" void __stdcall SweepDeaths(void* manager);
struct SlotVector {
    float x,y,z;
    SlotVector() {}
    SlotVector(float x_,float y_,float z_) : x(x_),y(y_),z(z_) {}
};
struct StageScoreDisplay {
    int id;
    SlotTimer first, second, third;
    unsigned reserved40[3];
    SlotRef first_animation, second_animation;
    unsigned reserved54, field58;
    const void* definition;
    SlotVector radius, region;
    unsigned reserved78[2], field80, field84, color_a, color_b;
    __declspec(noinline) StageScoreDisplay(const void* definition);
};
typedef char StageScoreDisplaySize[sizeof(StageScoreDisplay)==0x90?1:-1];

#define DISPLAY_OFFSET(field, value) \
    typedef char Display_##field##_offset[offsetof(StageScoreDisplay, field) == value ? 1 : -1]
DISPLAY_OFFSET(first, 0x4);
DISPLAY_OFFSET(second, 0x18);
DISPLAY_OFFSET(third, 0x2C);
DISPLAY_OFFSET(first_animation, 0x4C);
DISPLAY_OFFSET(second_animation, 0x50);
DISPLAY_OFFSET(definition, 0x5C);
DISPLAY_OFFSET(radius, 0x60);
DISPLAY_OFFSET(region, 0x6C);
DISPLAY_OFFSET(field80, 0x80);
DISPLAY_OFFSET(field84, 0x84);
DISPLAY_OFFSET(color_a, 0x88);
DISPLAY_OFFSET(color_b, 0x8C);
#undef DISPLAY_OFFSET
typedef char StageCollisionRecordSize[sizeof(StageCollisionRecord)==0x7F0?1:-1];
typedef char StageCollisionStateOffset[offsetof(StageCollisionRecord,state)==0x446?1:-1];
