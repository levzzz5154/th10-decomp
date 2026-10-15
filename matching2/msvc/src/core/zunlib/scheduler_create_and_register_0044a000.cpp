// 0x0044A000..0x0044A02A: create a scheduler callback and register it on
// the primary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/core/func_ctrl.hpp"

extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void*);
extern "C" FuncCtrl* g_func_ctrl;

struct SchedulerCreatePrimary_0044A000 {
    __declspec(noinline) SchedulerTask* Create(void* context, int priority);
};
#pragma code_seg(".text$76schedulerprimary")
__declspec(noinline) SchedulerTask*
SchedulerCreatePrimary_0044A000::Create(void* context, int priority) {
    SchedulerTask* task =
        SchedulerCallback_Create_00449ed0((void*)this);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, priority);
    return task;
}
#pragma code_seg()
