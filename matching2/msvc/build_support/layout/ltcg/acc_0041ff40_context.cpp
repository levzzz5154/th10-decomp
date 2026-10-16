// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41ff40.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_0041ff40(ObjectAccessor_0041ff40** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->LoadFlag();
    }
    return total;
}
#pragma code_seg()
