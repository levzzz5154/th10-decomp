#include "th10/platform/sound_worker.hpp"

// 0x0043CC40 - Stop the sound/music worker pair. The retail function
// guards on the primary handle at context+0x5218, raises the stop flag
// at +0x5224 when it is still clear, polls each handle with
// WaitForSingleObject(handle, 100) and Sleep(1) while the wait times
// out (0x102), then closes both handles and clears their slots. The
// readable form injects the three Win32 edges; a null hook is treated
// as an immediately signaled wait / no-op, following the shared
// Platform_StopWorker (0x0044C130) convention.
unsigned int Platform_StopSoundWorkers(
        SoundWorkerState* state, unsigned int (*wait)(void*, unsigned int),
        void (*sleep)(unsigned int), void (*close)(void*)) {
    if (state->worker_thread == 0) {
        return 0;
    }
    if (state->stop_requested == 0) {
        state->stop_requested = 1;
    }
    while (wait != 0 && wait(state->worker_thread, 100) == 0x102u) {
        if (sleep != 0) {
            sleep(1);
        }
    }
    while (wait != 0 && wait(state->companion_thread, 100) == 0x102u) {
        if (sleep != 0) {
            sleep(1);
        }
    }
    if (close != 0) {
        close(state->worker_thread);
        close(state->companion_thread);
    }
    state->worker_thread = 0;
    state->companion_thread = 0;
    return 0;
}
