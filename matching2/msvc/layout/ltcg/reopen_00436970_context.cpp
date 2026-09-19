// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00436970.cpp"
#pragma code_seg(".text$03context")
int __stdcall ReopenContext_00436970(Record_00436970** items, int count) {
    while (count--) (*items++)->Reopen();
    return 0;
}
#pragma code_seg()
