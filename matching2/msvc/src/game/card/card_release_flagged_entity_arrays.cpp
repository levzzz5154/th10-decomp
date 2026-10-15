// 0x004091C0..0x0040921E (95 bytes): release the entities of the score runtime
// state's two arrays of embedded animation VMs - eight at +0x778 and five at
// +0x24D8, both with a 0x3AC stride - when its flag byte at +0x378C asks for it.
//
// Retail is entered with the state in EBX, not ECX, because its only caller
// 0x00409270 is a scheduler callback (registered at 0x00408A11) whose body is
// `push ebx; mov ebx,ecx; call 0x004091C0; pop ebx; ret`: the pair is an /LTCG
// convention pair in which the caller owns the EBX save and the callee keeps the
// state in EBX across all four calls without saving it.  That receiver only
// exists while the callee's body is visible to the whole-program pass *and* the
// callee is not rooted - rooting pins the declared public __thiscall (ECX) ABI,
// which is the wrong register.  The synthetic batch context therefore names the
// call that keeps this model in the link (layout/ltcg/render_batch_context.cpp);
// the callee itself needs no `roots` entry.
//
// Every call uses 0x004451C0's private (manager in ECX, VM in EAX) entry, which
// is reproducible only because the dispatcher is a definition in this same link
// (the recovered AnmVmDrawDispatch of src/core/sprtfunc/anm_vm_draw_dispatch.cpp).  The
// manager is reloaded from ds:0x00491C10 inside each loop body and the loop
// pointer walks the array with `add esi,0x3AC`, so the two loops compile to
// retail's rotated form; the first one is 16-byte aligned, which is the `jmp`
// over the `lea esp,[esp]` + `nop` pad at +0x16.
#include "th10/render/quad_batch.hpp"

// 0x004451C0: dispatch one animation entity's quad.  Defined in
// src/core/sprtfunc/anm_vm_draw_dispatch.cpp and co-compiled by this cluster.
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        AnimationManager_00442F50* manager, RenderEntity* entity);

#include "th10/game/card_runtime.hpp"

#pragma code_seg(".text$001arrays")
int CardRuntime_004091c0::ReleaseFlaggedEntityArrays() {
    if (release_flag_378C & 1) {
        for (int i = 0; i < 8; ++i) {
            asm_FUN_004451c0_004451c0(data_00491c10,
                                      (RenderEntity*)((char*)this + 0x778 + i * 0x3AC));
        }
        for (int i = 0; i < 5; ++i) {
            asm_FUN_004451c0_004451c0(data_00491c10,
                                      (RenderEntity*)((char*)this + 0x24D8 + i * 0x3AC));
        }
    }
    return 1;
}
#pragma code_seg()
