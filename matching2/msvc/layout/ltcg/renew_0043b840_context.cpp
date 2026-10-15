// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0043b840.cpp"
#pragma code_seg(".text$03context")
int __stdcall RecordContext_0043b840(Record_0043b840** items, int count) {
    while (count--) (*items++)->Renew();
    return 0;
}
#pragma code_seg()
