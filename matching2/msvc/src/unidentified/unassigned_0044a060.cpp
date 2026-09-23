// 0x0044A060..0x0044A08A: create a callback task and register it on the
// primary scheduler list with task flag bit 1 clear. The private retail entry
// keeps the callback in EAX and the priority in EDI; the context is on stack.
#include "th10/game/scheduler.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(
    void* callback);
extern "C" Scheduler* data_00491be4;

struct SchedulerCreatePrimaryClearFlag_0044A060 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};

#pragma code_seg(".text$77schedulerprimaryclear")
__declspec(noinline) SchedulerTask*
SchedulerCreatePrimaryClearFlag_0044A060::Create(
    void* context, int priority) {
    SchedulerTask* task =
        SchedulerCallback_Create_00449ed0((void*)this);
    task->context = context;
    *(unsigned int*)((char*)task + 4) &= ~2u;
    Scheduler_RegisterPrimary(data_00491be4, task, priority);
    return task;
}
#pragma code_seg()
