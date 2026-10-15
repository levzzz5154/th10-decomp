// Compiler context only; never selected as recovered game code.
#include "../../../src/game/mother/cached_com_slot_release_retail_00421d20.cpp"

#pragma code_seg(".text$03context")
int __stdcall CachedComSlotReleaseRetailCompilerContext(
        CachedComSlot** slots, int count) {
    while (count--)
        (*slots++)->Release();
    return 0;
}
#pragma code_seg()
