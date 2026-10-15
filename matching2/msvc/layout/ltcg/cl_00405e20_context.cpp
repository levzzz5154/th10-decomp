// Compiler context only; never selected as recovered game code.
#include "../../src/game/bullet/bullet_manager_initialize_00405e20.cpp"
#include "scheduler_register_anchors.cpp"
#include "../../src/platform/text_log.cpp"

#pragma code_seg(".text$90context")
int __stdcall BulletManagerInitializeContext_00405e20(BulletManager_00405e20** managers,
                                                      int count, SchedulerTask* task) {
    // Keeps the primary registration anchor in the link.
    int result = Scheduler_RegisterPrimary(data_00491be4, task, count);
    while (count--)
        result += BulletManager_Initialize_00405e20(*managers++);
    return result;
}
#pragma code_seg()
