// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/main/resource_file.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Surface_00436ca0** s, unsigned int* c, int n) {
    for (int i = 0; i < n; ++i) FillRgb444_00436ca0(s[i], c[i]);
    return 0;
}
#pragma code_seg()
