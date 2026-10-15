// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00417750.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00417750(ObjectAccessor_00417750** items, int count) {
    while (count--) {
        (*items++)->Unlink();
    }
    return 0;
}
#pragma code_seg()
