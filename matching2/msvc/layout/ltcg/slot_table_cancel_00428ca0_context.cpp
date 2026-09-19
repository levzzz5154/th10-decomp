// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00428ca0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall SlotTableCancelContext_00428ca0(SlotTable_00428ca0** items, int id, int count) {
    while (count--) {
        (*items++)->Cancel(id);
    }
    return 0;
}
#pragma code_seg()
