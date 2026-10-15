// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004176f0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_004176f0(ObjectAccessor_004176f0** items, int count) {
    while (count--) {
        (*items++)->ClearFlag();
    }
    return 0;
}
#pragma code_seg()
