// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/zunlib/file_read_shared.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(unsigned int* s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += (int)ReadShared2(s[i]);
    return r;
}
#pragma code_seg()
