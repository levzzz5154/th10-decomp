// 0x00413350: create and register the FPS display.
#include <string.h>
#include "th10/game/fps.hpp"
extern "C" {
extern FPS* g_fps;
extern FuncCtrl* g_func_ctrl;
int __fastcall FPS_OnDraw(void*);
}
// Set up the task's embedded node before it enters a scheduler list.
inline void InitializeTaskLink(TaskLink& link, SchedulerTask* task) {
    link.task = task;
    link.next = 0;
    link.previous = 0;
}
struct FPSTask : SchedulerTask {
    FPSTask() {
        on_tick = 0;
        on_register = 0;
        on_remove = 0;
        priority = 0;
        heap_owned = 0;
        InitializeTaskLink(link, this);
    }
};
inline FPS::FPS() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    g_fps = this;
}
#pragma code_seg(".text$01factory")
extern "C" __declspec(noinline) FPS* __cdecl FPS_Create() {
    FPS* display = new FPS;
    SchedulerTask* task = new FPSTask;
    task->on_tick = FPS_OnDraw;
    task->on_register = 0;
    task->on_remove = 0;
    task->context = display;
    task->heap_owned = 1;
    task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 47);
    display->draw_task = task;
    return display;
}
#pragma code_seg()
