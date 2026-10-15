#include "th10/source_views/angle_4872c8_0.hpp"
#include "th10/source_views/angle_4872c8_1.hpp"
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


#include "../../../include/th10/source_views/angle_4872c8_2.hpp"
#include "th10/source_views/angle_4872c8_0.hpp"
#include "th10/source_views/angle_4872c8_1.hpp"
#include "th10/source_views/angle_4872c8_2.hpp"
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

