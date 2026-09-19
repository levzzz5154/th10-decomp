// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00418af0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00418af0(ObjectAccessor_00418af0** items, int count, int value) {
    while (count--) {
        (*items++)->SetBit1(value);
    }
    return 0;
}
#pragma code_seg()
