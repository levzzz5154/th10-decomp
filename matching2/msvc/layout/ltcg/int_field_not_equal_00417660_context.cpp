// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00417660.cpp"
#pragma code_seg(".text$03context")
int __stdcall IntFieldNotEqualContext_00417660(
        UnidentifiedIntField_00417660** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += items[index]->IsNotEqualTo(values[index]);
    return total;
}
#pragma code_seg()
