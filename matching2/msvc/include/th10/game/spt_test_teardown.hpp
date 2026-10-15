#pragma once
#include "th10/game/spt_test.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/platform/worker.hpp"

void __cdecl operator delete(void* block);

// The animation manager's loaded-file slots, as far as the screen unloads them.
struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};
struct SptTestAnimations_0042be20 {
    unsigned char reserved_000000[0x3AD06C];
    AnimationResource_00447810* slots[0x21];

    void Unload(int index) {
        AnimationResource_00447810** slot = &slots[index];
        if (*slot != 0) {
            (*slot)->Release();
            operator delete(*slot);
            *slot = 0;
        }
    }
};

extern "C" SptTestAnimations_0042be20* data_00491c10;
extern "C" void* data_00491be4;          // the scheduler
// 0x00449F60: unlink one task; the caller holds the scheduler lock.
__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler*, SchedulerTask*);
