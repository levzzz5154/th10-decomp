// Compiler context only; never selected as recovered game code.
#include "../../../src/game/bullet/bullet_manager_on_draw.cpp"

// 0x004451C0 enters on (EAX sprite, ECX manager). The recovered dispatcher
// lives in the render-batch cluster; this stand-in only fixes the parameter
// homes.
struct Sprite2 {
    unsigned char reserved[0x3AC];
};
struct AnimationManager {
    virtual int Submit(Sprite2* sprite);
};

#pragma code_seg(".text$05dispatch")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        Sprite2* sprite, AnimationManager* manager) {
    if (!(sprite->reserved[0] & 1))
        return -1;
    return manager->Submit(sprite);
}
#pragma code_seg()

#pragma code_seg(".text$07context")
extern "C" __declspec(noinline) int __stdcall EnemySlotAdvanceContext(
        SlotOwner** owners, int count) {
    int result = 0;
    while (count--) {
        result = (*owners++)->OnDraw();
    }
    return result;
}
#pragma code_seg()
