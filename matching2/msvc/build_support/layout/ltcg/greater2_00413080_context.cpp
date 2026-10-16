// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_413080.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall GreaterContext_00413080(
        Rec11** items, int* values, int count) {
    int total = 0;
    while (count--) total += Greater(*items++, *values++);
    return total;
}
#pragma code_seg()
