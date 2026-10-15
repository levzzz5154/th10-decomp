// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00418b10.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00418b10(ObjectAccessor_00418b10** items, int count, int value) {
    while (count--) {
        (*items++)->SetBit0(value);
    }
    return 0;
}
#pragma code_seg()
