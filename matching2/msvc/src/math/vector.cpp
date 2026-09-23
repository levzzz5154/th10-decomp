#include <math.h>

// Both retail entries use __thiscall: this is in ECX, followed by angle and
// scale on the stack. The semantic C++ spelling preserves the two field
// writes; sinf/cosf do not reproduce the fused FSINCOS instruction or its
// exact floating-point rounding.
struct PolarVector2_0041F800 {
    float x;
    float y;

    __declspec(noinline) void __thiscall SetPolar(float angle, float scale);
};

// 0x0041F800..0x0041F81D: ?SetPolar@Vector2@@
void __thiscall PolarVector2_0041F800::SetPolar(float angle, float scale) {
    x = cosf(angle) * scale;
    y = sinf(angle) * scale;
}

struct PolarVector2_004458B0 {
    float x;
    float y;

    __declspec(noinline) void __thiscall SetPolar(float angle, float scale);
};

// 0x004458B0..0x004458CD: Vector2_SetPolar
void __thiscall PolarVector2_004458B0::SetPolar(float angle, float scale) {
    x = cosf(angle) * scale;
    y = sinf(angle) * scale;
}
