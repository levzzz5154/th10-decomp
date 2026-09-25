#include <math.h>

// 0x0044C5D0..0x0044C5ED: Recovery_PolarToVectorRetail
// Ghidra confirms a __thiscall receiver in ECX and (angle, scale) on the
// stack. Writes are x at offset 0 then y at offset 4. This readable model
// does not claim retail's fused FSINCOS instruction or identical rounding.
struct RecoveryPolarVector2_0044C5D0 {
    float x;
    float y;

    __declspec(noinline) void SetFromPolar(
        float angle, float scale);
};

void RecoveryPolarVector2_0044C5D0::SetFromPolar(
    float angle, float scale) {
    x = cosf(angle) * scale;
    y = sinf(angle) * scale;
}
