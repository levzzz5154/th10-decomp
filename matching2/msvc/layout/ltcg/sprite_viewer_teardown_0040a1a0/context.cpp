// Compiler context only; never selected as recovered game code. The scheduler
// unlink and the worker stop are ABI anchors; the manager destructors are
// stand-ins whose real bodies are recovered (or still assembly) elsewhere.
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$07remove"
#include "../manager_teardown_native_0041adf0/scheduler.cpp"
#include "../../../src/platform/platform_stop_worker_0044c150.cpp"
#include "../../../src/game/sprite_viewer_teardown_0040a1a0.cpp"

extern "C" void __cdecl entry_free_00452422(void* memory);

// Each manager destructor unregisters its two scheduler tasks, as the real
// ones do; with every callee-saved register busy the receiver stays on the
// stack.
struct SpriteViewerStandInManager {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
};
static __forceinline void SpriteViewerStandIn_Unregister(SpriteViewerStandInManager* manager) {
    SchedulerTask* task = manager->update_task;
    Scheduler* scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownScheduler_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    task = manager->draw_task;
    scheduler = static_cast<Scheduler*>(data_00491be4);
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        ManagerTeardownScheduler_Remove_00449F60(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
}
#pragma code_seg(".text$00x1")
SpriteViewerLasers_0040a1a0::~SpriteViewerLasers_0040a1a0() {
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
#pragma code_seg(".text$00x2")
SpriteViewerBullets_0040a1a0::~SpriteViewerBullets_0040a1a0() {
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
#pragma code_seg(".text$06b")
SpriteViewerItems_0040a1a0::~SpriteViewerItems_0040a1a0() {
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
#pragma code_seg(".text$06c")
SpriteViewerEffects_0040a1a0::~SpriteViewerEffects_0040a1a0() {
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
#pragma code_seg(".text$06d")
SpriteViewerPlayer_0040a1a0::~SpriteViewerPlayer_0040a1a0() {
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
#pragma code_seg(".text$06e")
SpriteViewerPopups_0040a1a0::~SpriteViewerPopups_0040a1a0() {
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
// 0x0040D530 takes its receiver in EAX.
#pragma code_seg(".text$06a")
SpriteViewerEnemies_0040a940::~SpriteViewerEnemies_0040a940() {
    entry_free_00452422(this);
    SpriteViewerStandIn_Unregister(reinterpret_cast<SpriteViewerStandInManager*>(this));
}
#pragma code_seg()

// The owned-delete caller, 0x0040A410 in retail. It also destroys a worker
// array and a sprite array: the vector destructor iterator takes both member
// destructors' addresses, which keeps their public ECX receivers for the
// unwind funclets.
struct SpriteViewerWorkerArrayStandIn {
    SpriteViewerWorker_0040a940 workers[2];
    ~SpriteViewerWorkerArrayStandIn();
};
struct SpriteViewerSpriteArrayStandIn {
    SpriteViewerSprite_0040a940 sprites[2];
    ~SpriteViewerSpriteArrayStandIn();
};
#pragma code_seg(".text$05zarray")
__declspec(noinline) SpriteViewerWorkerArrayStandIn::~SpriteViewerWorkerArrayStandIn() {}
#pragma code_seg(".text$05zsprites")
__declspec(noinline) SpriteViewerSpriteArrayStandIn::~SpriteViewerSpriteArrayStandIn() {}
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall SpriteViewer_DestroyOwned_0040a1a0(SpriteViewer_0040a940* viewer,
                                                                       SpriteViewerWorkerArrayStandIn* workers,
                                                                       SpriteViewerSpriteArrayStandIn* sprites) {
    if (viewer) {
        viewer->~SpriteViewer_0040a940();
        ::operator delete(viewer);
    }
    workers->~SpriteViewerWorkerArrayStandIn();
    sprites->~SpriteViewerSpriteArrayStandIn();
}
#pragma code_seg()
