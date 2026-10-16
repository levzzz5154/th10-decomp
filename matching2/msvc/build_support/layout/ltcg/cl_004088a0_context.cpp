// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_4088a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall IndexContext_004088a0(int* indices, int* bases, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += SlotIndex(indices[i], bases[i]);
    }
    return total;
}
#pragma code_seg()
