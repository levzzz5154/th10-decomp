#pragma once
#include <stddef.h>

struct PickupPoint { float x, y; };
struct PickupPosition { float x, y, z; };
struct PickupClock {
    int previous, current;
    __declspec(noinline) int AtInterval(int interval);
};
struct PickupAnimation;
struct PickupAnimationNode {
    PickupAnimation* object;
    PickupAnimationNode* next;
    PickupAnimationNode* previous;
};
struct PickupHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) PickupAnimation* Validate();
    __declspec(noinline) void Retire();
};
struct PickupAnimation {
    unsigned int id;
    unsigned char reserved_004[0x10];
    PickupAnimationNode* child_next;
    PickupAnimationNode* child_previous;
    unsigned char reserved_01c[0x10];
    float angle;  // Entity::rotation.z at +0x2C
    unsigned char reserved_030[0x2d4];
    unsigned short stop_frame;
    unsigned char reserved_306[0x56];
    unsigned int flags;
};
struct PickupAnimationLists {
    unsigned char reserved_000000[0x72dad4];
    PickupAnimationNode* primary;
    PickupAnimationNode* primary_tail;
    PickupAnimationNode* secondary;
    __declspec(noinline) PickupAnimation* Find(PickupHandle handle);
    __declspec(noinline) void* MarkForRemoval(PickupHandle handle);
};
struct PickupManager;
struct PickupRecord;
typedef int (__fastcall *PickupFilter)(PickupManager*, PickupRecord*, const PickupPoint*);
struct PickupDescriptor {
    short reserved_00, value;
    unsigned char reserved_04[8];
    float width, height;
    unsigned char reserved_14[9];
    unsigned char type;
    unsigned char reserved_1e[2];
    short collected_script;
    unsigned char reserved_22[0x0e];
    PickupFilter filter;
};
struct PickupRecord {
    PickupClock clock;
    unsigned char reserved_08[0x0c];
    PickupPosition position;
    // The transition scale aliases position.z in the retail record.
    unsigned char reserved_20[0x0c];
    float velocity_scale;
    unsigned char reserved_30[0x10];
    int state;
    PickupHandle handle;
    unsigned char reserved_48[8];
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
    float radius, speed, angle;
    unsigned int reserved_0c;
    float width, height;
    PickupPosition center;
    unsigned char reserved_24[0x20];
    PickupRegionTimer timer;
    int value, accumulated, limit, interval;
    unsigned int flags;
};
struct PickupManager {
    unsigned char reserved_000[0x10];
    void* animation_resource;
    unsigned char reserved_014[0x474-0x14];
    int generation_begin, generation_end;
    unsigned char reserved_47c[0x20];
    PickupRecord pickups[128];
    unsigned char reserved_329c[0x270];
    PickupRegion regions[32];
};
struct PickupGameState { unsigned char reserved_0000[0x378c]; unsigned char flags; };
struct PickupConfig { unsigned char reserved_00[0x10]; int alternate_mode; };
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
__declspec(noinline) PickupHandle* __stdcall Pickup_CreatePrimaryBack(
    void* resource, PickupHandle* output, int script, int layer);
extern "C" __declspec(noinline) PickupRegion* __fastcall Pickup_AllocateIndicator(
    unsigned int unused, PickupManager*, const PickupPosition* volatile position,
    unsigned int radius_bits, unsigned int speed_bits, int countdown, unsigned int value);

#define PICKUP_CHECK(name, expression) typedef char name[(expression) ? 1 : -1]
PICKUP_CHECK(record_size, sizeof(PickupRecord)==0x5c);
PICKUP_CHECK(record_position, offsetof(PickupRecord,position)==0x14);
PICKUP_CHECK(record_handle, offsetof(PickupRecord,handle)==0x44);
PICKUP_CHECK(record_descriptor, offsetof(PickupRecord,descriptor)==0x58);
PICKUP_CHECK(region_size, sizeof(PickupRegion)==0x6c);
PICKUP_CHECK(region_timer, offsetof(PickupRegion,timer)==0x44);
PICKUP_CHECK(manager_records, offsetof(PickupManager,pickups)==0x49c);
PICKUP_CHECK(manager_regions, offsetof(PickupManager,regions)==0x350c);
PICKUP_CHECK(animation_angle, offsetof(PickupAnimation,angle)==0x2c);
PICKUP_CHECK(animation_child_previous, offsetof(PickupAnimation,child_previous)==0x18);
PICKUP_CHECK(animation_stop, offsetof(PickupAnimation,stop_frame)==0x304);
PICKUP_CHECK(animation_flags, offsetof(PickupAnimation,flags)==0x35c);
PICKUP_CHECK(animation_node_size, sizeof(PickupAnimationNode)==0x0c);
#undef PICKUP_CHECK
