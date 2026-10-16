// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_44c590.cpp"

#pragma code_seg(".text$zzcontext")
void __stdcall Ctx(Vector25** p, int n) {
    for (int i = 0; i < n; ++i) p[i]->SnapToHundredths();
}
#pragma code_seg()
