// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0041ab00.cpp"

#pragma code_seg(".text$03context")
int __stdcall AccessorContext_0041ab00(ObjectAccessor_0041ab00** items, int count) {
    int total = 0;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
