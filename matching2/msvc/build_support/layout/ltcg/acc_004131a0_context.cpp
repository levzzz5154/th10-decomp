// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4131a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_004131a0(ObjectAccessor_004131a0** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->LoadFlag();
    }
    return total;
}
#pragma code_seg()
