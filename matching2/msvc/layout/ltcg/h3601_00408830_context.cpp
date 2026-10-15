// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_00408830_00408830.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3601_00408830_Context(
        IndexAccessor_00408830** items, int* indices, int count) {
    int total = 0;
    while (count--)
        total += (*items++)->Load(*indices++);
    return total;
}
#pragma code_seg()
