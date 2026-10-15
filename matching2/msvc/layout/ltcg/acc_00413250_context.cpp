// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00413250.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00413250(ObjectAccessor_00413250** items, int count, float value) {
    while (count--) {
        (*items++)->Scale(value);
    }
    return 0;
}
#pragma code_seg()
