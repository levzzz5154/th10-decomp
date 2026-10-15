// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00427c40.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall Counter_00427c40Context_00427c40(Counter_00427c40** items, int count) {
    while (count--) {
        (*items++)->Subtract(count);
    }
    return 0;
}
#pragma code_seg()
