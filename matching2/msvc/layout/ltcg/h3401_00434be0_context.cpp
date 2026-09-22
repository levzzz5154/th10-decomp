// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00434be0_00434be0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl M3401Context_00434be0(
        H3401Slots_00434be0** objects, const int* indices, int count) {
    int total = 0;
    while (count--)
        total += (*objects++)->Get(*indices++);
    return total;
}
#pragma code_seg()
