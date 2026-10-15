// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00427e70.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall BusyStateIsBusyContext_00427e70(BusyState_00427e70** items, int count) {
    int busy = 0;
    while (count--) {
        busy += (*items++)->IsBusy();
    }
    return busy;
}
#pragma code_seg()
