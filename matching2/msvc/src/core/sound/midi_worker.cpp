#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"


// 0x0043E3A0..0x0043E45C: MidiWorker_MessageLoopRetail
// DirectSound music worker: service notification events while playing and
// drain queued messages, finishing after WM_QUIT or a missing global stream.
// Historical field names below: stream at +0x30 means playing; stopping at
// +0x74 means servicing. The called 0x44D850 routine refills one segment.
// See reference/recovery_notes/sound_stream_restart_service_worker.md and its
// typed candidate for explicit cached imports and the direct stdcall callee.
struct MidiWorkerState {
    unsigned char pad_00[0x30];
    unsigned int stream;
    unsigned char pad_34[0x40];
    unsigned int stopping;
};

struct TagMsg {
    unsigned int window;
    unsigned int message;
    unsigned int wparam;
    unsigned int lparam;
    unsigned int time;
    unsigned int point_x;
    unsigned int point_y;
};

extern "C" unsigned char g_midi_worker_state;
extern "C" unsigned char g_midi_worker_event;
extern "C" void __cdecl asm_FUN_0044d850_0044d850();

extern "C" __declspec(dllimport) unsigned int __stdcall MsgWaitForMultipleObjects(
    unsigned int count, void* handles, unsigned int wake_mask, unsigned int timeout,
    unsigned int wake_flags);
extern "C" __declspec(dllimport) int __stdcall PeekMessageA(
    TagMsg* message, void* window, unsigned int min, unsigned int max, unsigned int remove);

typedef void (__stdcall* StreamStopFn)(void* state, int mode);

extern "C" unsigned int __stdcall asm_MidiWorker_MessageLoopRetail_0043e3a0(void* thread_parameter) {
    int finished = 0;
    TagMsg message;
    do {
        unsigned int wait = MsgWaitForMultipleObjects(1, &g_midi_worker_event, 0, 0xFFFFFFFF, 0xBF);
        MidiWorkerState* state = (MidiWorkerState*)*(void**)&g_midi_worker_state;
        if (state == 0)
            finished = 1;
        switch (wait) {
        case 0:
            if (state != 0 && state->stream != 0) {
                state->stopping = 1;
                ((StreamStopFn)asm_FUN_0044d850_0044d850)(*(void**)&g_midi_worker_state, 1);
                ((MidiWorkerState*)*(void**)&g_midi_worker_state)->stopping = 0;
            }
            break;
        case 1:
            if (PeekMessageA(&message, 0, 0, 0, 1) != 0) {
                do {
                    if (message.message == 18)
                        finished = 1;
                } while (PeekMessageA(&message, 0, 0, 0, 1) != 0);
            }
            break;
        }
    } while (finished == 0);
    return 0;
}
