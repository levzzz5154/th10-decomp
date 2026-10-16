// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41ac40.cpp"
#pragma code_seg(".text$03context")
int __stdcall ResetContext_0041ac40(ObjectAccessor_0041ac40** items, int count) {
    while (count--) {
        Reset4(*items++);
    }
    return 0;
}
#pragma code_seg()
