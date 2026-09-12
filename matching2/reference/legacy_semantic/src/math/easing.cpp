#include "th10/math/easing.hpp"

// 0x0044C350 - Evaluate the retail animation easing table. Retail evaluates
// through x87 extended intermediates; double keeps the same shape on host
// builds while retaining the explicit mode/ratio semantics.
float Easing_Evaluate(int mode, float numerator, float denominator) {
    const double ratio = (double)numerator / (double)denominator;
    const double one = 1.0;
    const double two = 2.0;
    const double half = 0.5;
    double x;
    switch (mode) {
    case 1: return (float)(ratio * ratio);
    case 2: return (float)(ratio * ratio * ratio);
    case 3: return (float)(ratio * ratio * ratio * ratio);
    case 4: x = one - ratio; return (float)(one - x * x);
    case 5: x = one - ratio; return (float)(one - x * x * x);
    case 6: x = one - ratio; return (float)(one - x * x * x * x);
    case 9:
        x = ratio + ratio;
        return (float)(x < one ? x * x * half :
                       (two - (two - x) * (two - x)) * half);
    case 10:
        x = ratio + ratio;
        return (float)(x < one ? x * x * x * half :
                       (two - (two - x) * (two - x) * (two - x)) * half);
    case 11:
        x = ratio + ratio;
        return (float)(x < one ? x * x * x * x * half :
                       (two - (two - x) * (two - x) * (two - x) *
                        (two - x)) * half);
    case 12:
        x = ratio + ratio;
        return (float)(x < one ? half - (one - x) * (one - x) * half :
                       (x - one) * (x - one) * half + half);
    case 13:
        x = ratio + ratio;
        return (float)(x < one ? half - (one - x) * (one - x) *
                       (one - x) * half :
                       (x - one) * (x - one) * (x - one) * half + half);
    case 14:
        x = ratio + ratio;
        return (float)(x < one ? half - (one - x) * (one - x) *
                       (one - x) * (one - x) * half :
                       (x - one) * (x - one) * (x - one) * (x - one) *
                       half + half);
    case 15: return 0.0f;
    case 16: return 1.0f;
    default: return (float)ratio;
    }
}
