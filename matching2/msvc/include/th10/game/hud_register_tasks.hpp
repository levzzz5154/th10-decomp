#pragma once
#include <stddef.h>
#include "th10/game/scheduler.hpp"

struct ItemFrontState_00413980 {
    unsigned char reserved_0000[8];
    SchedulerTask* update_task;
    SchedulerTask* render_task;
    unsigned char reserved_0010[0x9ec8 - 0x10];
    void* front_resource;
};
typedef char ItemFrontState_00413980_offsets_check[
    offsetof(ItemFrontState_00413980, update_task) == 8 &&
    offsetof(ItemFrontState_00413980, render_task) == 12 &&
    offsetof(ItemFrontState_00413980, front_resource) == 0x9ec8 ? 1 : -1];

// Native LTCG supplies the receiver in EBX, preserving the retail entry.
extern "C" __declspec(noinline) int __stdcall
Hud_RegisterTasks(ItemFrontState_00413980* state);
