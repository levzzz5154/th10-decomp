// 0x0040D530..0x0040D65B (300 bytes): EnemyManager_Destroy
//
// Runs the manager's list release, unregisters both scheduler nodes, frees the
// per-difficulty block array, releases the four animation slots the manager
// owns and clears the global owner pointer.
//
// Retail reaches this member with the receiver in EAX - a whole-program
// agreement, because the body needs all four callee-saved registers (EDI for
// the manager itself, ESI for the node/record under work, EBX for the
// scheduler and the animation manager, EBP for the cached import pointer).
#include <stddef.h>
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

extern "C" Scheduler *data_00491be4;
extern "C" void *data_00477704;
extern "C" unsigned char data_00474ca0;

extern "C" void __cdecl entry_free_004524a1(void *memory);
extern "C" void __cdecl entry_free_00452422(void *memory);
extern "C" void __stdcall EnemyManager_ReleaseLists_00409f90(void *manager);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// The animation-manager and bullet-entity types are declared exactly as the
// co-compiled models in this cluster define them, so the calls bind to those
// bodies and their whole-program register agreements.
#include "th10/game/enemy_manager_dependencies_0040d530.hpp"

class AnimationManager_004477d0 {
public:
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810 *slots_3ad06c[0x21];

    __declspec(noinline) void ClearResourceSlot(int index);
};



extern "C" AnimationManager *data_00491c10;

#include "th10/game/enemy_manager_factory_0040d6b0.hpp"

#pragma code_seg(".text$02b")
void EnemyManager_0040d530::Destroy() {
    EnemyManager_ReleaseLists_00409f90(this);

    SchedulerTask *task = node_008;
    Scheduler *scheduler = data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }

    task = node_00C;
    scheduler = data_00491be4;
    if (task) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        Scheduler_Remove(scheduler, task);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }

    for (int index = 3; index < 35; ++index) {
        void *block = blocks_054[index];
        if (block)
            entry_free_00452422(block);
    }

    void **blocks = blocks_054;
    if (blocks) {
        ((BulletEntity_0040d680 *)blocks)->ReleaseResource();
        entry_free_004524a1(blocks);
    }
    blocks_054 = 0;

    _ReadWriteBarrier();
    if ((data_00474ca0 & 9u) == 0) {
        for (int i = 0; i < 4; ++i) {
            int index = 9 + i;
            if (index < 0)
                continue;
            if ((unsigned int)index >= 0x21u)
                continue;
            AnimationResource_00447810 **slot =
                &((AnimationManager_004477d0 *)data_00491c10)->slots_3ad06c[index];
            if (*slot == 0)
                continue;
            (*slot)->Release();
            entry_free_004524a1(*slot);
            *slot = 0;
        }
    }

    data_00477704 = 0;
}
#pragma code_seg()
