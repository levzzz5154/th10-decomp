#define data_00491c10 stage_effect_data_00491c10
#define data_0047770c stage_effect_data_0047770c
#define data_00474c40 stage_effect_data_00474c40
#define data_004776e0 stage_effect_data_004776e0
#define data_00477704 stage_effect_data_00477704
#define g_player stage_effect_data_00477834
#define data_00477838 stage_effect_data_00477838
#define data_0047783c stage_effect_data_0047783c
#define data_00476f78 stage_effect_data_00476f78
#define data_00491fc4 stage_effect_data_00491fc4
#define data_00491fb8 stage_effect_data_00491fb8
#define data_00492590 stage_effect_data_00492590
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

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef data_004776e0
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
