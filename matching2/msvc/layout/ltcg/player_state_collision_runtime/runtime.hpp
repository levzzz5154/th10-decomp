#pragma once
#include <stddef.h>
#include "registration.hpp"
#include <math.h>
#include "timer.hpp"

struct PickupPoint { float x, y; };
struct Vec3 {
    float x, y, z;
    __declspec(noinline) int OutsideViewport(float horizontal_margin, float vertical_margin) const;
    Vec3 *SetPolar(float angle, float radius);
    Vec3 &operator+=(const Vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    void SnapToHundredths() {
        x = (float)floor(x * 100.0f) * 0.01f;
        y = (float)floor(y * 100.0f) * 0.01f;
    }
    Vec3 operator+(const Vec3 &other) const {
        Vec3 sum;
        sum.x = x + other.x;
        sum.y = y + other.y;
        sum.z = z + other.z;
        return sum;
    }
};
struct Motion {
    Vec3 position, velocity;
    // speed is also the orbit turn rate when flags bit 0 is set.
    float speed, angle, radius, radius_step;
    unsigned char flags;
    __declspec(noinline) void Advance();
    void Update();
};
typedef Vec3 PickupPosition;
struct PickupAnimation;
struct SpriteResource {
    unsigned char reserved_00[0x30];
    float width, height;
};
struct PickupAnimationNode {
    PickupAnimation* object;
    PickupAnimationNode* next;
    PickupAnimationNode* previous;
};
struct PickupHandle {
    // Retail preserves handle reloads and repeated retirement stores.
    volatile unsigned int value;
    __declspec(noinline) void StopAtFrame1();
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
    __declspec(noinline) PickupAnimation* Validate();
    __declspec(noinline) void Retire();
};
struct PickupAnimation {
    unsigned int id;
    PickupAnimation* manager_node_animation;
    unsigned char reserved_008[0x0c];
    PickupAnimationNode* child_next;
    PickupAnimationNode* child_previous;
    unsigned char reserved_01c[0x10];
    float angle;  // Entity::rotation.z at +0x2C
    unsigned char reserved_030[0x0c];
    float scale_x, scale_y;
    unsigned char reserved_044[0x304-0x44];
    unsigned short stop_frame;
    unsigned char reserved_306[0x340-0x306];
    PickupPosition position;
    unsigned char reserved_34c[0x35c-0x34c];
    unsigned int flags;
    unsigned char reserved_360[0x394-0x360];
    SpriteResource* sprite;
    unsigned char reserved_398[0x3ac-0x398];
};
struct PickupAnimationLists {
    unsigned char reserved_000000[0x72dad4];
    PickupAnimationNode* primary;
    PickupAnimationNode* primary_tail;
    PickupAnimationNode* secondary;
    __forceinline PickupAnimation* FindInBuckets(AnimationRef handle) {
        if (!handle.value) return 0;
        for (PickupAnimationNode* node=primary; node; node=node->next)
            if (node->object->id==handle.value) return node->object;
        for (PickupAnimationNode* node=secondary; node; node=node->next)
            if (node->object->id==handle.value) return node->object;
        return 0;
    }
    __declspec(noinline) PickupAnimation* Find(AnimationRef handle);
    __declspec(noinline) void* MarkForRemoval(AnimationRef handle);
};
struct PlayerState;
typedef PlayerState PickupManager;
struct PickupRecord;
typedef int (__fastcall *PickupFilter)(PickupManager*, PickupRecord*, const PickupPoint*);
struct PickupDescriptor {
    signed char period, phase;
    short value;
    PickupPoint spawn_offset;
    float width, height;
    float spawn_angle, spawn_speed;
    signed char ordinal;
    unsigned char type;
    short spawn_script, collected_script, spawn_sound;
    void (__fastcall *spawn_callback)(PlayerState*, PickupRecord*, int frame);
    void (__fastcall *effect_callback)(PlayerState*, PickupRecord*);
    unsigned char reserved_2c[4];
    PickupFilter filter;
};
struct PickupRecord {
    FrameTimer clock;
    Motion motion;
    // Snapshot the initial state where retail reads it once.
    volatile int state;
    PickupHandle handle, secondary_handle;
    unsigned int reserved_4c;
    int collected, initialized;
    PickupDescriptor* descriptor;
};
struct PickupRegionTimer {
    int previous, current;
    float elapsed;
    const float* speed;
    unsigned int flags;
};
struct PickupRegion {
    float radius, speed, angle, angle_step;
    float width, height;
    union {
        struct { PickupPosition center; unsigned char reserved_24[0x20]; };
        Motion motion;
    };
    PickupRegionTimer timer;
    int value, accumulated, limit, interval;
    unsigned int flags;
};
// The real player state owns both the motion records and collision regions.
struct FamiliarPosition {
    int x, y;
    Vec3 ToWorldPosition() const {
        Vec3 value = {x * 0.01f, y * 0.01f, 0.0f};
        return value;
    }
};
struct ScheduledFamiliar {
    unsigned char reserved_00[0x40];
    FamiliarPosition position;
    unsigned char reserved_48[0x48];
    int active;
    unsigned int reserved_94;
};
struct ScheduleSlot { PickupDescriptor* entries; int reserved; };
struct ScheduleFile { unsigned char reserved_000[0x110]; ScheduleSlot schedules[10]; };
struct PlayerState {
    unsigned char reserved_000[0x10];
    void* animation_resource;
    Entity animation;
    Vec3 spawn_origin;
    int fixed_x, fixed_y;
    unsigned char reserved_3d4[0x404-0x3d4];
    Vec3 primary_min, primary_max, primary_half;
    Vec3 full_size, outer_half, previous_position;
    unsigned char reserved_44c[8];
    int movement_direction;
    int phase;
    ScheduleFile* stage_schedule;
    FrameTimer stage_timer, state_timer, auxiliary_timer;
    PickupRecord pickups[128];
    ScheduledFamiliar familiars[4];
    unsigned int reserved_34fc;
    int familiar_level;
    int pending_3504;
    char pending_name_3508;
    unsigned char reserved_3509[3];
    PickupRegion regions[32];
    unsigned char reserved_428c[0x42f4-0x428c];
    int active_by_ordinal[6];
    FrameTimer invulnerability_timer;
    unsigned int reserved_4320;
    Vec3 secondary_half_min, secondary_half_max;
    Vec3 secondary_min, secondary_max;
    Vec3 size_min, size_max;
    struct HistoryPoint {
        int x, y;
        HistoryPoint& operator=(const HistoryPoint& other) { x = other.x; y = other.y; return *this; }
    } history[33];
    int alternate;
    __declspec(noinline) int Dispatch(int frame);
    __declspec(noinline) int UpdateSequence();
    __declspec(noinline) int Move();
};
struct PickupGameState { unsigned char reserved_0000[0x378c]; unsigned char flags; };
struct PickupConfig { unsigned char reserved_00[0x10]; int alternate_mode;
    unsigned char reserved_14[0x60-0x14]; int enabled; };
struct PickupPlayer {
    unsigned char reserved_00[0x28];
    int active;
    int reserved_2c;
    PickupPoint position;
    int reserved_38;
    float radius;
    int reserved_40;
    int mode;
    __declspec(noinline) int HitTest(const PickupPoint* point);
};
// Retail takes an optional output word in ECX and the three inputs on the
// stack. MSVC 7.1 supports the observed null receiver at this boundary.
struct PickupSweepResult {
    int value;
    __declspec(noinline) int Sweep(PickupManager*, const PickupPoint*, const PickupPoint*);
};
extern "C" {
extern PickupPlayer* data_004776ec;
extern PickupGameState* data_004776f4;
extern PickupConfig* data_00477704;
extern int data_00474c68, data_00474c44;
extern void* data_00491c10;
extern float data_00476f78;
}
__declspec(noinline) AnimationRef __stdcall Pickup_CreatePrimaryBack(
    void* resource, int script, int layer);
extern "C" __declspec(noinline) PickupRegion* __fastcall Pickup_AllocateIndicator(
    unsigned int unused, PickupManager*, const PickupPosition* volatile position,
    unsigned int radius_bits, unsigned int speed_bits, int countdown, unsigned int value);

#define PICKUP_CHECK(name, expression) typedef char name[(expression) ? 1 : -1]
PICKUP_CHECK(animation_reference_size, sizeof(AnimationRef)==4);
PICKUP_CHECK(player_size, sizeof(PlayerState)==0x4478);
PICKUP_CHECK(player_state_timer, offsetof(PlayerState,state_timer)==0x474);
PICKUP_CHECK(player_stage_current, offsetof(PlayerState,stage_timer)+offsetof(FrameTimer,current)==0x464);
PICKUP_CHECK(descriptor_callback, offsetof(PickupDescriptor,effect_callback)==0x28);
PICKUP_CHECK(record_secondary_handle, offsetof(PickupRecord,secondary_handle)==0x48);
PICKUP_CHECK(record_size, sizeof(PickupRecord)==0x5c);
PICKUP_CHECK(record_position, offsetof(PickupRecord,motion)+offsetof(Motion,position)==0x14);
PICKUP_CHECK(record_handle, offsetof(PickupRecord,handle)==0x44);
PICKUP_CHECK(record_descriptor, offsetof(PickupRecord,descriptor)==0x58);
PICKUP_CHECK(region_size, sizeof(PickupRegion)==0x6c);
PICKUP_CHECK(region_timer, offsetof(PickupRegion,timer)==0x44);
PICKUP_CHECK(manager_records, offsetof(PickupManager,pickups)==0x49c);
PICKUP_CHECK(manager_regions, offsetof(PickupManager,regions)==0x350c);
PICKUP_CHECK(animation_angle, offsetof(PickupAnimation,angle)==0x2c);
PICKUP_CHECK(animation_child_previous, offsetof(PickupAnimation,child_previous)==0x18);
PICKUP_CHECK(animation_size, sizeof(PickupAnimation)==0x3ac);
PICKUP_CHECK(animation_position, offsetof(PickupAnimation,position)==0x340);
PICKUP_CHECK(animation_sprite, offsetof(PickupAnimation,sprite)==0x394);
PICKUP_CHECK(animation_stop, offsetof(PickupAnimation,stop_frame)==0x304);
PICKUP_CHECK(animation_flags, offsetof(PickupAnimation,flags)==0x35c);
PICKUP_CHECK(animation_node_size, sizeof(PickupAnimationNode)==0x0c);
PICKUP_CHECK(spawn_origin_offset, offsetof(PlayerState,spawn_origin)==0x3c0);
PICKUP_CHECK(familiar_first_x, offsetof(PlayerState,familiars)+offsetof(ScheduledFamiliar,position)==0x32dc);
PICKUP_CHECK(familiar_stride, sizeof(ScheduledFamiliar)==0x98);
PICKUP_CHECK(descriptor_spawn_callback, offsetof(PickupDescriptor,spawn_callback)==0x24);
PICKUP_CHECK(descriptor_spawn_script, offsetof(PickupDescriptor,spawn_script)==0x1e);
PICKUP_CHECK(descriptor_size, sizeof(PickupDescriptor)==0x34);

PICKUP_CHECK(sequence_running, offsetof(PlayerState,phase)==0x458);
PICKUP_CHECK(sequence_clock, offsetof(PlayerState,stage_timer)==0x460);
PICKUP_CHECK(sequence_pending, offsetof(PlayerState,pending_3504)==0x3504);
PICKUP_CHECK(sequence_pending_name, offsetof(PlayerState,pending_name_3508)==0x3508);

PICKUP_CHECK(player_animation, offsetof(PlayerState,animation)==0x14);
PICKUP_CHECK(player_fixed_y, offsetof(PlayerState,fixed_y)==0x3d0);
PICKUP_CHECK(player_primary_min, offsetof(PlayerState,primary_min)==0x404);
PICKUP_CHECK(player_primary_half, offsetof(PlayerState,primary_half)==0x41c);
PICKUP_CHECK(player_full_size, offsetof(PlayerState,full_size)==0x428);
PICKUP_CHECK(player_previous_position, offsetof(PlayerState,previous_position)==0x440);
PICKUP_CHECK(familiar_active, offsetof(ScheduledFamiliar,active)==0x90);
PICKUP_CHECK(region_motion, offsetof(PickupRegion,motion)==0x18);
#undef PICKUP_CHECK
