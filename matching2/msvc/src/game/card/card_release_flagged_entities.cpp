// 0x00409230..0x00409261 (50 bytes): release the two embedded animation VMs of
// the score runtime state when its flag byte at +0x378C asks for it.
//
// Retail is entered with the state in ECX- this is a scheduler callback, whose
// address escapes at 0x004089EA (`push 0x00409230; call SchedulerCallback_Create`),
// so it keeps the public __thiscall receiver - and holds it in ESI across both
// calls.  Each embedded VM at +0x10 and +0x3BC is handed to 0x004451C0 as
// (manager in ECX, VM in EAX), and the manager is reloaded from ds:0x00491C10
// before the second call because the dispatcher clobbers ECX.
//
// That (ECX manager, EAX VM) pair is the dispatcher's private convention: no
// MSVC declaration names an argument in EAX, so the call site only reproduces it
// when the callee's *body* is in the same /LTCG link.  It is: 0x004451C0 is the
// recovered AnmVmDrawDispatch, a function of this same render-batch cluster
// (src/core/sprtfunc/anm_vm_draw_dispatch.cpp).  With an opaque binding instead, the
// pass falls back to the declared convention and the two `lea eax,[...]` become
// `lea edx,[...]` - byte-exact but handing the dispatcher garbage.
//
// The region is rooted (its `roots` entry in layout/ltcg/anm_batch_flush_00442f50
// .json), because a scheduler callback's receiver is its public ABI: without the
// root the pass is free to re-home it in ESI or EDX and the 50 bytes are not
// retail's.
#include "th10/render/quad_batch.hpp"

// 0x004451C0: dispatch one animation entity's quad.  Defined in
// src/core/sprtfunc/anm_vm_draw_dispatch.cpp and co-compiled by this cluster.
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        SprtCtrlBatchView* manager, RenderEntity* entity);

struct CardRuntime_00409230 {
    unsigned char reserved_0000[0x378C];
    unsigned char release_flag_378C;                 // +0x378C: release when bit 0 is set
    unsigned char reserved_378D[0x400];

    __declspec(noinline) int ReleaseFlaggedEntities();
};

#pragma code_seg(".text$001release")
int CardRuntime_00409230::ReleaseFlaggedEntities() {
    if (release_flag_378C & 1) {
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, (RenderEntity*)((char*)this + 0x10));
        asm_FUN_004451c0_004451c0(g_sprt_ctrl, (RenderEntity*)((char*)this + 0x3BC));
    }
    return 1;
}
#pragma code_seg()
