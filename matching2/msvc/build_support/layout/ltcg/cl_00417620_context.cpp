// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_417620.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00417620(ObjectAccessor_00417620** items, int count, int value) {
    while (count--) {
        (*items++)->Mask(value);
    }
    return 0;
}
#pragma code_seg()
