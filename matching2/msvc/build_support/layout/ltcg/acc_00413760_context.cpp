// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_413760.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_00413760(ObjectAccessor_00413760** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->LoadFlag();
    }
    return total;
}
#pragma code_seg()
