#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"

struct SchedulerTask;
struct Resource_0043e5a0;

struct SmollScoreTimer {
    volatile int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    __forceinline void Tick();
};

struct SmollScorePopup {
    float position;
    unsigned char pad_004[8];
    SmollScoreTimer timer;
    unsigned char pad_020[8];
    unsigned char active;
    unsigned char pad_029[0x17];
};
typedef char EffectDrop_0042b6f0_size[sizeof(SmollScorePopup) == 0x40 ? 1 : -1];

struct SmollScoreView {
    unsigned char pad_000[0x08];
    SchedulerTask* update_task;          // +0x008
    SchedulerTask* draw_task;            // +0x00C
    Resource_0043e5a0* resource;         // +0x010
    unsigned char pad_014[0x04];
    Entity sprite;                       // +0x018
    unsigned char pad_3C4[0x10];
    SmollScorePopup popups[0x2D3];
    __declspec(noinline) int UpdatePopups();
    __declspec(noinline) int Update();
    __declspec(noinline) int Initialize();
};
typedef char SmollScoreView_popups_offset[offsetof(SmollScoreView, popups) == 0x3D4 ? 1 : -1];
