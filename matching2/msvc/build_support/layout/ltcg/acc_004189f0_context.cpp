// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004189f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_004189f0(ObjectAccessor_004189f0** items, int count) {
    while (count--) {
        (*items++)->IncrementCounters();
    }
    return 0;
}
#pragma code_seg()
