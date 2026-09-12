#include "th10/game/thread_spawn.hpp"

// 0x00420EA0 - Spawn the game worker thread. The retail body brackets
// the whole operation with EnterCriticalSection(+0x6DC) plus a spawn
// depth byte at +0x6FA and reuses the generic worker-start sequence
// (compare Platform_StartWorker at 0x0044C1C0): stop the current
// worker, store the entry point at +0x644, set running (+0x63C), clear
// the stop request (+0x638), and keep the _beginthreadex handle and
// thread id at +0x630/+0x634.
uint32_t GameThread_SpawnWorker(
        GameThreadSpawner* state, void* start_address, void* argument,
        void (*enter_lock)(GameThreadSpawner*),
        void (*leave_lock)(GameThreadSpawner*),
        void (*stop_current)(GameThreadSpawner*),
        uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                                  void* start, void* argument, unsigned flags,
                                  uint32_t* thread_id)) {
    if (enter_lock != 0) {
        enter_lock(state);
    }
    state->spawn_depth += 1;
    if (stop_current != 0) {
        stop_current(state);
    }
    state->start_address = start_address;
    state->running = 1;
    state->stop_requested = 0;
    state->worker_handle =
        begin_thread != 0
            ? begin_thread(0, 0, start_address, argument, 0,
                           &state->worker_thread_id)
            : 0;
    if (leave_lock != 0) {
        leave_lock(state);
    }
    state->spawn_depth -= 1;
    return 0;
}
