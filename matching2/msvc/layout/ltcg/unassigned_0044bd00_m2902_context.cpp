// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0044bd00.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl M2902Context_0044bd00(
        const char* const* titles, int count) {
    int total = 0;
    while (count--)
        total += asm_unassigned_0044bd00(*titles++);
    return total;
}
#pragma code_seg()
