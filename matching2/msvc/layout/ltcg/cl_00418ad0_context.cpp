// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00418ad0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00418ad0(ObjectAccessor_00418ad0** items, int count, int value) {
    while (count--) {
        (*items++)->SetBit3(value);
    }
    return 0;
}
#pragma code_seg()
