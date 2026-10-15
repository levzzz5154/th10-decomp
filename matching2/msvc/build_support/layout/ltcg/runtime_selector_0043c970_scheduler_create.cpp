// 0x0044A000..0x0044A02A: create a scheduler callback and register it on
// the primary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/core/func_ctrl.hpp"

extern "C" SchedulerTask* __stdcall SchedulerTask_Create(void*);
extern "C" FuncCtrl* g_func_ctrl;

#pragma code_seg(".text$76schedulerprimary")
__declspec(noinline) SchedulerTask*
__stdcall CreateEffectPrimary(void* context, int priority, void* routine) {
    SchedulerTask* task =
        SchedulerTask_Create(routine);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, priority);
    return task;
}
#pragma code_seg()

// 0x0044A030..0x0044A05A: create a scheduler callback and register it on
// the secondary list.  Native LTCG gives the callback receiver in EAX and
// the priority in EDI; the public stack home remains the callback context.
#include "th10/core/func_ctrl.hpp"

extern "C" SchedulerTask* __stdcall SchedulerTask_Create(void*);
extern "C" FuncCtrl* g_func_ctrl;

#pragma code_seg(".text$78schedulersecondary")
__declspec(noinline) SchedulerTask*
__stdcall CreateEffectSecondary(void* context, int priority, void* routine) {
    SchedulerTask* task =
        SchedulerTask_Create(routine);
    task->context = context;
    *(unsigned int*)((char*)task + 4) |= 2u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, priority);
    return task;
}
#pragma code_seg()

