#pragma once
#include <stddef.h>
#include "th10/math/timer.hpp"
struct GameStateFade_00404530 {
    unsigned char reserved[0x2A18];
    unsigned int flags;
    FrameTimer timer;
    __declspec(noinline) void BeginFade();
};
typedef char GameStateFade_timer_offset[offsetof(GameStateFade_00404530,timer)==0x2A1C?1:-1];
