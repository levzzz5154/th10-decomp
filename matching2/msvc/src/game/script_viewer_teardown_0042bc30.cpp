// 0x0042BC30: tear the "Spt Test" debug screen down. Frees the script name
// list, unregisters both scheduler tasks, releases the loaded script, its
// parser and resource, unloads the two animation files the screen loaded and
// finally stops the loader thread (the worker member's destructor, which is
// also what the compiler-generated unwind funclet at 0x004653E0 runs).
// 0x0042BAD0: free every script name and the list itself; native LTCG passes
// the screen in ESI.
#include "th10/game/script_viewer_teardown_0042bc30.hpp"

#pragma code_seg(".text$10worker")
inline ScriptViewerWorker_0042be20::~ScriptViewerWorker_0042be20() {
    vtable = &platform_worker_vtable;
    reinterpret_cast<PlatformWorker*>(this)->Stop();
}
#pragma code_seg()

#pragma code_seg(".text$01names")
void ScriptViewer_0042be20::ClearScriptNames() {
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

#pragma code_seg(".text$03dtor")
ScriptViewer_0042be20::~ScriptViewer_0042be20() {
    ClearScriptNames();
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
    if (script_data) {
        free(script_data);
        script_data = 0;
    }
    if (parser) {
        delete parser;
        parser = 0;
    }
    if (resource) {
        resource->Retire(1);
        resource = 0;
    }
    data_00491c10->Unload(7);
    data_00491c10->Unload(6);
    data_00477844 = 0;
}
#pragma code_seg()
