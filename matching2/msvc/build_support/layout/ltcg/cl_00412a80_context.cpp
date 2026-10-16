// Compiler context only; never selected as recovered game code.
#include <string.h>
#include "../../../src/unreferenced/unassigned_412a80.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResolveContext_00412a80(EclOperandSource** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        EclOperandSource* one = items[i];
        total += one->Resolve(count, i);
    }
    return total;
}
#pragma code_seg()
