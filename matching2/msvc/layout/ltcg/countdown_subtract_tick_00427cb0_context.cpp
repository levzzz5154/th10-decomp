// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00427cb0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall CountdownSubtractTickContext_00427cb0(Countdown_00427cb0** items, int count) {
    while (count--) {
        (*items++)->SubtractTick();
    }
    return 0;
}
#pragma code_seg()
