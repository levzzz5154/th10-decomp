#include "../../../src/unreferenced/unassigned_405c80.cpp"

#pragma code_seg(".text$03context")
typedef Rec2* (__fastcall *InitFn_00405c80)(Rec2*);
int __stdcall RepsContext_00405c80(Rec2** items, int count) {
    InitFn_00405c80 fn = Init2;
    while (count--) { fn(*items++); }
    return 0;
}
#pragma code_seg()
