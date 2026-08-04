#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// Output device object released at the end of the shutdown; retail
// calls the first vtable entry with the literal argument 1.
struct MidiDevice;
struct MidiDeviceVtbl {
    void (*destroy)(int mode);
};
struct MidiDevice {
    const MidiDeviceVtbl* vtbl;
};

// MIDI worker fields inside the sound-thread context (retail offsets in
// comments; retail slots are 32-bit).
struct MidiWorkerState {
    uint32_t worker_thread_id;  // +0x614, PostThreadMessageA target
    void* worker_thread;        // +0x618, worker thread handle
    MidiDevice* device;         // +0x5208, output device object
    void* companion_handle;     // +0x520C, closed with the worker
};

// 0x0043DAB0 - Stop the MIDI worker: flush pending playback (retail
// 0x0044D550), post WM_QUIT (0x12) to the worker thread and re-post
// until a 0x100 ms wait on its handle succeeds, close the worker and
// companion handles, clear the worker slot, and finally destroy the
// output device object (first vtable entry, argument 1) and clear its
// slot. All Win32 edges are injected. A cleared device slot makes the
// whole call a no-op, matching the retail guard.
void MidiWorker_Stop(MidiWorkerState* state, void (*flush)(),
                     int (*post_thread_message)(uint32_t thread_id,
                                                uint32_t message,
                                                uint32_t wparam,
                                                uint32_t lparam),
                     uint32_t (*wait)(void* handle, uint32_t milliseconds),
                     void (*close)(void* handle));
