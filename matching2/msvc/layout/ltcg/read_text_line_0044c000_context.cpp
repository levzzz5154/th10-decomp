// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0044c000_0044c000.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(unsigned char** l, const unsigned char** t, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += *ReadLine_0044c000(l[i], t[i], n);
    return r;
}
#pragma code_seg()
