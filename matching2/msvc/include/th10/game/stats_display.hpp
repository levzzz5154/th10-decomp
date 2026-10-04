#pragma once
#include "th10/game/scheduler.hpp"
// 0x8C-byte FPS display state, published at 0x00477708.
struct StatsDisplay {
    unsigned int flags;
    unsigned char reserved_004[8];
    SchedulerTask* draw_task;
    unsigned char reserved_010[0x8c-0x10];
    StatsDisplay();
};
extern "C" StatsDisplay* __cdecl StatsDisplay_Create();

typedef char StatsDisplay_size_must_be_0x8c[sizeof(StatsDisplay) == 0x8C ? 1 : -1];
typedef char StatsDisplay_draw_task_offset_must_be_0xc[offsetof(StatsDisplay, draw_task) == 0xC ? 1 : -1];
