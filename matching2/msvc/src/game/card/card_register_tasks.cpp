#include "th10/game/card_tasks.hpp"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" {
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine callback);
int __fastcall CardPrimary(void* owner);
int __fastcall CardRender(void* owner);
int __fastcall CardTrailing(void* owner);
extern FuncCtrl* g_func_ctrl;
extern float g_game_speed;
}

// 0x004089C0 (211 bytes): register the manager's update and two render tasks.
// The retail receiver is in EBX; native LTCG selects that ABI from the caller.
#pragma code_seg(".text$02initializer")
int CardTasks::InitializeTasks() {
    SchedulerTask* callback = SchedulerTask_Create(
        CardPrimary);
    callback->context = this;
    callback->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, callback, 0x16);
    primary_task = callback;

    callback = SchedulerTask_Create(CardRender);
    callback->reserved_flags &= ~1u;
    callback->context = this;
    FuncCtrl_RegisterSecondary(g_func_ctrl, callback, 0x0e);
    secondary_task = callback;

    callback = SchedulerTask_Create(CardTrailing);
    callback->context = this;
    callback->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, callback, 0x25);
    trailing_task = callback;

    // Finish publishing the callback before initializing the embedded timer.
    _ReadWriteBarrier();
    unsigned int flags = frame_timer.flags;
    if (!(flags & 1)) {
        flags |= 1;
        frame_timer.current = 0;
        frame_timer.previous = (int)0xfff0bdc1;
        frame_timer.elapsed = 0;
        frame_timer.speed = &g_game_speed;
        frame_timer.flags = flags;
    }
    // Lazy defaults and the subsequent reset are distinct observed writes.
    _ReadWriteBarrier();
    frame_timer.current = 0;
    frame_timer.elapsed = 0;
    frame_timer.previous = -1;
    return 0;
}
#pragma code_seg()
