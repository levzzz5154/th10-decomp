// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004067a0_004067a0.cpp"

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall EnemySlotAdvanceContext(
        SlotOwner_004067a0** owners, int count) {
    int result = 0;
    while (count--) {
        result = (*owners++)->AdvanceAllSlots();
    }
    return result;
}
#pragma code_seg()
