#include "th10/math/angle.hpp"

// Retail angle constants at 0x00470B10..0x00470B18.
extern float DAT_00470b10;  // -pi (-3.1415927)
extern float DAT_00470b14;  // 2*pi (6.2831855)
extern float DAT_00470b18;  // pi (3.1415927)

// 0x0044BC70 - Wrap an angle into [-pi, pi]. The iteration counter is
// intentionally shared by both adjustment loops, as it is in the retail code.
float Angle_Normalize(float angle) {
    int iterations = 0;
    while (angle > DAT_00470b18) {
        angle -= DAT_00470b14;
        if (iterations++ > 0x20)
            break;
    }
    while (angle < DAT_00470b10) {
        angle += DAT_00470b14;
        if (iterations++ > 0x20)
            break;
    }
    return angle;
}

// 0x0044BC10 - Add two angles and normalize the result into [-pi, pi].
float Angle_NormalizeSum(float angle, float delta) {
    float sum = angle + delta;
    int iterations = 0;
    while (sum > DAT_00470b18) {
        sum -= DAT_00470b14;
        if (iterations++ > 0x20)
            break;
    }
    while (sum < DAT_00470b10) {
        sum += DAT_00470b14;
        if (iterations++ > 0x20)
            break;
    }
    return sum;
}
