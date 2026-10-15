// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00427c90.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall Countdown_00427c90Context_00427c90(Countdown_00427c90** items, int count) {
    while (count--) {
        (*items++)->Subtract(count);
    }
    return 0;
}
#pragma code_seg()
