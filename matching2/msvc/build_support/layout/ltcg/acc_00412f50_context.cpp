// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00412f50.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00412f50(ObjectAccessor_00412f50** items, int count) {
    while (count--) {
        (*items++)->SetFlag();
    }
    return 0;
}
#pragma code_seg()
