// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00412f80.cpp"

#pragma code_seg(".text$03context")
float __stdcall AccessorContext_00412f80(ObjectAccessor_00412f80** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->LoadValue();
    }
    return total;
}
#pragma code_seg()
