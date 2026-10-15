// Synthetic compiler context only; it is not recovered game code.
#include "../../../src/unreferenced/FUN_00427d70_00427d70.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall PairCompilerContext_00427d70(
        Pair_00427d70** items, int count, int first, int second) {
    int total = 0;
    while (count-- > 0) {
        (*items++)->Set(first, second);
        ++total;
    }
    return total;
}
#pragma code_seg()
