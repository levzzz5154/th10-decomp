#ifndef TH10_GAME_LIFE_STOCK_ADD_004188A0_HPP
#define TH10_GAME_LIFE_STOCK_ADD_004188A0_HPP

#include "th10/platform/sound_queue.hpp"

// A handle to a running animation; zero when there is none.
struct AnimationHandle_004188a0 {
    unsigned int value;
};

// A running animation as the handle lookup sees it.
struct AnimationNode_004188a0 {
    AnimationNode_004188a0* object;      // +0x000: list nodes point at the animation
    AnimationNode_004188a0* next;        // +0x004
    unsigned char reserved_008[0x0C];
    AnimationNode_004188a0* children;    // +0x014
    int children_flagged;                // +0x018
    unsigned char reserved_01c[0x340];
    unsigned int flags;                  // +0x35C
};

// The animation manager's two running lists.
struct AnimationLists_004188a0 {
    unsigned char reserved_000[0x72DAD4];
    AnimationNode_004188a0* primary;     // +0x72DAD4
    int reserved_72dad8;
    AnimationNode_004188a0* secondary;   // +0x72DADC

    // 0x004491C0: find a running animation by handle.
    __declspec(noinline) AnimationNode_004188a0* Find(AnimationHandle_004188a0 handle);
    // 0x004492A0: mark an animation and its children for removal.
    __declspec(noinline) AnimationNode_004188a0* MarkForRemoval(AnimationHandle_004188a0 handle);
};

extern "C" AnimationLists_004188a0* data_00491c10;

// 0x00448D00: start script `index` of a resource as a new animation at the
// back of the primary list; the handle is written to `out` and returned.
__declspec(noinline) void** __stdcall AnimationManager_CreatePrimaryBack_00448d00(
    void* resource, void** out, int index, int render_bucket);

// One life icon of the side panel.
struct AnimationRecord_00413790 {
    unsigned int flags_0000;             // +0x000
    unsigned char pad_0004[0x3AC - 4];
};

// The side panel: nine life icons and the extend banner.
struct AnimationManager_00413790 {
    unsigned char pad_0000[0x4CDC];
    AnimationRecord_00413790 records_4cdc[9];
    unsigned char pad_6de8[0x9E18 - 0x6DE8];
    AnimationHandle_004188a0 extend_banner;  // +0x9E18
    unsigned char pad_9e1c[0x9EC8 - 0x9E1C];
    void* animation_resource;            // +0x9EC8

    // 0x00413790: show `count` life icons and hide the rest.
    __declspec(noinline) void SetActiveCount(int count);
};

extern "C" AnimationManager_00413790* data_0047770c;

// The run's counters; the power sits at +0x08 and the life stock at +0x30.
struct RunCounters_004188a0 {
    unsigned char reserved_00[8];
    short power;                         // +0x08: 100 is full, 20 per level
    unsigned char reserved_0a[0x30 - 0x0A];
    int lives;                           // +0x30

    // 0x00418930: add power, capped at 100; true when the level changed.
    __declspec(noinline) int AddPower(int amount);

    // 0x004188A0: add lives, capped at nine.
    __declspec(noinline) void AddLives(int amount);
};

extern "C" RunCounters_004188a0 data_00474c40;

#endif
