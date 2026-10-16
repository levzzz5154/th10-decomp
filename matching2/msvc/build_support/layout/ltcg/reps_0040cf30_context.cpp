#include "../../../src/unreferenced/unassigned_40cf30.cpp"

#pragma code_seg(".text$03context")
int __stdcall RepsContext_0040cf30(Rec8** items, int count) {
    while (count--) { Init8(0, *items++); }
    return 0;
}
#pragma code_seg()
