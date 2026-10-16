// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_4243b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(FieldComparison4** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) total += items[index]->IsValueAt0000LessThan(values[index]);
    return total;
}
#pragma code_seg()
