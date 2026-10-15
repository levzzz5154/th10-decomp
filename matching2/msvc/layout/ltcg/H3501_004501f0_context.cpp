// Synthetic compiler context only; it is not recovered game code.
#include "../../src/unreferenced/FUN_004501f0_004501f0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall OuterRecordCompilerContext_004501f0(
        OuterRecord_004501f0** items, int count, int value) {
    int total = 0;
    while (count-- > 0) {
        (*items++)->Store(value);
        ++total;
    }
    return total;
}
#pragma code_seg()
