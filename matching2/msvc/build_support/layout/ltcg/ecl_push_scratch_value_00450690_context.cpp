// Compiler context only; never selected as recovered game code.
#include "../../../src/script/sptlib/ecl_push_scratch_value.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall EclPushScratchValueContext(
        EclFrame4** items, int size, int count) {
    int last = 0;
    while (count--) {
        last = (*items++)->Push(size);
    }
    return last;
}
#pragma code_seg()
