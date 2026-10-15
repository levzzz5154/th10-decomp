// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0042aa10.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall ReplayHeaderContext_0042aa10(ReplayHeader_0042aa10** items, int count) {
    while (count--) {
        (*items++)->Initialize();
    }
    return 0;
}
#pragma code_seg()
