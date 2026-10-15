// 0x00422150: register the pause menu's update task (primary list, priority
// 9) and draw task (secondary list, priority 0x2E), then start its frame
// timer at zero. Native LTCG passes the state in EBX.
//
// The including driver selects the code section.
#include "th10/game/timer_state_00422360.hpp"

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
int __fastcall Pause_UpdateTask_00422a90(void* state);
int __fastcall Pause_DrawTask_00422aa0(void* state);
extern FuncCtrl* g_func_ctrl;
extern const float g_game_speed;
}

__declspec(noinline) int __cdecl Pause_RegisterTasks(Pause* state) {
    SchedulerTask* task = SchedulerTask_Create(Pause_UpdateTask_00422a90);
    task->reserved_flags &= ~1u;
    task->context = state;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, 9);
    state->update_task = task;

    task = SchedulerTask_Create(Pause_DrawTask_00422aa0);
    task->context = state;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x2E);
    state->draw_task = task;

    FrameTimer& timer = state->timer;
    unsigned int flags = timer.flags;
    if ((flags & 1) == 0) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0.0f;
        timer.speed = &g_game_speed;
        timer.flags = flags | 1u;
    }
    timer.current = 0;
    timer.elapsed = 0.0f;
    timer.previous = -1;
    return 0;
}
