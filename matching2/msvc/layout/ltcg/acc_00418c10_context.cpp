// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00418c10.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00418c10(ObjectAccessor_00418c10** items, int count) {
    while (count--) {
        (*items++)->ClearCounters();
    }
    return 0;
}
#pragma code_seg()
