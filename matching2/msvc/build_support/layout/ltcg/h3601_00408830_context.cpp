// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_408830.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3601_00408830_Context(
        IndexAccessor2** items, int* indices, int count) {
    int total = 0;
    while (count--)
        total += (*items++)->Load(*indices++);
    return total;
}
#pragma code_seg()
