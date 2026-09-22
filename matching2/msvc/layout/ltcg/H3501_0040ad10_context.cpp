// Synthetic compiler context only; it is not recovered game code.
#include "../../src/unidentified/FUN_0040ad10_0040ad10.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall CopyPairCompilerContext(
        CopyPair_0040ad10** items, int count) {
    int total = 0;
    while (count-- > 0) {
        (*items++)->CopyFirstToSecond();
        ++total;
    }
    return total;
}
#pragma code_seg()
