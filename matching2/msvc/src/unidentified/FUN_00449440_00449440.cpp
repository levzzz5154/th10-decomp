// 0x00449440: draw one animation entity with the global animation manager.
// Retail has no callers left; the out-of-line copy keeps the whole-program
// convention of its inlined uses - the entity arrives in EAX and passes
// straight through to 0x004451C0, which takes (EAX entity, ECX manager), so
// the body is one load of the manager and a tail jump. The layout
// layout/ltcg/draw_global_animation_00449440.json reproduces that convention.
struct AnimationManager_00449440;
struct RenderEntity_00449440;

extern "C" AnimationManager_00449440* data_00491c10;

extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        RenderEntity_00449440* entity, AnimationManager_00449440* manager);

#pragma code_seg(".text$03draw")
__declspec(noinline) int DrawGlobalAnimation_00449440(RenderEntity_00449440* entity) {
    return asm_FUN_004451c0_004451c0(entity, data_00491c10);
}
#pragma code_seg()
