#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// 0x00427C70 - Interval test on a two-word frame counter {previous,
// current}: true when the counter moved this frame and the current
// value is an exact multiple of the interval.
int32_t FrameCounter_AtInterval(const int32_t* counter, int32_t interval);
