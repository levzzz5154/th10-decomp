// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00417730.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00417730(ObjectAccessor_00417730** items, int count, double value) {
    while (count--) {
        (*items++)->StoreValue(value);
    }
    return 0;
}
#pragma code_seg()
