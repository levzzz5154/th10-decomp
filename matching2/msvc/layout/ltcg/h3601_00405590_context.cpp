// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00405590_00405590.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3601_00405590_Context(
        IndexAccessor_00405590** items, int* indices, int count) {
    int total = 0;
    while (count--)
        total += (*items++)->Load(*indices++);
    return total;
}
#pragma code_seg()
