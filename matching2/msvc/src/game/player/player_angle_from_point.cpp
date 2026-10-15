// 0x00426660 - Return the angle from a supplied point to the player.
// The native-LTCG caller supplies the point in EAX while the player stays in ECX.
#include <math.h>
#include "th10/game/player.hpp"

extern "C" float flt_0;
extern "C" float flt_pi_2;

#pragma code_seg(".text$01angle")
float Player::AngleFromPoint(const float* point) {
    float dx = position.x - point[0];
    float dy = position.y - point[1];
    if (dy == flt_0 && dx == flt_0)
        return flt_pi_2;
    return (float)atan2((double)dy, (double)dx);
}
#pragma code_seg()
