// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_0040ce40_0040ce40.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3301Context_0040ce40(
        H3301Outer_0040ce40** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->GetValue();
    }
    return total;
}
#pragma code_seg()
