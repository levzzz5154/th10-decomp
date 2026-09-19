// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00418cc0.cpp"
#pragma code_seg(".text$03context")
int __stdcall ResetContext_00418cc0(ObjectAccessor_00418cc0** items, int count) {
    while (count--) {
        Reset_00418cc0(*items++);
    }
    return 0;
}
#pragma code_seg()
