// 0x0044A060: create a scheduler callback with flag bit 1 cleared and register
// it on the primary list; the counterpart of the flag-setting wrapper beside it.
// Native LTCG gives the callback receiver in EAX and the priority in EDI.
#include "th10/core/func_ctrl.hpp"

extern "C" SchedulerTask* __stdcall SchedulerTask_Create(void*);
extern "C" FuncCtrl* g_func_ctrl;

struct SchedulerCreatePrimaryClear {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
#pragma code_seg(".text$79sched_gap_secondaryb")
__declspec(noinline) SchedulerTask*
SchedulerCreatePrimaryClear::Create(void* context, int priority) {
    SchedulerTask* task =
        SchedulerTask_Create((void*)this);
    task->context = context;
    *(unsigned int*)((char*)task + 4) &= ~2u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, priority);
    return task;
}
#pragma code_seg()
