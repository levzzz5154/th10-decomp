// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/handle_record_release.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecordReleaseContext_0043b890(Record_0043b890** items, int count) {
    while (count--) (*items++)->Release();
    return 0;
}
#pragma code_seg()
