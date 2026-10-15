#pragma once
#include <stddef.h>
#include "th10/math/timer.hpp"
struct BackGround {
    unsigned char reserved[0x2A18];
    unsigned int flags;
    FrameTimer timer;
    __declspec(noinline) void BeginFade();
    __declspec(noinline) void StartMode();
};
typedef char BackGroundFadeTimerOffset[offsetof(BackGround,timer)==0x2A1C?1:-1];
