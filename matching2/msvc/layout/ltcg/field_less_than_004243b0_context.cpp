// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_004243b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(FieldComparison_004243b0** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) total += items[index]->IsValueAt0000LessThan(values[index]);
    return total;
}
#pragma code_seg()
