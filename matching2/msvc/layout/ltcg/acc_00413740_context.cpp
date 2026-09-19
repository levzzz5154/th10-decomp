// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00413740.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00413740(ObjectAccessor_00413740** items, int count) {
    while (count--) {
        (*items++)->SetFlagAndClear();
    }
    return 0;
}
#pragma code_seg()
