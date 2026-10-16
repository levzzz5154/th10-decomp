// 0x00408AF0: destroy the spell-card manager (Card, card.cpp). Its three effect animations are
// handed back to the animation manager, its three tasks leave the scheduler
// and the published pointer is cleared before the sprite pools are destroyed.
// The compiler-generated cleanups at 0x004655C0..0x004655F4 destroy the
// remaining pools if a sprite destructor throws.
#include "th10/game/card_destructor.hpp"

#pragma code_seg(".text$01a_dtor")
Card2::~Card2() {
    AnimationLookupContext* animations = g_sprt_ctrl;
    effects[0].Release(animations);
    effects[1].Release(animations);
    effects[2].Release(animations);

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
    task = trailing_task;
    scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    g_card = 0;
}
#pragma code_seg()
