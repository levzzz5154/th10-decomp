// 0x00449440: draw one animation entity with the global animation manager.
// Retail has no callers left; the out-of-line copy keeps the whole-program
// convention of its inlined uses - the entity arrives in EAX and passes
// straight through to 0x004451C0, which takes (EAX entity, ECX manager), so
// the body is one load of the manager and a tail jump. The layout
// build_support/layout/ltcg/draw_global_animation.json reproduces that convention.
struct AnimationManager14;
struct RenderEntity2;

extern "C" AnimationManager14* g_sprt_ctrl;

extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        RenderEntity2* entity, AnimationManager14* manager);

#pragma code_seg(".text$03draw")
__declspec(noinline) int DrawGlobalAnimation(RenderEntity2* entity) {
    return asm_FUN_004451c0_004451c0(entity, g_sprt_ctrl);
}
#pragma code_seg()
