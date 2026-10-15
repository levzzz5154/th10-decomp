// 0x00448740..0x0044876F (48 bytes): clear the shake offsets and the stored
// sprite origin, then render render-slot 14.
//
// GameStateInit stores this address as the on_tick routine of one of the twenty
// scheduler records it creates (record+0x08, priority 0x24, record+0x20 = the
// manager), and the scheduler calls a routine with its context in ECX, so the
// body is reached with the manager there.  The body clears the two shake offsets
// the camera setup copies into the active view (data_00491E64/data_00491E68),
// clears the manager's own sprite origin (origin_x/origin_y at +0x5C/+0x60, the
// pair the quad pipelines add to every sprite corner) and then walks render-slot
// 14's entity list through 0x00448980, returning that call's result.
//
// Two shapes are load-bearing, both measured against retail's own 48 bytes:
//
// 1. The shake pair is written through a pointer to the record.  Writing the two
//    fields directly through the global emits the same instructions but lets the
//    pass sink both stores past the argument setup (they land just before the
//    call), which costs the whole store order; the derived pointer keeps them
//    where retail has them.  The two stores use the immediate form for an
//    absolute address while the two origin stores use the shared zero register -
//    that split is the compiler's, and it is what the pointer form reproduces.
// 2. 0x00448980 reads the manager from EDI and the slot index from EAX -
//    registers no MSVC declaration names - so its body is compiled in the
//    native-LTCG cluster layout/ltcg/fun_00448740_wave11.json as an ABI anchor:
//    a C++ body placed at the retail address, validated, and never exported as
//    recovered code.  With its body visible the pass enters it with the manager
//    in EDI (which the body keeps across its loop) and the index in EAX, and the
//    caller reproduces retail's `push edi` / `mov edi,ecx` / `pop edi` around the
//    call.
#include "th10/render/quad_batch.hpp"

// The two adjacent shake offsets at 0x00491E64: the camera setup copies them
// into the active view's offset pair and the shake task at 0x0043C710 writes
// them from its sine terms.
struct ShakeOffset_00448740 {
    float x;    // 0x00491E64
    float y;    // 0x00491E68
};
extern "C" ShakeOffset_00448740 data_00491e64;

// 0x00448980: walk the entity list of one render slot.
extern "C" int __cdecl asm_AnimationManager_RenderBucket_00448980(
    SprtCtrlBatchView* manager, int slot);

#pragma code_seg(".text$01slot14")
int SprtCtrlBatchView::ResetOriginAndRenderSlot14() {
    ShakeOffset_00448740* shake = &data_00491e64;
    shake->x = 0.0f;
    shake->y = 0.0f;
    g_sprt_ctrl->origin_x = 0.0f;
    g_sprt_ctrl->origin_y = 0.0f;
    return asm_AnimationManager_RenderBucket_00448980(this, 14);
}
#pragma code_seg()
