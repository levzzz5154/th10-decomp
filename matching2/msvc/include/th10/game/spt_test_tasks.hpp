#pragma once
#include "th10/game/scheduler.hpp"

struct SptTestTaskView {
    unsigned char reserved_00[0x08];
    SchedulerTask* update_task;             // +0x08
    SchedulerTask* draw_task;               // +0x0C

    __declspec(noinline) int InstallTasks();
};
