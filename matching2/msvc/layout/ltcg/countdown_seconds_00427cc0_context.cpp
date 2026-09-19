// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00427cc0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall CountdownSecondsContext_00427cc0(Countdown_00427cc0** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->Seconds();
    }
    return total;
}
#pragma code_seg()
