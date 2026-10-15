// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004052b0.cpp"

#include "th10/math/timer.hpp"
#pragma code_seg(".text$03context")
int __stdcall AccessorCompilerContext(TimerDecrementer_004052b0** items, int count) {
    while (count--) {
        (*items++)->Decrement(count);
    }
    return 0;
}
#pragma code_seg()
