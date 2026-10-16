// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_427c90.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall Countdown_00427c90Context_00427c90(Countdown** items, int count) {
    while (count--) {
        (*items++)->Subtract(count);
    }
    return 0;
}
#pragma code_seg()
