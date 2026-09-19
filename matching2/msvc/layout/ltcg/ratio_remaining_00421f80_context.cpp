// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00421f80.cpp"

#pragma code_seg(".text$03context")
extern "C" float __stdcall RatioRemainingContext_00421f80(Ratio_00421f80** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->Remaining();
    }
    return total;
}
#pragma code_seg()
