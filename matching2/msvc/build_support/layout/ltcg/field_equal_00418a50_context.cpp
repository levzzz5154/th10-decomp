// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00418a50.cpp"
#pragma code_seg(".text$03context")
int __stdcall IsValueAt0004EqualToContext_00418a50(
        FieldComparison_00418a50** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += items[index]->IsValueAt0004EqualTo(values[index]);
    return total;
}
#pragma code_seg()
