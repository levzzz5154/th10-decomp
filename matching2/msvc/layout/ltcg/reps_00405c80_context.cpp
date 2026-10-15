#include "../../src/unreferenced/unassigned_00405c80.cpp"

#pragma code_seg(".text$03context")
typedef Rec_00405c80* (__fastcall *InitFn_00405c80)(Rec_00405c80*);
int __stdcall RepsContext_00405c80(Rec_00405c80** items, int count) {
    InitFn_00405c80 fn = Init_00405c80;
    while (count--) { fn(*items++); }
    return 0;
}
#pragma code_seg()
