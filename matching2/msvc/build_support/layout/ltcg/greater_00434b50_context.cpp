// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_434b50.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall GreaterContext_00434b50(
        Object5** items, int* values, int count) {
    int total = 0;
    while (count--)
        total += Greater2(*items++, *values++);
    return total;
}
#pragma code_seg()
