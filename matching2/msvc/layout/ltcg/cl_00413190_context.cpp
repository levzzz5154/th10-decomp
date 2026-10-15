// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00413190.cpp"
#pragma code_seg(".text$03context")
int __stdcall ClearContext_00413190(void** items, int count) {
    while (count--) {
        ClearBlock_00413190(*items++);
    }
    return 0;
}
#pragma code_seg()
