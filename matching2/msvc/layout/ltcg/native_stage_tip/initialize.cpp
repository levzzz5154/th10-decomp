#include "stage_tip.hpp"
#pragma code_seg(".text$a02initialize")
extern "C" __declspec(noinline) int __stdcall Hint_Initialize(Hint* manager) {
    SchedulerTask* primary = SchedulerCallback_Create_00449ed0((void*)0x4198A0);
    primary->context = manager;
    primary->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, primary, 0x19);
    manager->primary_task_008 = primary;

    SchedulerTask* secondary = SchedulerCallback_Create_00449ed0((void*)0x4198B0);
    secondary->reserved_flags &= ~1u;
    secondary->context = manager;
    FuncCtrl_RegisterSecondary(g_func_ctrl, secondary, 0x2C);
    manager->secondary_task_00C = secondary;
    manager->field_010 = 0;

    if (data_00491d6a) {
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6D8, 0);
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6C4, 1);
    }
    return 0;
}
#pragma code_seg()
