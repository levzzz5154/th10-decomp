// 0x004145F0: destroy the HUD. Its contents are released, its two
// tasks leave the scheduler, its banner and eight effect animations are
// handed back to the animation manager along with everything still using its
// caption file, and the published pointer is cleared before the sprites are
// destroyed. The compiler-generated cleanups at 0x004656A0..0x00465740
// destroy the remaining sprites if a sprite destructor throws.
#include "th10/game/front_destroy.hpp"

#pragma code_seg(".text$01a_dtor")
Front::~Front() {
    Front_ReleaseContents(this);

    SchedulerTask* task = update_task;
    FuncCtrl* scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = draw_task;
    scheduler = static_cast<FuncCtrl*>(g_func_ctrl);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownFuncCtrl_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    update_task = 0;

    AnimationLookupContext* animations = g_sprt_ctrl;
    banner.Release(animations);
    HudAnimation* effect = effects;
    int remaining = 8;
    do {
        effect->ReleaseInPlace(animations);
        ++effect;
    } while (--remaining);
    AnimationRemoval(animations)->MarkResourceForRemoval(captions);
    g_front = 0;
}
#pragma code_seg()
