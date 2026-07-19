// Readable reconstruction of the retail angle-wrapping pair. Both leaves fold
// their input into [-pi, pi] with a shared iteration counter capped at 0x20,
// matching the retail x87 control flow exactly (including the cap ordering).
#include "th10/math/angle.hpp"

extern float DAT_00470b10;  // -pi (-3.1415927)
extern float DAT_00470b14;  // 2*pi (6.2831855)
extern float DAT_00470b18;  // pi (3.1415927)

// 0x0044BC70 - Wrap an angle into [-pi, pi]. The iteration cap is shared by
// both adjustment loops and bounds huge inputs after 34 steps.
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

// 0x0044BC10 - Add two angles and wrap the sum into [-pi, pi]. Used when
// integrating angular velocity so directions never accumulate error.
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
