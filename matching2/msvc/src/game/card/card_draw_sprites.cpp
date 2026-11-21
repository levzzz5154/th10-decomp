// 0x00409190 (46 bytes): draw the card's two own sprites - the animation
// objects at +0x10 and +0x3BC - when the player's visible flag is set.
//
// Retail keeps this out-of-line copy without a remaining caller; it enters
// with the card in ESI and hands each sprite to the draw dispatcher at
// 0x004451C0 (sprite in EAX, animation manager in ECX).
struct AnimationManager2;

struct PlayerSprite2 {
    unsigned char reserved[0x3AC];
};

struct CardDrawView {
    unsigned char reserved_0000[0x10];
    PlayerSprite2 body_sprite;                 // +0x0010
    PlayerSprite2 option_sprite;               // +0x03BC
    unsigned char reserved_0768[0x378C - 0x768];
    unsigned char flags;                               // +0x378C

    __declspec(noinline) int DrawSprites();
};

extern "C" AnimationManager2* g_sprt_ctrl;

extern "C" __declspec(noinline) int __cdecl AnmVm_DrawDispatch(
        PlayerSprite2* sprite, AnimationManager2* manager);

#pragma code_seg(".text$01draw")
__declspec(noinline) int CardDrawView::DrawSprites() {
    if (flags & 1) {
        AnmVm_DrawDispatch(&body_sprite, g_sprt_ctrl);
        AnmVm_DrawDispatch(&option_sprite, g_sprt_ctrl);
    }
    return 1;
}
#pragma code_seg()
