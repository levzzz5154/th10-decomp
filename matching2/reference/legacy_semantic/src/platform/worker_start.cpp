#include "th10/platform/worker_start.hpp"

// 0x0044C1C0 - Start a worker thread. Retail first invokes the shared
// worker stop path at 0x0044C150 for the same control block, then
// stores the entry point at +0x18, sets the running word at +0x10,
// clears the stop request at +0x0C, and calls
// _beginthreadex(0, 0, start, argument, 0, &thread_id), keeping the
// returned handle at +0x04. Both external edges are injected so the
// host test can observe the exact call sequence.
void Platform_StartWorker(
        WorkerControl* state, void* start_address, void* argument,
        void (*stop_current)(WorkerControl*),
        uintptr_t (*begin_thread)(void* security, unsigned stack_size,
                                  void* start, void* argument, unsigned flags,
                                  uint32_t* thread_id)) {
    if (stop_current != 0) {
        stop_current(state);
    }
    state->start_address = start_address;
    state->running = 1;
    state->stop_requested = 0;
    state->thread_handle =
        begin_thread != 0
            ? begin_thread(0, 0, start_address, argument, 0, &state->thread_id)
            : 0;
}
