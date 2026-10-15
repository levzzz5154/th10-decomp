#include "../../src/game/mother/slot_lock_leaves.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall D3703SlotLockContext_00421c50(
        SlotLockManager** managers, int* indices, int count) {
    for (int i = 0; i < count; ++i)
        managers[i]->Leave(indices[i]);
    return 0;
}
#pragma code_seg()
