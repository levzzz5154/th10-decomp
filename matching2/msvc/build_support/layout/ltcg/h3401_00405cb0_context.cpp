// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00405cb0_00405cb0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl M3401Context_00405cb0(
        const int* values, int count) {
    int total = 0;
    while (count--)
        total += asm_FUN_00405cb0_00405cb0(*values++);
    return total;
}
#pragma code_seg()
