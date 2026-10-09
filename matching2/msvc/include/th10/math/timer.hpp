#ifndef TH10_MATH_TIMER_HPP
#define TH10_MATH_TIMER_HPP

#include <stddef.h>

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64
extern float g_score_default_speed;       // 0x00476F78, the script-time frame delta

// Five-word frame timer. The source declarations are ordinary __thiscall;
// the documented native LTCG cluster selects ESI for this and EAX for the
// Decrement count. Unrecovered assembly callers use those actual conventions.
struct FrameTimer {
    int previous;                 // +0x00
    int current;                  // +0x04
    float elapsed;                // +0x08
    const float* speed;            // +0x0C
    unsigned int flags;            // +0x10

    // Fractional frame count. Retail reads it through this accessor: the
    // inlined float return is what keeps later integer operands apart.
    float Elapsed() const { return elapsed; }

    // Frames added per tick: 1.0 normally, less while the game is slowed.
    float Speed() const { return *speed; }

    // Retail expands the tick in some callers and calls it in others; the
    // callers that expand it use this copy.
    // The upper bound reads the speed through the accessor and the lower
    // bound does not: that one extra temporary is what orders the x87
    // operands of the slowed-down add in every expansion.
    void TickInline() {
        previous = current;
        if (*speed > g_frame_timer_normal_lower && Speed() < g_frame_timer_normal_upper) {
            ++current;
            elapsed += 1.0f;
        } else {
            current = int(elapsed += *speed);
        }
    }

    // Jump to a frame, initialising the timer on first use.
    void Set(int frame);

    // Back to frame zero, initialising the timer on first use.
    void Reset() {
        if (!(flags & 1)) {
            current = 0;
            previous = -999999;
            elapsed = 0.0f;
            speed = &g_score_default_speed;
            flags |= 1;
        }
        current = 0;
        elapsed = 0.0f;
        previous = -1;
    }

    __declspec(noinline) void Tick();
    __declspec(noinline) void Advance(float delta);
    __declspec(noinline) void Decrement(int count);
};

// 0x00405410 is this function where retail did not expand it in place.
#pragma code_seg(push, ".text$00405410_fn")
inline void FrameTimer::Set(int frame) {
    if (!(flags & 1)) {
        current = 0;
        previous = -999999;
        elapsed = 0.0f;
        speed = &g_score_default_speed;
        flags |= 1;
    }
    current = frame;
    previous = frame - 1;
    elapsed = (float)frame;
}
#pragma code_seg(pop)

typedef char FrameTimer_size_must_be_20[sizeof(FrameTimer) == 20 ? 1 : -1];
typedef char FrameTimer_elapsed_offset_must_be_8[offsetof(FrameTimer, elapsed) == 8 ? 1 : -1];
typedef char FrameTimer_speed_offset_must_be_12[offsetof(FrameTimer, speed) == 12 ? 1 : -1];

#endif
