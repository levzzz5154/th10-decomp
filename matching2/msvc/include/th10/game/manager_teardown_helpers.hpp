#pragma once
// Teardown steps shared by the manager destructors: take a task off the
// scheduler under its lock, and unload one of the animation manager's script
// banks.
#include "th10/core/func_ctrl.hpp"
#include "th10/game/enemy_manager_dependencies_0040d530.hpp"
#include "th10/platform/thread_sync.hpp"

// The animation manager's table of loaded script banks (a view of the
// manager at g_sprt_ctrl).
struct AnimationBanks_00402440 {
    unsigned char reserved_000000[0x3ad06c];
    AnimationResource_00447810* banks[0x21];
};

void __cdecl operator delete(void* block);
extern "C" FuncCtrl* g_func_ctrl;

inline void RemoveSchedulerTask(SchedulerTask* task) {
    FuncCtrl* scheduler = g_func_ctrl;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        FuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}

inline void ReleaseAnimationBank(AnimationBanks_00402440* manager, int index) {
    if (index < 0)
        return;
    if ((unsigned int)index >= 0x21u)
        return;
    AnimationResource_00447810** slot = &manager->banks[index];
    if (*slot == 0)
        return;
    (*slot)->Release();
    delete *slot;
    *slot = 0;
}
