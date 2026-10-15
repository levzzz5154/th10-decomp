// Compiler context only: the anchor copy of 0x00426660, returning the angle
// from a supplied point to the player origin. The whole-program pass derives
// the point-in-EAX convention from the spawn path's call sites. The anchor
// bytes are never exported as recovered code.
#include <math.h>
#include "th10/game/player.hpp"

extern "C" const float flt_0;
extern "C" const float flt_pi_2;

#pragma code_seg(".text$00426660_s")
float Player::AngleFromPoint(const float* point) {
    float dx = position.x - point[0];
    float dy = position.y - point[1];
    if (dy == flt_0 && dx == flt_0)
        return flt_pi_2;
    return (float)atan2((double)dy, (double)dx);
}
#pragma code_seg()
