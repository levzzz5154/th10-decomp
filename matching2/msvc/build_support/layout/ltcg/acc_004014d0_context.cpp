// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4014d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PendingCompilerContext(WidgetHost** items, int count) {
    while (count--) {
        (*items++)->ClearPending2();
    }
    return 0;
}
#pragma code_seg()
