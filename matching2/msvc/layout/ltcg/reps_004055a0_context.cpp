#include "../../src/unreferenced/unassigned_004055a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall RepsContext_004055a0(Rec_004055a0** items, int count) {
    while (count--) { Init_004055a0(0, *items++); }
    return 0;
}
#pragma code_seg()
