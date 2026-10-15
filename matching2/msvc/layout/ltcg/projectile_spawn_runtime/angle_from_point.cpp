// Compiler context only: the anchor copy of 0x00426660, returning the angle
// from a supplied point to the player origin. The whole-program pass derives
// the point-in-EAX convention from the spawn path's call sites. The anchor
// bytes are never exported as recovered code.
#include <math.h>
#include "th10/game/player.hpp"

extern "C" const float data_00470b04;
extern "C" const float data_00470b94;

#pragma code_seg(".text$00426660_s")
float Player::AngleFromPoint(const float* point) {
    float dx = position.x - point[0];
    float dy = position.y - point[1];
    if (dy == data_00470b04 && dx == data_00470b04)
        return data_00470b94;
    return (float)atan2((double)dy, (double)dx);
}
#pragma code_seg()
