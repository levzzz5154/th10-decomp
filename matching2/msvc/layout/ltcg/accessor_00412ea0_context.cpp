// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00412ea0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00412ea0(ObjectAccessor_00412ea0** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
