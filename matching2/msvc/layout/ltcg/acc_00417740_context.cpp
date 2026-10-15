// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00417740.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00417740(ObjectAccessor_00417740** items, int count, double value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
