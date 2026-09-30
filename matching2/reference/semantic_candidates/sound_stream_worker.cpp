// 0x0043E3A0, 189 retail bytes: service DirectSound notifications and drain
// thread messages. The single stdcall argument is unused (retail RET 4).
#include "sound_wave_types.hpp"

struct SoundWorkerMessage {
    void* window;
    unsigned int message;
    unsigned int wparam;
    int lparam;
    unsigned int time;
    int point_x;
    int point_y;
};
typedef unsigned int (__stdcall* SoundWorkerWait)(unsigned int, void* const*, int, unsigned int, unsigned int);
typedef int (__stdcall* SoundWorkerPeek)(SoundWorkerMessage*, void*, unsigned int, unsigned int, unsigned int);
extern "C" {
    extern SoundWorkerWait g_sound_worker_wait;
    extern SoundWorkerPeek g_sound_worker_peek;
    extern SoundStreamingState* volatile g_active_music_stream;
    extern void* g_music_notification_event;
    int __stdcall SoundStream_Service_0044d850(SoundStreamingState*, unsigned int repeat);
}

extern "C" unsigned int __stdcall SoundStream_Worker_0043e3a0(void*) {
    SoundWorkerPeek peek = g_sound_worker_peek;
    SoundWorkerWait wait = g_sound_worker_wait;
    bool quit = false;
    do {
        unsigned int result = wait(1, &g_music_notification_event, 0, 0xffffffffu, 0xbfu);
        SoundStreamingState* stream = g_active_music_stream;
        if (!stream)
            quit = true;
        if (result == 1) {
            SoundWorkerMessage message;
            while (peek(&message, 0, 0, 0, 1)) {
                if (message.message == 0x12)
                    quit = true;
            }
        } else if (result == 0 && stream && stream->playing) {
            stream->servicing = 1;
            SoundStream_Service_0044d850(g_active_music_stream, 1);
            // Retail reloads the global after servicing, without a null check.
            g_active_music_stream->servicing = 0;
        }
    } while (!quit);
    return 0;
}
