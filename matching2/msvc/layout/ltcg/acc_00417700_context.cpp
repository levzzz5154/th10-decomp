// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00417700.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00417700(ObjectAccessor_00417700** items, int count) {
    while (count--) {
        (*items++)->SetFlag();
    }
    return 0;
}
#pragma code_seg()
