// 0x00405F70: retire the bullet pool, unregister its two scheduler tasks,
// and destroy all 2,001 bullet slots. The actual member array also makes
// MSVC generate the original exception cleanup; no explicit EH frame is used.
#include "th10/game/bullet_manager_teardown_00405f70.hpp"

#pragma code_seg(".text$03manager_dtor")
BulletManager_00405F70::~BulletManager_00405F70() {
    SchedulerTask* task = update_task;
    Scheduler* scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownScheduler_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = draw_task;
    scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownScheduler_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    data_00491c10->MarkResourceForRemoval(archive);
    data_004776f0 = 0;
}
#pragma code_seg()
