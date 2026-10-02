// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004067a0_004067a0.cpp"

// 0x004451C0 enters on (EAX sprite, ECX manager). The recovered dispatcher
// lives in the render-batch cluster; this stand-in only fixes the parameter
// homes.
struct Sprite_004067a0 {
    unsigned char reserved[0x3AC];
};
struct AnimationManager_004067a0 {
    virtual int Submit(Sprite_004067a0* sprite);
};

#pragma code_seg(".text$05dispatch")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        Sprite_004067a0* sprite, AnimationManager_004067a0* manager) {
    if (!(sprite->reserved[0] & 1))
        return -1;
    return manager->Submit(sprite);
}
#pragma code_seg()

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) int __stdcall EnemySlotAdvanceContext(
        SlotOwner_004067a0** owners, int count) {
    int result = 0;
    while (count--) {
        result = (*owners++)->AdvanceAllSlots();
    }
    return result;
}
#pragma code_seg()
