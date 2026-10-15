// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00424610.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl M2902Context_00424610(
        const int* values, int count) {
    int total = 0;
    while (count--)
        total += asm_unassigned_00424610(*values++);
    return total;
}
#pragma code_seg()
