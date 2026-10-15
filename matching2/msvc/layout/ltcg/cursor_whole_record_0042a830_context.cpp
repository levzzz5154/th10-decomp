// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0042a830.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall CursorWholeRecordContext_0042a830(CursorState_0042a830** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->WholeRecordBytes();
    }
    return total;
}
#pragma code_seg()
