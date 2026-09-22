// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0040c820_0040c820.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3601_0040c820_Context(
        IndexAccessor_0040c820** items, int* indices, int count) {
    int total = 0;
    while (count--)
        total += (*items++)->Load(*indices++);
    return total;
}
#pragma code_seg()
