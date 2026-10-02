// 0x0044A000..0x0044A02A: create a scheduler callback and register it on
// the primary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/game/scheduler.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void*);
extern "C" Scheduler* data_00491be4;

#pragma code_seg(".text$0044a000_fn")
__declspec(noinline) SchedulerTask*
__stdcall CreateEffectPrimary(void* context, int priority, void* routine) {
    SchedulerTask* task =
        SchedulerCallback_Create_00449ed0(routine);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    Scheduler_RegisterPrimary(data_00491be4, task, priority);
    return task;
}
#pragma code_seg()

// 0x0044A030..0x0044A05A: create a scheduler callback and register it on
// the secondary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/game/scheduler.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void*);
extern "C" Scheduler* data_00491be4;

#pragma code_seg(".text$0044a030_fn")
__declspec(noinline) SchedulerTask*
__stdcall CreateEffectSecondary(void* context, int priority, void* routine) {
    SchedulerTask* task =
        SchedulerCallback_Create_00449ed0(routine);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    Scheduler_RegisterSecondary(data_00491be4, task, priority);
    return task;
}
#pragma code_seg()

