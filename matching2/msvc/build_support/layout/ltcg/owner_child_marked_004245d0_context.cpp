// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4245d0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall OwnerChildMarkedContext_004245d0(Owner3** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->IsChildMarked();
    }
    return total;
}
#pragma code_seg()
