// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4175c0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_004175c0(ObjectAccessor_004175c0** items, int count) {
    while (count--) {
        (*items++)->SetFlag();
    }
    return 0;
}
#pragma code_seg()
