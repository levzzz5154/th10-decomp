// Compiler context only; never selected as recovered game code. The scheduler
// unlink, the worker stop and the animation release are ABI anchors.
#define TH10_SCHEDULER_REMOVE_ONLY
#define TH10_SCHEDULER_REMOVE_CODE_SEG ".text$07remove"
#include "../manager_teardown_native_0041adf0/scheduler.cpp"
#include "../../../../src/core/zunlib/platform_stop_worker_0044c150.cpp"
#include "../../../../src/game/spttest/spt_test_teardown.cpp"

// Stand-in for 0x00447810, whose real body is recovered in the animation
// resource cluster: an inner cursor takes ESI, which leaves the record in EDI.
extern "C" void __cdecl crt_free(void* memory);
struct SptTestReleaseView {
    unsigned char reserved_000[0x108];
    void* resource;
    int entry_count;
    unsigned char reserved_110[0x10];
    void** entries;
};
#pragma code_seg(".text$06release")
void AnimationResource_00447810::Release() {
    SptTestReleaseView* view = reinterpret_cast<SptTestReleaseView*>(this);
    if (view->resource == 0)
        return;
    crt_free(this);
    for (int index = 0; index < view->entry_count; ++index) {
        void** entry = &view->entries[index];
        if (*entry != 0) {
            crt_free(*entry);
            *entry = 0;
        }
        if (entry[1] != 0) {
            crt_free(entry[1]);
            entry[1] = 0;
        }
    }
    if (view->resource != 0) {
        crt_free(view->resource);
        view->resource = 0;
    }
}
#pragma code_seg()

// The owned-delete caller, 0x0042BF80 in retail. It also destroys a worker
// array: the vector destructor iterator takes the worker destructor's address,
// which keeps that destructor's public ECX receiver for the unwind funclet.
struct SptTestWorkerArrayStandIn {
    SptTestWorker workers[2];
    ~SptTestWorkerArrayStandIn();
};
#pragma code_seg(".text$05zarray")
__declspec(noinline) SptTestWorkerArrayStandIn::~SptTestWorkerArrayStandIn() {}
#pragma code_seg()
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall SptTest_DestroyOwned_0042bc30(SptTest_0042be20* viewer,
                                                                       SptTestWorkerArrayStandIn* workers) {
    if (viewer) {
        viewer->~SptTest_0042be20();
        ::operator delete(viewer);
    }
    workers->~SptTestWorkerArrayStandIn();
}
#pragma code_seg()
