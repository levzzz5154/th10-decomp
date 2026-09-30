#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"

struct SchedulerTask;
struct Resource_0043e5a0;

struct EffectTimer_0042b6f0 {
    volatile int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __forceinline void Tick();
};

struct EffectDrop_0042b6f0 {
    float position;
    unsigned char pad_004[8];
    EffectTimer_0042b6f0 timer;
    unsigned char pad_020[8];
    unsigned char active;
    unsigned char pad_029[0x17];
};
typedef char EffectDrop_0042b6f0_size[sizeof(EffectDrop_0042b6f0) == 0x40 ? 1 : -1];

struct EffectPool_0042b6f0 {
    unsigned char pad_000[0x08];
    SchedulerTask* update_task;          // +0x008
    SchedulerTask* draw_task;            // +0x00C
    Resource_0043e5a0* resource;         // +0x010
    unsigned char pad_014[0x04];
    Entity sprite;                       // +0x018
    unsigned char pad_3C4[0x10];
    EffectDrop_0042b6f0 drops[0x2D3];
    __declspec(noinline) int UpdateDrops();
    __declspec(noinline) int Update();
    __declspec(noinline) int Initialize();
};
typedef char EffectPool_0042b6f0_drops_offset[offsetof(EffectPool_0042b6f0, drops) == 0x3D4 ? 1 : -1];
