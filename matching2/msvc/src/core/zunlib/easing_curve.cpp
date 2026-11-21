// 0x0044C350..0x0044C58F: evaluate the animation easing table.
enum EasingMode {
    EASE_LINEAR = 0,
    EASE_IN_QUAD = 1,
    EASE_IN_CUBIC = 2,
    EASE_IN_QUART = 3,
    EASE_OUT_QUAD = 4,
    EASE_OUT_CUBIC = 5,
    EASE_OUT_QUART = 6,
    EASE_IN_OUT_QUAD = 9,
    EASE_IN_OUT_CUBIC = 10,
    EASE_IN_OUT_QUART = 11,
    EASE_OUT_IN_QUAD = 12,
    EASE_OUT_IN_CUBIC = 13,
    EASE_OUT_IN_QUART = 14,
    EASE_CONSTANT_ZERO = 15,
    EASE_CONSTANT_ONE = 16
};

#pragma code_seg(".text$01ease")
__declspec(noinline) float __stdcall EvaluateCurve2(
        unsigned int mode, float numerator, float denominator) {
    float ratio = numerator / denominator;
    float x;
    switch (mode) {
    case EASE_IN_QUAD: return ratio * ratio;
    case EASE_OUT_QUAD: x = 1.0f - ratio; return 1.0f - x * x;
    case EASE_IN_CUBIC: return ratio * ratio * ratio;
    case EASE_OUT_CUBIC: return 1.0f - (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio);
    case EASE_IN_QUART: return ratio * ratio * ratio * ratio;
    case EASE_OUT_QUART: return 1.0f - (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio);
    case EASE_IN_OUT_QUAD:
        x = ratio + ratio;
        return x < 1.0f ? x * x * 0.5f
                        : (2.0f - (2.0f - x) * (2.0f - x)) * 0.5f;
    case EASE_OUT_IN_QUAD:
        x = ratio + ratio;
        return x < 1.0f ? 0.5f - (1.0f - x) * (1.0f - x) * 0.5f
                        : (x - 1.0f) * (x - 1.0f) * 0.5f + 0.5f;
    case EASE_IN_OUT_CUBIC:
        x = ratio + ratio;
        return x < 1.0f ? x * x * x * 0.5f
                        : (2.0f - (2.0f - x) * (2.0f - x) * (2.0f - x)) * 0.5f;
    case EASE_OUT_IN_CUBIC:
        x = ratio + ratio;
        return x < 1.0f ? 0.5f - (1.0f - x) * (1.0f - x) * (1.0f - x) * 0.5f
                        : (x - 1.0f) * (x - 1.0f) * (x - 1.0f) * 0.5f + 0.5f;
    case EASE_IN_OUT_QUART:
        x = ratio + ratio;
        return x < 1.0f ? x * x * x * x * 0.5f
                        : (2.0f - (2.0f - x) * (2.0f - x) * (2.0f - x) * (2.0f - x)) * 0.5f;
    case EASE_OUT_IN_QUART:
        x = ratio + ratio;
        return x < 1.0f ? 0.5f - (1.0f - x) * (1.0f - x) * (1.0f - x) * (1.0f - x) * 0.5f
                        : (x - 1.0f) * (x - 1.0f) * (x - 1.0f) * (x - 1.0f) * 0.5f + 0.5f;
    case EASE_CONSTANT_ZERO: return 0.0f;
    case EASE_CONSTANT_ONE: return 1.0f;
    default: return ratio;
    }
}
#pragma code_seg()
