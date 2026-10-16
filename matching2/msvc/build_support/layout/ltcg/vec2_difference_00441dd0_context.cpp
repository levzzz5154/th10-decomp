// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_441dd0.cpp"

#pragma code_seg(".text$03context")
float __stdcall Ctx(Vec26** a, Vec26** b, int n) {
    float s = 0;
    while (n--) s += Difference(*a++, *b++).x;
    return s;
}
#pragma code_seg()
