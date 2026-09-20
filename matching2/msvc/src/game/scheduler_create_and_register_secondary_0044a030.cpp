// 0x0044A030..0x0044A05A: create a scheduler callback and register it on
// the secondary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/game/scheduler.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void*);
extern "C" Scheduler* data_00491be4;

struct SchedulerCreateSecondary_0044A030 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
#pragma code_seg(".text$78schedulersecondary")
__declspec(noinline) SchedulerTask*
SchedulerCreateSecondary_0044A030::Create(void* context, int priority) {
    SchedulerTask* task =
        SchedulerCallback_Create_00449ed0((void*)this);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    Scheduler_RegisterSecondary(data_00491be4, task, priority);
    return task;
}
#pragma code_seg()
