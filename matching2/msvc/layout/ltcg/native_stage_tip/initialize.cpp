#include "stage_tip.hpp"
#pragma code_seg(".text$a02initialize")
extern "C" __declspec(noinline) int __stdcall StageTipInitialize(StageTipManager* manager) {
    SchedulerTask* primary = SchedulerCallback_Create_00449ed0((void*)0x4198A0);
    primary->context = manager;
    primary->reserved_flags &= ~1u;
    Scheduler_RegisterPrimary(data_00491be4, primary, 0x19);
    manager->primary_task_008 = primary;

    SchedulerTask* secondary = SchedulerCallback_Create_00449ed0((void*)0x4198B0);
    secondary->reserved_flags &= ~1u;
    secondary->context = manager;
    Scheduler_RegisterSecondary(data_00491be4, secondary, 0x2C);
    manager->secondary_task_00C = secondary;
    manager->field_010 = 0;

    if (data_00491d6a) {
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6D8, 0);
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6C4, 1);
    }
    return 0;
}
#pragma code_seg()
