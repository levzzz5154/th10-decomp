// Synthetic compiler context only; it is not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_4501f0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall OuterRecordCompilerContext_004501f0(
        OuterRecord** items, int count, int value) {
    int total = 0;
    while (count-- > 0) {
        (*items++)->Store(value);
        ++total;
    }
    return total;
}
#pragma code_seg()
