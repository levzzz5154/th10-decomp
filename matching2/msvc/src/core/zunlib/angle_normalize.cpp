#include "th10/source_views/angle_4872c8_0.hpp"
#include "th10/source_views/angle_4872c8_1.hpp"
float Angle_Normalize(float angle) {
    int iterations = 0;
    while (angle > DAT4) {
        angle -= DAT3;
        if (iterations++ > 0x20)
            break;
    }
    while (angle < DAT2) {
        angle += DAT3;
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
    while (sum > DAT4) {
        sum -= DAT3;
        if (iterations++ > 0x20)
            break;
    }
    while (sum < DAT2) {
        sum += DAT3;
        if (iterations++ > 0x20)
            break;
    }
    return sum;
}

