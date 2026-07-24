#pragma once

#include <cstdint>

// Worker-thread control block (retail offsets in comments; retail slots
// are 32-bit).
struct WorkerControl {
    uint32_t reserved_00;     // +0x00
    uintptr_t thread_handle;  // +0x04, _beginthreadex result
    uint32_t thread_id;       // +0x08, filled by _beginthreadex
    uint32_t stop_requested;  // +0x0C, cleared on start
    uint32_t running;         // +0x10, set on start
    uint32_t reserved_14;     // +0x14
    void* start_address;      // +0x18, thread entry point
};

// 0x0044C1C0 - Start (or restart) a worker thread: stop the current
// worker through the shared stop path (retail 0x0044C150), record the
// entry point, mark the worker running with the stop flag cleared, and
// spawn the thread. The stop path and the _beginthreadex edge are
// injected; retail passes the entry point in EDI.
void Platform_StartWorker(
    WorkerControl* state, void* start_address, void* argument,
    void (*stop_current)(WorkerControl*),
    uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                              void* start, void* argument, unsigned flags,
                              uint32_t* thread_id));
