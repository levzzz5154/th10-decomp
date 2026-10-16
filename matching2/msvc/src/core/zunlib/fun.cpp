// 0x0044C350..0x0044C58F: evaluate the animation easing table.
#pragma code_seg(".text$01ease")
__declspec(noinline) float __stdcall EvaluateCurve2(
        unsigned int mode, float numerator, float denominator) {
    float ratio = numerator / denominator;
    float x;
    switch (mode) {
    case 1: return ratio * ratio;
    case 4: x = 1.0f - ratio; return 1.0f - x * x;
    case 2: return ratio * ratio * ratio;
    case 5: return 1.0f - (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio);
    case 3: return ratio * ratio * ratio * ratio;
    case 6: return 1.0f - (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio);
    case 9:
        x = ratio + ratio;
        return x < 1.0f ? x * x * 0.5f
                        : (2.0f - (2.0f - x) * (2.0f - x)) * 0.5f;
    case 12:
        x = ratio + ratio;
        return x < 1.0f ? 0.5f - (1.0f - x) * (1.0f - x) * 0.5f
                        : (x - 1.0f) * (x - 1.0f) * 0.5f + 0.5f;
    case 10:
        x = ratio + ratio;
        return x < 1.0f ? x * x * x * 0.5f
                        : (2.0f - (2.0f - x) * (2.0f - x) * (2.0f - x)) * 0.5f;
    case 13:
        x = ratio + ratio;
        return x < 1.0f ? 0.5f - (1.0f - x) * (1.0f - x) * (1.0f - x) * 0.5f
                        : (x - 1.0f) * (x - 1.0f) * (x - 1.0f) * 0.5f + 0.5f;
    case 11:
        x = ratio + ratio;
        return x < 1.0f ? x * x * x * x * 0.5f
                        : (2.0f - (2.0f - x) * (2.0f - x) * (2.0f - x) * (2.0f - x)) * 0.5f;
    case 14:
        x = ratio + ratio;
        return x < 1.0f ? 0.5f - (1.0f - x) * (1.0f - x) * (1.0f - x) * (1.0f - x) * 0.5f
                        : (x - 1.0f) * (x - 1.0f) * (x - 1.0f) * (x - 1.0f) * 0.5f + 0.5f;
    case 15: return 0.0f;
    case 16: return 1.0f;
    default: return ratio;
    }
}
#pragma code_seg()
