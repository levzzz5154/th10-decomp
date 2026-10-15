#include "th10/game/card_tasks.hpp"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" {
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine callback);
int __fastcall CardPrimary_00409220(void* owner);
int __fastcall CardRender_00409230(void* owner);
int __fastcall CardTrailing_00409270(void* owner);
extern Scheduler* data_00491be4;
extern float data_00476f78;
}

// 0x004089C0 (211 bytes): register the manager's update and two render tasks.
// The retail receiver is in EBX; native LTCG selects that ABI from the caller.
#pragma code_seg(".text$02initializer")
int CardTasks_004089c0::InitializeTasks() {
    SchedulerTask* callback = SchedulerCallback_Create_00449ed0(
        CardPrimary_00409220);
    callback->context = this;
    callback->reserved_flags &= ~1u;
    Scheduler_RegisterPrimary(data_00491be4, callback, 0x16);
    primary_task = callback;

    callback = SchedulerCallback_Create_00449ed0(CardRender_00409230);
    callback->reserved_flags &= ~1u;
    callback->context = this;
    Scheduler_RegisterSecondary(data_00491be4, callback, 0x0e);
    secondary_task = callback;

    callback = SchedulerCallback_Create_00449ed0(CardTrailing_00409270);
    callback->context = this;
    callback->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, callback, 0x25);
    trailing_task = callback;

    // Finish publishing the callback before initializing the embedded timer.
    _ReadWriteBarrier();
    unsigned int flags = frame_timer.flags;
    if (!(flags & 1)) {
        flags |= 1;
        frame_timer.current = 0;
        frame_timer.previous = (int)0xfff0bdc1;
        frame_timer.elapsed = 0;
        frame_timer.speed = &data_00476f78;
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
