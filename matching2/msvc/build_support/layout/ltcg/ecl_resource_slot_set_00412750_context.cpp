// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_412750.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(SlotTable2** t, int* id, int* v, int n) {
    for (int i = 0; i < n; ++i) SetSlot(t[i], i, id[i], v[0], v[1], v[2]);
    return 0;
}
#pragma code_seg()
