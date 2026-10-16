// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_418b50.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00418b50(ObjectAccessor_00418b50** items, int count) {
    while (count--) {
        (*items++)->ClearFlag();
    }
    return 0;
}
#pragma code_seg()
