// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004014d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PendingCompilerContext(WidgetHost** items, int count) {
    while (count--) {
        (*items++)->ClearPending_004014d0();
    }
    return 0;
}
#pragma code_seg()
