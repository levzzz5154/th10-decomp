// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/vec2_scale_00441de0.cpp"

#pragma code_seg(".text$03context")
float __stdcall Ctx(Vec2_00441dd0** a, float f, int n) {
    float s = 0;
    while (n--) s += Scaled_00441de0(*a++, f).x;
    return s;
}
#pragma code_seg()
