// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0041be70.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_0041be70(ObjectAccessor_0041be70** items, int count) {
    int total = 0;
    while (count--) {
        total += (int)(*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
