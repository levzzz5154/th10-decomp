// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00439350.cpp"

#pragma code_seg(".text$03context")
int __stdcall ApplySettingsCompilerContext(int count) {
    while (count--) {
        ApplySettings();
    }
    return 0;
}
#pragma code_seg()
