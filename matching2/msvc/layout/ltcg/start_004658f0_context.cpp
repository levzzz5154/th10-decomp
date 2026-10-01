// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004658f0.cpp"
#pragma code_seg(".text$05context")
int __stdcall StartContext_004658f0(int count) {
    int total = 0;
    while (count--) { StartThread_004658f0(); total += count; }
    return total;
}
#pragma code_seg()
