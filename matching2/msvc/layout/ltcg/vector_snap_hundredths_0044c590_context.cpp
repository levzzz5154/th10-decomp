// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0044c590_0044c590.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(Vector2_0044c590** p, int n) {
    for (int i = 0; i < n; ++i) p[i]->SnapToHundredths();
}
#pragma code_seg()
