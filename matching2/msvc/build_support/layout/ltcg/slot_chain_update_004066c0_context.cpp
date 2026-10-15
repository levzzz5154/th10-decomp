// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_004066c0.cpp"

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall SlotChainUpdateContext(
        SlotChainOwner_004066C0** owners, int count) {
    int result = 0;
    while (count--)
        result = (*owners++)->UpdateAllSlotChains();
    return result;
}
#pragma code_seg()
