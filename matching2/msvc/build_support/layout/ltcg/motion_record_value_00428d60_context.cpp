// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00428d60.cpp"

#pragma code_seg(".text$03context")
extern "C" float __stdcall MotionRecordValueContext_00428d60(MotionRecord_00428d60** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->GetValue();
    }
    return total;
}
#pragma code_seg()
