// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_00441dd0.cpp"

#pragma code_seg(".text$03context")
float __stdcall Ctx(Vec2_00441dd0** a, Vec2_00441dd0** b, int n) {
    float s = 0;
    while (n--) s += Difference_00441dd0(*a++, *b++).x;
    return s;
}
#pragma code_seg()
