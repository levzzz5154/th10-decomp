// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00405280.cpp"
#pragma code_seg(".text$03context")
int __stdcall PlayerValueAtMostContext_00405280(
        PlayerLeafComparison_00405280** items, int* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += items[index]->IsUnknownValueAt0004AtMost(values[index]);
    return total;
}
#pragma code_seg()
