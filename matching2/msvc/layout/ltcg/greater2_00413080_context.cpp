// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00413080.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall GreaterContext_00413080(
        Rec_00413080** items, int* values, int count) {
    int total = 0;
    while (count--) total += Greater_00413080(*items++, *values++);
    return total;
}
#pragma code_seg()
