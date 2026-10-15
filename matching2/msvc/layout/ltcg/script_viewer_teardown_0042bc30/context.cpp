// Compiler context only; never selected as recovered game code. The scheduler
// unlink, the worker stop and the animation release are ABI anchors.
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$07remove"
#include "../manager_teardown_native_0041adf0/scheduler.cpp"
#include "../../../src/core/zunlib/platform_stop_worker_0044c150.cpp"
#include "../../../src/game/spttest/script_viewer_teardown_0042bc30.cpp"

// Stand-in for 0x00447810, whose real body is recovered in the animation
// resource cluster: an inner cursor takes ESI, which leaves the record in EDI.
extern "C" void __cdecl entry_free_00452422(void* memory);
struct ScriptViewerReleaseView {
    unsigned char reserved_000[0x108];
    void* resource;
    int entry_count;
    unsigned char reserved_110[0x10];
    void** entries;
};
#pragma code_seg(".text$06release")
void AnimationResource_00447810::Release() {
    ScriptViewerReleaseView* view = reinterpret_cast<ScriptViewerReleaseView*>(this);
    if (view->resource == 0)
        return;
    entry_free_00452422(this);
    for (int index = 0; index < view->entry_count; ++index) {
        void** entry = &view->entries[index];
        if (*entry != 0) {
            entry_free_00452422(*entry);
            *entry = 0;
        }
        if (entry[1] != 0) {
            entry_free_00452422(entry[1]);
            entry[1] = 0;
        }
    }
    if (view->resource != 0) {
        entry_free_00452422(view->resource);
        view->resource = 0;
    }
}
#pragma code_seg()

// The owned-delete caller, 0x0042BF80 in retail. It also destroys a worker
// array: the vector destructor iterator takes the worker destructor's address,
// which keeps that destructor's public ECX receiver for the unwind funclet.
struct ScriptViewerWorkerArrayStandIn {
    ScriptViewerWorker_0042be20 workers[2];
    ~ScriptViewerWorkerArrayStandIn();
};
#pragma code_seg(".text$05zarray")
__declspec(noinline) ScriptViewerWorkerArrayStandIn::~ScriptViewerWorkerArrayStandIn() {}
#pragma code_seg()
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall ScriptViewer_DestroyOwned_0042bc30(ScriptViewer_0042be20* viewer,
                                                                       ScriptViewerWorkerArrayStandIn* workers) {
    if (viewer) {
        viewer->~ScriptViewer_0042be20();
        ::operator delete(viewer);
    }
    workers->~ScriptViewerWorkerArrayStandIn();
}
#pragma code_seg()
