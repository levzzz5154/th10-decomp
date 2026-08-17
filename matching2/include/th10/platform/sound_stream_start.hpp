#pragma once

#include <cstdint>

// Streaming-voice fields inside the sound manager (retail offsets in
// comments).
struct SoundStream {
    uint32_t device;     // +0x04, guard: 0 means no sound device
    int32_t fade_count;  // +0x14, cleared on start
    uint32_t fade_wait;  // +0x18, cleared on start
    uint32_t fade_mode;  // +0x1C, cleared on start
    uint32_t play_arg1;  // +0x20, recorded play argument
    uint32_t play_arg2;  // +0x24
    uint32_t stop_flag;  // +0x2C, cleared on start
    uint32_t started;    // +0x30, set on start
};

// 0x0044D440 - Start a streaming voice. Fails with the retail HRESULTs
// when the device guard is clear (0x80040 1F0-style constant
// -0x7FFBFE10) or when the buffer lookup (retail 0x0044D370) returns
// null (-0x7FFFBFFB). Otherwise the prepare step (retail 0x0044D300)
// must succeed, and a non-zero position additionally runs the buffer
// reset (retail 0x0044D110, aborting on failure) and the post-reset
// step (retail 0x0044D600). The fade words clear, the volume step
// (retail 0x0044D4E0) runs, the started flag and play arguments are
// recorded, and the buffer's Play (vtable +0x30) result is returned.
int32_t SoundStream_Start(
    SoundStream* state, uint32_t position, uint32_t arg1, uint32_t arg2,
    void* (*get_buffer)(uint32_t position), int32_t (*prepare)(),
    int32_t (*reset_buffer)(void* buffer), void (*after_reset)(),
    void (*step_volume)(),
    int32_t (*play)(void* buffer, uint32_t reserved, uint32_t arg1,
                    uint32_t arg2));
