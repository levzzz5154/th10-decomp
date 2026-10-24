// Replay frame-step callback, 0x0042A3E0. Receiver in ECX, result in EAX.
#include <stddef.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" unsigned char g_game;
extern "C" unsigned int g_input_keys_raw;
struct ReplayScene {
    unsigned char reserved000[0x58];
    unsigned int flags;
};
struct ReplayFrameStep {
    unsigned char reserved000[0x10];
    int state;
    unsigned char reserved014[0x1b4];
    int frame;
    __declspec(noinline) int Check();
};
typedef char ReplayFrameStep_state_offset[offsetof(ReplayFrameStep, state) == 0x10 ? 1 : -1];
typedef char ReplayFrameStep_frame_offset[offsetof(ReplayFrameStep, frame) == 0x1c8 ? 1 : -1];
typedef char ReplayScene_flags_offset[offsetof(ReplayScene, flags) == 0x58 ? 1 : -1];
// Returns 6 (run the frame again) every frame but each fourth while the skip key
// is held during playback, otherwise 1.
int ReplayFrameStep::Check() {
    ReplayScene* scene = (ReplayScene*)*(void**)&g_game;
    if (scene) {
        int result;
        if ((scene->flags & 4) != 0) result = 1;
        else {
            result = 1;
            if (state == 1 && (g_input_keys_raw & 0x100) != 0 && frame % 4 != 0) result = 6;
        }
        // Retail keeps this join until the exit jumps are final: the four
        // failure branches share the `ret` after `mov eax,6` and the null path
        // owns the trailing `mov eax,1; ret`. Without the barrier the empty join
        // folds into the exit label and the branches pick the other `ret`.
        _ReadWriteBarrier();
        return result;
    }
    return 1;
}
