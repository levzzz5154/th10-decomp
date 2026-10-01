#pragma once
#include "th10/math/timer.hpp"

struct ReturningFrameTimer : FrameTimer {
    __declspec(noinline) int TickReturningFrame();
};
typedef char ReturningFrameTimerSize[sizeof(ReturningFrameTimer) == sizeof(FrameTimer) ? 1 : -1];
