// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_004243e0.cpp"
#pragma code_seg(".text$03context")
int __stdcall IsValueAt0000NotEqualToContext_004243e0(
        FieldComparison_004243e0** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += items[index]->IsValueAt0000NotEqualTo(values[index]);
    return total;
}
#pragma code_seg()
