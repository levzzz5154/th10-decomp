// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00428f20.cpp"

#pragma code_seg(".text$03context")
extern "C" float __stdcall ScalarRecordValueContext_00428f20(ScalarRecord_00428f20** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->GetValue();
    }
    return total;
}
#pragma code_seg()
