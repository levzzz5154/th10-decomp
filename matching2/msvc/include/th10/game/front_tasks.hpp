#pragma once
#include <stddef.h>
#include "th10/core/func_ctrl.hpp"

struct FrontTaskView {
    unsigned char reserved_0000[8];
    SchedulerTask* update_task;
    SchedulerTask* render_task;
    unsigned char reserved_0010[0x9ec8 - 0x10];
    void* front_resource;
};
typedef char FrontTaskView_offsets_check[
    offsetof(FrontTaskView, update_task) == 8 &&
    offsetof(FrontTaskView, render_task) == 12 &&
    offsetof(FrontTaskView, front_resource) == 0x9ec8 ? 1 : -1];

// Native LTCG supplies the receiver in EBX, preserving the retail entry.
extern "C" __declspec(noinline) int __stdcall
Front_RegisterTasks(FrontTaskView* state);
