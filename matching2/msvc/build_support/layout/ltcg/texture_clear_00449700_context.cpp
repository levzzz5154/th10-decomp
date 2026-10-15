// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN_00449700_00449700.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(TextureHolder_00449700** t, int n) {
    for (int i = 0; i < n; ++i) ClearTexture_00449700(t[i]);
    return 0;
}
#pragma code_seg()
