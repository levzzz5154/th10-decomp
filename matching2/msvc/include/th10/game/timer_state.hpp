#pragma once
#include "th10/core/func_ctrl.hpp"
#include "th10/math/timer.hpp"

// The 0x2C8-byte state created by 0x00422360: two scheduler tasks, a frame
// timer, and two counter blocks.
struct Pause {
    unsigned flags;              // +0x000
    char pad_004[0x04];
    SchedulerTask* update_task;  // +0x008
    SchedulerTask* draw_task;    // +0x00C
    FrameTimer timer;            // +0x010
    int field_24;                // +0x024
    char pad_028[0x04];
    int field_2C;                // +0x02C
    char pad_030[0x80];
    int field_B0;                // +0x0B0
    char pad_0B4[0x40];
    int field_F4;                // +0x0F4
    int field_F8;                // +0x0F8
    int field_FC;                // +0x0FC
    char pad_100[0x04];
    int field_104;               // +0x104
    char pad_108[0x80];
    int field_188;               // +0x188
    char pad_18C[0x40];
    int field_1CC;               // +0x1CC
    int field_1D0;               // +0x1D0
    char pad_1D4[0xF4];
};

typedef char Pause_size_must_be_0x2C8[sizeof(Pause) == 0x2C8 ? 1 : -1];
