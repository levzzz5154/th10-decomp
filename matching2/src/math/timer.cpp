// =============================================================================
// timer.cpp - Readable frame-timer advancement from 0x00404ED0
// =============================================================================
#include "th10/math/timer.hpp"

extern float _DAT_00470afc;      // 1.0f
extern float _DAT_00470b68;      // normal-speed lower bound
extern float _DAT_00470b64;      // normal-speed upper bound

void FrameTimer_Tick(FrameTimer* timer) {
    timer->previous = timer->current;

    const float speed = *timer->speed;
    if (_DAT_00470b68 < speed && speed < _DAT_00470b64) {
        ++timer->current;
        timer->elapsed += _DAT_00470afc;
        return;
    }

    timer->elapsed += speed;
    timer->current = (int)timer->elapsed;
}
