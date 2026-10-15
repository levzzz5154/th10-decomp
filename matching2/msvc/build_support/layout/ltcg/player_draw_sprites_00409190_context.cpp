// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../../src/game/card/card_draw_sprites.cpp"

// 0x004451C0 enters on (EAX entity, ECX manager). The recovered dispatcher
// lives in the render-batch cluster; this stand-in only fixes the parameter
// homes.
struct AnimationManager_00409190 {
    virtual int Submit(PlayerSprite_00409190* sprite);
};

#pragma code_seg(".text$03dispatch")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        PlayerSprite_00409190* sprite, AnimationManager_00409190* manager) {
    if (!(sprite->reserved[0] & 1))
        return -1;
    return manager->Submit(sprite);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall PlayerDrawSpritesCompilerContext_00409190(CardDrawView** players, int count) {
    int total = 0;
    while (count--) {
        CardDrawView* player = *players++;
        total += player->DrawSprites();
        total += player->DrawSprites();
    }
    return total;
}
#pragma code_seg()
