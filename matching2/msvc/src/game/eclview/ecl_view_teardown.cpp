// 0x0040A1A0: tear the "SprtView" debug screen down. Frees the script name
// list, unregisters both scheduler tasks, deletes the game managers the screen
// created, then destroys its sprite and stops its loader thread (the two
// member destructors, which the compiler-generated unwind funclets at
// 0x004657D0 and 0x004657DB also run).
// 0x00409EB0: free every script name and the list itself; native LTCG passes
// the screen in ESI.
#include "th10/game/ecl_view_teardown.hpp"

#pragma code_seg(".text$10worker")
inline EclViewWorker::~EclViewWorker() {
    vtable = &platform_worker_vtable;
    reinterpret_cast<PlatformWorker*>(this)->Stop();
}
#pragma code_seg()

#pragma code_seg(".text$00sprite")
inline EclViewSprite::~EclViewSprite() {
    void* owned = resource;
    if (owned) free(owned);
    resource = 0;
}
#pragma code_seg()

#pragma code_seg(".text$01names")
void EclView::ClearScriptNames() {
    if (script_names) {
        for (int i = 0; i < script_count; ++i) {
            if (script_names[i]) {
                free(const_cast<char*>(script_names[i]));
                script_names[i] = 0;
            }
        }
        if (script_names) {
            free(script_names);
            script_names = 0;
        }
        script_names = 0;
    }
}
#pragma code_seg()

// Destroy and free an owned manager, if the screen created it.
template <class T>
inline void EclView_DeleteOwned(T* const& owner) {
    T* object = owner;
    if (object) {
        object->~T();
        operator delete(object);
    }
}

#pragma code_seg(".text$03dtor")
EclView::~EclView() {
    ClearScriptNames();
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
    EclView_DeleteOwned(g_front);
    EclView_DeleteOwned(g_player);
    EclView_DeleteOwned(g_bullet_manager);
    EclView_DeleteOwned(g_enemy_ctrl);
    EclView_DeleteOwned(g_bomb);
    EclView_DeleteOwned(g_item_manager);
    EclView_DeleteOwned(g_smoll_score);
    g_ecl_view = 0;
}
#pragma code_seg()
