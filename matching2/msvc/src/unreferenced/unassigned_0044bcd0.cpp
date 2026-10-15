// 0x0044BCD0: rotate a vector by an angle in radians.
#include <math.h>
struct Vec2_0044bcd0 {
    float x, y;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall Rotate(const Vec2_0044bcd0* v, Vec2_0044bcd0* out, float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    out->x = c * v->x - s * v->y;
    out->y = c * v->y + s * v->x;
}
#pragma code_seg()
