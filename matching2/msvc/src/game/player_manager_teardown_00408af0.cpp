// 0x00408AF0: destroy the player manager. Its three effect animations are
// handed back to the animation manager, its three tasks leave the scheduler
// and the published pointer is cleared before the sprite pools are destroyed.
// The compiler-generated cleanups at 0x004655C0..0x004655F4 destroy the
// remaining pools if a sprite destructor throws.
#include "th10/game/player_manager_teardown_00408af0.hpp"

#pragma code_seg(".text$01a_dtor")
PlayerManager_00408af0::~PlayerManager_00408af0() {
    AnimationLookupContext* animations = data_00491c10;
    effects[0].Release(animations);
    effects[1].Release(animations);
    effects[2].Release(animations);

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
    task = trailing_task;
    scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownScheduler_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    data_004776f4 = 0;
}
#pragma code_seg()
