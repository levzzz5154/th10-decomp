#pragma once

#include <cstdint>

// Fade context referenced from the sound manager (retail manager+0x5208;
// field offsets in comments).
struct SoundFadeState {
    int32_t counter;  // +0x14, frames remaining
    int32_t mode;     // +0x1C, 1 fade-out-stop / 2 / 4 / 3 fade steps
};

// 0x00421E00 - Tick the active sound fade. Each recognized mode (1, 2,
// 4, then 3, checked in that retail order) decrements the frame
// counter: while frames remain the volume step (retail 0x0044D4E0)
// runs; when the counter is exhausted the mode resets to 0, and mode 1
// additionally stops the streaming buffer (retail calls the buffer's
// Stop through vtable +0x48). A null fade context is a no-op, matching
// the retail guard on the manager slot.
void SoundFade_Tick(SoundFadeState* fade, void (*stop_buffer)(),
                    void (*step_volume)());
