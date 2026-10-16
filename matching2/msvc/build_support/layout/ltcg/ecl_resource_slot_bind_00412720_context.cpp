// Compiler context only; its bytes are not recovered game code.
#include "../../../src/game/enemy/ecl_set_resource_slot.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(SlotTable** t, int* id, const char** d, int n) {
    for (int i = 0; i < n; ++i) BindSlot(t[i], i, id[i], n, d[i] + 0x20);
    return 0;
}
#pragma code_seg()
