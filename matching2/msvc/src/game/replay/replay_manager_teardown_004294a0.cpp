// 0x004294A0: destroy the replay manager. The header, every stage's input
// pools, the summary and the eight stage blocks are freed, the three tasks
// leave the scheduler and the published pointer is cleared if it names this
// manager, before the list nodes are destroyed. The compiler-generated
// cleanup at 0x00465250 destroys the nodes if anything before them throws.
#include "th10/game/replay_manager_create_004296f0.hpp"

#pragma code_seg(".text$01a_dtor")
ReplayManager_004296f0::~ReplayManager_004296f0() {
    delete header;
    for (int stage = 0; stage < 8; ++stage)
        ClearStage(stage);
    delete summary;
    summary = 0;
    for (int i = 0; i < 8; ++i) {
        delete stage_data[i];
        stage_data[i] = 0;
    }

    SchedulerTask* task = update_task;
    if (task) {
        FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = trailing_task;
    if (task) {
        FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = draw_task;
    if (task) {
        FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    if (this == g_replay)
        g_replay = 0;
}
#pragma code_seg()
