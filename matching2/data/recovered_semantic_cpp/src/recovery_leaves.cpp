#include "th10/math/angle.hpp"

void Score_SetNormalizedAngle(void* state, float angle) {
    *(float*)((unsigned char*)state + 0x1C) = Angle_Normalize(angle);
}
