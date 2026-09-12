#include "th10/platform/sound_stream_start.hpp"


// 0x0044D440 - Start a streaming voice. Retail keeps the manager in
// EAX with the stream fields at +0x14..+0x30 and dispatches Play
// through the buffer vtable at +0x30; every external edge is injected
// so the host test can drive both failure paths and the reset branch.
int32_t SoundStream_Start(
        SoundStream* state, uint32_t position, uint32_t arg1, uint32_t arg2,
        void* (*get_buffer)(uint32_t position), int32_t (*prepare)(),
        int32_t (*reset_buffer)(void* buffer), void (*after_reset)(),
        void (*step_volume)(),
        int32_t (*play)(void* buffer, uint32_t reserved, uint32_t arg1,
                        uint32_t arg2)) {
    if (state->device == 0) {
        return (int32_t)0x800401F0;  // -0x7FFBFE10
    }
    void* buffer = get_buffer != 0 ? get_buffer(position) : 0;
    if (buffer == 0) {
        return (int32_t)0x80004005;  // -0x7FFFBFFB
    }
    int32_t result = prepare != 0 ? prepare() : 0;
    if (result < 0) {
        return result;
    }
    if (position != 0) {
        result = reset_buffer != 0 ? reset_buffer(buffer) : 0;
        if (result < 0) {
            return result;
        }
        if (after_reset != 0) {
            after_reset();
        }
    }
    state->fade_mode = 0;
    state->fade_count = 0;
    state->fade_wait = 0;
    if (step_volume != 0) {
        step_volume();
    }
    state->started = 1;
    state->play_arg1 = arg1;
    state->play_arg2 = arg2;
    state->stop_flag = 0;
    return play != 0 ? play(buffer, 0, arg1, arg2) : 0;
}
