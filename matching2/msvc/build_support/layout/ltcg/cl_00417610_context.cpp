// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_417610.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00417610(ObjectAccessor_00417610** items, int count, int value) {
    while (count--) {
        (*items++)->Mask(value);
    }
    return 0;
}
#pragma code_seg()
