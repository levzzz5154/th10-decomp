// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_004051f0.cpp"

#pragma code_seg(".text$03context")
float __stdcall Ctx(Vec3_004051f0** a, float f, int n) {
    float s = 0;
    while (n--) s += Divided_004051f0(*a++, f).x;
    return s;
}
#pragma code_seg()
