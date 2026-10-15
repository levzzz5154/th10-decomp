// Compiler context only; never selected as recovered game code. The scheduler
// unlink and the worker stop are ABI anchors; the manager destructors are
// stand-ins whose real bodies are recovered (or still assembly) elsewhere.
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$07remove"
#include "../manager_teardown_native_0041adf0/scheduler.cpp"
#include "../../../src/core/zunlib/platform_stop_worker_0044c150.cpp"
#include "../../../src/game/eclview/ecl_view_teardown.cpp"

extern "C" void __cdecl entry_free_00452422(void* memory);

// Each manager destructor unregisters its two scheduler tasks, as the real
// ones do; with every callee-saved register busy the receiver stays on the
// stack.
struct EclViewStandInManager {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
};
static __forceinline void EclViewStandIn_Unregister(EclViewStandInManager* manager) {
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
EclViewLasers_0040a1a0::~EclViewLasers_0040a1a0() {
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
#pragma code_seg(".text$00x2")
EclViewBullets_0040a1a0::~EclViewBullets_0040a1a0() {
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
#pragma code_seg(".text$06b")
EclViewItems_0040a1a0::~EclViewItems_0040a1a0() {
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
#pragma code_seg(".text$06c")
EclViewEffects_0040a1a0::~EclViewEffects_0040a1a0() {
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
#pragma code_seg(".text$06d")
EclViewPlayer_0040a1a0::~EclViewPlayer_0040a1a0() {
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
#pragma code_seg(".text$06e")
EclViewPopups_0040a1a0::~EclViewPopups_0040a1a0() {
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
// 0x0040D530 takes its receiver in EAX.
#pragma code_seg(".text$06a")
EclViewEnemies_0040a940::~EclViewEnemies_0040a940() {
    entry_free_00452422(this);
    EclViewStandIn_Unregister(reinterpret_cast<EclViewStandInManager*>(this));
}
#pragma code_seg()

// The owned-delete caller, 0x0040A410 in retail. It also destroys a worker
// array and a sprite array: the vector destructor iterator takes both member
// destructors' addresses, which keeps their public ECX receivers for the
// unwind funclets.
struct EclViewWorkerArrayStandIn {
    EclViewWorker_0040a940 workers[2];
    ~EclViewWorkerArrayStandIn();
};
struct EclViewSpriteArrayStandIn {
    EclViewSprite_0040a940 sprites[2];
    ~EclViewSpriteArrayStandIn();
};
#pragma code_seg(".text$05zarray")
__declspec(noinline) EclViewWorkerArrayStandIn::~EclViewWorkerArrayStandIn() {}
#pragma code_seg(".text$05zsprites")
__declspec(noinline) EclViewSpriteArrayStandIn::~EclViewSpriteArrayStandIn() {}
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall EclView_DestroyOwned_0040a1a0(EclView_0040a940* viewer,
                                                                       EclViewWorkerArrayStandIn* workers,
                                                                       EclViewSpriteArrayStandIn* sprites) {
    if (viewer) {
        viewer->~EclView_0040a940();
        ::operator delete(viewer);
    }
    workers->~EclViewWorkerArrayStandIn();
    sprites->~EclViewSpriteArrayStandIn();
}
#pragma code_seg()
