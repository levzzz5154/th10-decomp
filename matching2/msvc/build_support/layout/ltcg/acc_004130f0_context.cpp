// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4130f0.cpp"

#pragma code_seg(".text$03context")
float __stdcall AccessorContext_004130f0(ObjectAccessor_004130f0** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
