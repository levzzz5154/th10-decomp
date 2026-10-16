// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_4051f0.cpp"

#pragma code_seg(".text$03context")
float __stdcall Ctx(Vec38** a, float f, int n) {
    float s = 0;
    while (n--) s += Divided(*a++, f).x;
    return s;
}
#pragma code_seg()
