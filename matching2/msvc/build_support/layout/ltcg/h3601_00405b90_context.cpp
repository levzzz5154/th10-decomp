// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_405b90.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3601_00405b90_Context(
        ShortAccessor** items, int count) {
    int total = 0;
    while (count--)
        total += (*items++)->Load();
    return total;
}
#pragma code_seg()
