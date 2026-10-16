// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_44c000.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(unsigned char** l, const unsigned char** t, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += *ReadLine2(l[i], t[i], n);
    return r;
}
#pragma code_seg()
