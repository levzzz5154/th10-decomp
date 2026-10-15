// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_004053b0_004053b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall FUN004053b0CompilerContext(FUN_004053b0_Triple* out, FUN_004053b0_Triple* values, int count) {
    while (count--) {
        FUN_004053b0_StoreTriple(out, *values);
        out++;
        values++;
    }
    return 0;
}
#pragma code_seg()
