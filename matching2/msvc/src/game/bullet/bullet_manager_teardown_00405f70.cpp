// 0x00405F70: retire the bullet pool, unregister its two scheduler tasks,
// and destroy all 2,001 bullet slots. The actual member array also makes
// MSVC generate the original exception cleanup; no explicit EH frame is used.
#include "th10/game/bullet_manager_teardown_00405f70.hpp"

#pragma code_seg(".text$03manager_dtor")
BulletManager_00405F70::~BulletManager_00405F70() {
    SchedulerTask* task = update_task;
    FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = draw_task;
    scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    g_sprt_ctrl->MarkResourceForRemoval(archive);
    g_bullet_manager = 0;
}
#pragma code_seg()
