// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4132c0.cpp"
#include "scheduler_register_anchors.cpp"

#pragma code_seg(".text$30context")
int __stdcall TaskOwnerContext_004132c0(TaskOwner** owners, int count,
                                         SchedulerTask* task) {
    // Keeps the primary registration anchor in the link.
    int result = FuncCtrl_RegisterPrimary(g_func_ctrl, task, count);
    while (count--)
        result += (*owners++)->InstallDrawTask();
    return result;
}
#pragma code_seg()
