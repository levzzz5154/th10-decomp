// 0x00422150: register the timer state's update task (primary list, priority
// 9) and draw task (secondary list, priority 0x2E), then start its frame
// timer at zero. Native LTCG passes the state in EBX.
//
// The including driver selects the code section.
#include "th10/game/timer_state_00422360.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall TimerStateUpdate_00422a90(void* state);
int __fastcall TimerStateDraw_00422aa0(void* state);
extern Scheduler* data_00491be4;
extern const float data_00476f78;
}

__declspec(noinline) int __cdecl RegisterTimerState_00422150(TimerState_00422360* state) {
    SchedulerTask* task = SchedulerCallback_Create_00449ed0(TimerStateUpdate_00422a90);
    task->reserved_flags &= ~1u;
    task->context = state;
    Scheduler_RegisterPrimary(data_00491be4, task, 9);
    state->update_task = task;

    task = SchedulerCallback_Create_00449ed0(TimerStateDraw_00422aa0);
    task->context = state;
    task->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x2E);
    state->draw_task = task;

    FrameTimer& timer = state->timer;
    unsigned int flags = timer.flags;
    if ((flags & 1) == 0) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0.0f;
        timer.speed = &data_00476f78;
        timer.flags = flags | 1u;
    }
    timer.current = 0;
    timer.elapsed = 0.0f;
    timer.previous = -1;
    return 0;
}
