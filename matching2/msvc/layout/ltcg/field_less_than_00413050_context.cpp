// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00413050.cpp"
#pragma code_seg(".text$03context")
int __stdcall IsValueAt0004LessThanContext_00413050(
        FieldComparison_00413050** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += items[index]->IsValueAt0004LessThan(values[index]);
    return total;
}
#pragma code_seg()
