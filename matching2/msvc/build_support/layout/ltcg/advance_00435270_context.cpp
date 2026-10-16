// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_435270.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall AdvanceContext_00435270(
        int*** items, int count) {
    int total = 0;
    while (count--)
        total += Advance2(*items++);
    return total;
}
#pragma code_seg()
