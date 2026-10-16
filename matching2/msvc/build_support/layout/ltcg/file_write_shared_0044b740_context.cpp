// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/zunlib/file_write_shared.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(const void** b, unsigned int* s, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += WriteShared2(b[i], s[i]);
    return r;
}
#pragma code_seg()
