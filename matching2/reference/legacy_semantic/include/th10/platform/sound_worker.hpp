#pragma once

// Worker-thread fields embedded in the sound/music thread context
// (retail context offsets +0x5218..+0x5224). In retail each handle is
// one 32-bit slot; the readable form uses native pointers and documents
// the retail offsets.
struct SoundWorkerState {
    void* worker_thread;         // +0x5218, primary worker handle
    void* companion_thread;      // +0x521C, companion worker handle
    unsigned int reserved_5220;  // +0x5220
    unsigned int stop_requested; // +0x5224, set to 1 to stop the workers
};

// 0x0043CC40 - Request worker shutdown, poll both worker handles until
// they leave the WAIT_TIMEOUT (0x102) state, close them, and clear the
// handle slots. The Win32 edges (WaitForSingleObject with a 100 ms
// timeout, Sleep(1), CloseHandle) are injected so the host-side test
// can drive the polling loops deterministically. Returns 0, matching
// the retail function; a null primary handle is a no-op.
unsigned int Platform_StopSoundWorkers(
    SoundWorkerState* state, unsigned int (*wait)(void*, unsigned int),
    void (*sleep)(unsigned int), void (*close)(void*));
