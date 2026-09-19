// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004187a0.cpp"
#pragma code_seg(".text$03context")
int __stdcall ResetContext_004187a0(ObjectAccessor_004187a0** items, int count) {
    int total = 0;
    while (count--) {
        total += Reset_004187a0(*items++);
    }
    return total;
}
#pragma code_seg()
