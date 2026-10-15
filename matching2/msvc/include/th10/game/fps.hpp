#pragma once
#include "th10/core/func_ctrl.hpp"
// 0x8C-byte FPS display state, published at 0x00477708.
struct FPS {
    unsigned int flags;
    unsigned char reserved_004[8];
    SchedulerTask* draw_task;
    unsigned char reserved_010[0x8c-0x10];
    FPS();
};
extern "C" FPS* __cdecl FPS_Create();

typedef char FPS_size_must_be_0x8c[sizeof(FPS) == 0x8C ? 1 : -1];
typedef char FPS_draw_task_offset_must_be_0xc[offsetof(FPS, draw_task) == 0xC ? 1 : -1];
