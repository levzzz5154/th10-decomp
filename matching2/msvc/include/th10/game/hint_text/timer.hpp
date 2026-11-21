#ifndef TH10_MATH_TIMER_HPP
#define TH10_MATH_TIMER_HPP

#include <stddef.h>

// Five-word frame timer. The source declarations are ordinary __thiscall;
// the documented native LTCG cluster selects ESI for this and EAX for the
// Decrement count. Unrecovered assembly callers use those actual conventions.
struct FrameTimer {
    int previous;                 // +0x00
    int current;                  // +0x04
    float elapsed;                // +0x08
    const float* speed;            // +0x0C
    unsigned int flags;            // +0x10

    __declspec(noinline) void Tick();
    __declspec(noinline) void Advance(float delta);
    __declspec(noinline) void Decrement(int count);
};

typedef char FrameTimer_size_must_be_20[sizeof(FrameTimer) == 20 ? 1 : -1];
typedef char FrameTimer_elapsed_offset_must_be_8[offsetof(FrameTimer, elapsed) == 8 ? 1 : -1];
typedef char FrameTimer_speed_offset_must_be_12[offsetof(FrameTimer, speed) == 12 ? 1 : -1];

#endif
