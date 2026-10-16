#pragma once
#include "th10/math/angle.hpp"

// Retail angle constants at 0x00470B10..0x00470B18.
extern float DAT2;  // -pi (-3.1415927)
extern float DAT3;  // 2*pi (6.2831855)
extern float DAT4;  // pi (3.1415927)

// 0x00408660: subtract two angles, wrapping the result by one full turn.
