// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004245b0.cpp"
#pragma code_seg(".text$03context")
int __stdcall IsValueAt0000EqualToContext_004245b0(
        FieldComparison_004245b0** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += items[index]->IsValueAt0000EqualTo(values[index]);
    return total;
}
#pragma code_seg()
