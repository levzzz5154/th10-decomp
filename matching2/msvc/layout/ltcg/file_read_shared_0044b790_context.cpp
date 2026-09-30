// Compiler context only; its bytes are not recovered game code.
#include "../../src/platform/file_read_shared_0044b790.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(unsigned int* s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += (int)ReadShared_0044b790(s[i]);
    return r;
}
#pragma code_seg()
