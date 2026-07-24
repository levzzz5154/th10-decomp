#pragma once

#include <cstdint>

// Worker-spawn block inside the game thread object (retail offsets in
// comments; the critical section lives at +0x6DC).
struct GameThreadSpawner {
    uintptr_t worker_handle;    // +0x630, _beginthreadex result
    uint32_t worker_thread_id;  // +0x634
    uint32_t stop_requested;    // +0x638, cleared on spawn
    uint32_t running;           // +0x63C, set on spawn
    void* start_address;        // +0x644
    int8_t spawn_depth;         // +0x6FA, incremented inside the lock
};

// 0x00420EA0 - Spawn the game worker thread under the spawner's
// critical section: enter the lock, bump the spawn depth, stop the
// current worker through the shared stop path (retail 0x0044C150),
// record the entry point / running / stop-request words, start the
// thread with _beginthreadex, then release the lock and drop the spawn
// depth. All external edges are injected. Always returns 0.
uint32_t GameThread_SpawnWorker(
    GameThreadSpawner* state, void* start_address, void* argument,
    void (*enter_lock)(GameThreadSpawner*),
    void (*leave_lock)(GameThreadSpawner*),
    void (*stop_current)(GameThreadSpawner*),
    uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                              void* start, void* argument, unsigned flags,
                              uint32_t* thread_id));
