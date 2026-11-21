// 0x0043E3A0: MusicStreamWorker_Loop
#include "th10/runtime/asm_symbols.hpp"


// 0x0043E3A0..0x0043E45C: MusicStreamWorker_Loop
// DirectSound music worker: service notification events while playing and
// drain queued messages, finishing after WM_QUIT or a missing global stream.
// Historical field names below: stream at +0x30 means playing; stopping at
// +0x74 means servicing. The called 0x44D850 routine refills one segment.
// See reference/recovery_notes/sound_stream_restart_service_worker.md and its
// typed candidate for explicit cached imports and the direct stdcall callee.
struct SoundStreamingState {
    unsigned char pad_00[0x30];
    unsigned int playing;
    unsigned char pad_34[0x40];
    unsigned int servicing;
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

extern "C" unsigned char g_music_stream;
extern "C" unsigned char g_music_worker_event;
extern "C" void __cdecl SoundStream_ServiceChunk();

extern "C" __declspec(dllimport) unsigned int __stdcall MsgWaitForMultipleObjects(
    unsigned int count, void* handles, unsigned int wake_mask, unsigned int timeout,
    unsigned int wake_flags);
extern "C" __declspec(dllimport) int __stdcall PeekMessageA(
    TagMsg* message, void* window, unsigned int min, unsigned int max, unsigned int remove);

typedef void (__stdcall* StreamServiceFn)(void* state, int mode);

extern "C" unsigned int __stdcall MusicStreamWorker_Loop(void* thread_parameter) {
    int finished = 0;
    TagMsg message;
    do {
        unsigned int wait = MsgWaitForMultipleObjects(1, &g_music_worker_event, 0, 0xFFFFFFFF, 0xBF);
        SoundStreamingState* state = (SoundStreamingState*)*(void**)&g_music_stream;
        if (state == 0)
            finished = 1;
        switch (wait) {
        case 0:
            if (state != 0 && state->playing != 0) {
                state->servicing = 1;
                ((StreamServiceFn)SoundStream_ServiceChunk)(*(void**)&g_music_stream, 1);
                ((SoundStreamingState*)*(void**)&g_music_stream)->servicing = 0;
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
