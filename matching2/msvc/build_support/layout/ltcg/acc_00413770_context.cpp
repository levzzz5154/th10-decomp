// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_413770.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00413770(ObjectAccessor_00413770** items, int count) {
    while (count--) {
        (*items++)->SetFlag();
    }
    return 0;
}
#pragma code_seg()
