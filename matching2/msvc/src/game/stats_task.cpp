// 0x00413350: create and register the FPS display.
#include <string.h>
#include "th10/game/stats_display.hpp"
extern "C" {
extern StatsDisplay* data_00477708;
extern Scheduler* data_00491be4;
int __fastcall FpsDrawCallback_00413690(void*);
}
// Set up the task's embedded node before it enters a scheduler list.
inline void InitializeTaskLink(TaskLink& link, SchedulerTask* task) {
    link.task = task;
    link.next = 0;
    link.previous = 0;
}
struct StatsDisplayTask : SchedulerTask {
    StatsDisplayTask() {
        on_tick = 0;
        on_register = 0;
        on_remove = 0;
        priority = 0;
        heap_owned = 0;
        InitializeTaskLink(link, this);
    }
};
inline StatsDisplay::StatsDisplay() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_00477708 = this;
}
#pragma code_seg(".text$01factory")
extern "C" __declspec(noinline) StatsDisplay* __cdecl StatsDisplay_Create() {
    StatsDisplay* display = new StatsDisplay;
    SchedulerTask* task = new StatsDisplayTask;
    task->on_tick = FpsDrawCallback_00413690;
    task->on_register = 0;
    task->on_remove = 0;
    task->context = display;
    task->heap_owned = 1;
    task->reserved_flags |= 1;
    Scheduler_RegisterSecondary(data_00491be4, task, 47);
    display->draw_task = task;
    return display;
}
#pragma code_seg()
