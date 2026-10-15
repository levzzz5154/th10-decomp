// 0x00409190 (46 bytes): draw the player's two own sprites - the animation
// objects at +0x10 and +0x3BC - when the player's visible flag is set.
//
// Retail keeps this out-of-line copy without a remaining caller; it enters
// with the player in ESI and hands each sprite to the draw dispatcher at
// 0x004451C0 (sprite in EAX, animation manager in ECX).
struct AnimationManager_00409190;

struct PlayerSprite_00409190 {
    unsigned char reserved[0x3AC];
};

struct CardDrawView {
    unsigned char reserved_0000[0x10];
    PlayerSprite_00409190 body_sprite;                 // +0x0010
    PlayerSprite_00409190 option_sprite;               // +0x03BC
    unsigned char reserved_0768[0x378C - 0x768];
    unsigned char flags;                               // +0x378C

    __declspec(noinline) int DrawSprites();
};

extern "C" AnimationManager_00409190* g_sprt_ctrl;

extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        PlayerSprite_00409190* sprite, AnimationManager_00409190* manager);

#pragma code_seg(".text$01draw")
__declspec(noinline) int CardDrawView::DrawSprites() {
    if (flags & 1) {
        asm_FUN_004451c0_004451c0(&body_sprite, g_sprt_ctrl);
        asm_FUN_004451c0_004451c0(&option_sprite, g_sprt_ctrl);
    }
    return 1;
}
#pragma code_seg()
