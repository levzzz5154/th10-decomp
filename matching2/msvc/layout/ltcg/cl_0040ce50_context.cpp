// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0040ce50.cpp"

#pragma code_seg(".text$03context")
int __stdcall SetMaxContext_0040ce50(Options_0040ce50** items, int* values, int count) {
    for (int i = 0; i < count; ++i) {
        items[i]->SetMax(values[i]);
    }
    return 0;
}
#pragma code_seg()
