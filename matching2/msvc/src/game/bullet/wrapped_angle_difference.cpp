#include "th10/source_views/angle_4872c8_0.hpp"
float __stdcall WrappedAngleDifference(float first, float second) {
    const float pi = 3.14159265358979323846f;
    const float tau = 6.28318530717958647692f;
    float difference = first - second;
    if (difference > pi)
        return first - (tau + second);
    if (second - first > pi)
        return first - (second - tau);
    return difference;
}
