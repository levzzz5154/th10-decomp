// Compiler context only. Ghidra has no retail caller for 0x004187F0; this
// null-terminated point list is synthetic context for the native-LTCG model.
#include "../../src/unidentified/unassigned_004187f0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall Vector3TranslateCompilerContext_004187F0(
    Vector3_004187F0* output, const Vector3_004187F0** points) {
    int translatedCount = 0;
    while (*points) {
        *output++ = (*points++)->Translate();
        ++translatedCount;
    }
    return translatedCount;
}
#pragma code_seg()
