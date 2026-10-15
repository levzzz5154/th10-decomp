// Replay frame-step callback, 0x0042A3E0. Receiver in ECX, result in EAX.
#include <stddef.h>
extern "C" unsigned char g_game;
extern "C" unsigned int data_00474e30;
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
int ReplayFrameStep::Check() {
    ReplayScene* scene = (ReplayScene*)*(void**)&g_game;
    if (scene) {
        int result = 1;
        if ((scene->flags & 4) != 0) return result;
        if (state != 1) return result;
        if ((data_00474e30 & 0x100) == 0) return result;
        result = 1;
        if (frame % 4 != 0) result = 6;
        return result;
    }
    return 1;
}
