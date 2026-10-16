// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_427e20.cpp"

#pragma code_seg(".text$03context")
float __stdcall Ctx(Vec25* a, Vec25* b, int n) {
    float s = 0;
    for (int i = 0; i < n; ++i) s += a[i].Assign(b[i]).y;
    return s;
}
#pragma code_seg()
