#include "th10/game/progress_worker.hpp"

#include "th10/game/pool_constructors.hpp"


// 0x0042CD50 - Create the progress manager and start its worker thread.
// Retail calls the statically linked operator new with size 0x5ACC
// (host callers must return at least kProgressManagerDwords words),
// constructs and publishes the manager, stops the current worker, and
// then fills the embedded worker control block exactly like the generic
// worker start at 0x0044C1C0: entry point at word 0x16B2, running flag
// at 0x16B0, stop request cleared at 0x16AF, and the _beginthreadex
// handle at word 0x16AD with the thread id at 0x16AE.
uint32_t* ProgressManager_CreateAndStartWorker(
        void* (*allocate)(uint32_t size),
        void (*stop_current)(uint32_t* manager),
        uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                                  void* start, void* argument, unsigned flags,
                                  uint32_t* thread_id),
        void* thread_proc) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x5ACC) : (uint32_t*)0;
    if (state == 0) {
        return 0;
    }
    ProgressManager_ConstructAndPublish(state);
    if (stop_current != 0) {
        stop_current(state);
    }
    // Retail keeps 32-bit slots; the host image truncates like the
    // release path at 0x0042AB20.
    state[0x16B2] = (uint32_t)(uintptr_t)thread_proc;
    state[0x16B0] = 1;
    state[0x16AF] = 0;
    const uintptr_t handle =
        begin_thread != 0
            ? begin_thread(0, 0, thread_proc, state, 0, &state[0x16AE])
            : 0;
    state[0x16AD] = (uint32_t)handle;
    return state;
}
