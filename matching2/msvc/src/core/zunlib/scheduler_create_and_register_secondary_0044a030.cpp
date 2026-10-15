// 0x0044A030..0x0044A05A: create a scheduler callback and register it on
// the secondary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/core/func_ctrl.hpp"

extern "C" SchedulerTask* __stdcall SchedulerTask_Create(void*);
extern "C" FuncCtrl* g_func_ctrl;

struct SchedulerCreateSecondary {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
#pragma code_seg(".text$78schedulersecondary")
__declspec(noinline) SchedulerTask*
SchedulerCreateSecondary::Create(void* context, int priority) {
    SchedulerTask* task =
        SchedulerTask_Create((void*)this);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, priority);
    return task;
}
#pragma code_seg()
