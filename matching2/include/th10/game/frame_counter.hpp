#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// 0x00427C70 - Interval test on a two-word frame counter {previous,
// current}: true when the counter moved this frame and the current
// value is an exact multiple of the interval. Retail is a thiscall member
// (this in ECX, interval on the stack, ret 4); MSVC 7.1 compiles the
// member body below to the exact retail bytes.
struct FrameCounterPair {
    int32_t previous;   // +0x00
    int32_t current;    // +0x04

    int32_t AtInterval(int32_t interval);
};
