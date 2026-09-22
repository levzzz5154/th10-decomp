// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00434bf0_00434bf0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3301Context_00434bf0(
        H3301Stride9_00434bf0** items, const int* indices, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->GetValue(*indices++);
    }
    return total;
}
#pragma code_seg()
