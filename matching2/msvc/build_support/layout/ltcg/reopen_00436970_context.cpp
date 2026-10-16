// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_436970.cpp"
#pragma code_seg(".text$03context")
int __stdcall ReopenContext_00436970(Record4** items, int count) {
    while (count--) (*items++)->Reopen();
    return 0;
}
#pragma code_seg()
