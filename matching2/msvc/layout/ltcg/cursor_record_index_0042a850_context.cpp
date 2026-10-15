// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0042a850.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall CursorRecordIndexContext_0042a850(CursorState_0042a850** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->RecordIndex();
    }
    return total;
}
#pragma code_seg()
