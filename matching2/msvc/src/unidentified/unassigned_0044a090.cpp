// 0x0044A090..0x0044A0BA: create a callback task and register it on the
// secondary scheduler list with task flag bit 1 clear. The private retail entry
// keeps the callback in EAX and the priority in EDI; the context is on stack.
#include "th10/game/scheduler.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(
    void* callback);
extern "C" Scheduler* data_00491be4;

struct SchedulerCreateSecondaryClearFlag_0044A090 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};

#pragma code_seg(".text$79schedulersecondaryclear")
__declspec(noinline) SchedulerTask*
SchedulerCreateSecondaryClearFlag_0044A090::Create(
    void* context, int priority) {
    SchedulerTask* task =
        SchedulerCallback_Create_00449ed0((void*)this);
    task->context = context;
    task->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, task, priority);
    return task;
}
#pragma code_seg()
