// 0x00448980..0x004489C2 (67 bytes): draw one animation bucket's entity list.
//
// The body is reached with the bucket index in EAX and the animation manager -
// its receiver - in EDI, and EDI is not preserved: it is an argument register
// here, not a saved one.  No MSVC declaration names that pair, so the function is
// compiled in the native-LTCG cluster
// build_support/layout/ltcg/animation_manager_render_bucket_00448980.json, whose synthetic
// context walks an array of managers and calls it in a loop: the whole-program
// pass then assigns retail's own convention to the selected member (index in EAX,
// `this` in EDI, plain RET).  The function is deliberately *not* in the layout's
// `roots`: rooting it would pin the declared `__thiscall` ABI and the body would
// be emitted with `mov edi,ecx` / `ret 4` instead, which is what the first
// attempt measured.
//
// The per-node draw at 0x004451C0 is entered with the entity in EAX and the
// manager in ECX, another private pair.  Its body is compiled in the same cluster
// as an ABI anchor placed at its retail address by the layout's gaps; only then
// does this body's call emit retail's `mov eax,esi / mov ecx,edi / call` instead
// of the stack-passing approximation the sibling anchor had to accept.
#include "th10/render/quad_batch.hpp"

// One node of a render slot's entity list: the next link at +0x1C, the flag word
// at +0x35C and the per-entity draw callback at +0x39C.  A node with bit 26 of
// its flag word set is skipped (it is the "removed" marker), and a node with a
// non-null callback is offered to it before the per-kind draw dispatch runs.
struct RenderSlotNode_00448980 {
    unsigned char reserved_000[0x1C];
    RenderSlotNode_00448980* next;                          // +0x1C
    unsigned char reserved_020[0x35C - 0x20];
    unsigned int flags;                                     // +0x35C
    unsigned char reserved_360[0x39C - 0x360];
    void (__fastcall* on_render)(RenderSlotNode_00448980*); // +0x39C
};

// 0x004451C0: the per-kind draw dispatch.  The parameter order is load-bearing:
// the anchor's declaration decides the order in which the caller materialises the
// arguments, and retail sets the entity up first (`mov eax,esi`) and the manager
// second (`mov ecx,edi`), so the manager is declared first.
extern "C" int __cdecl asm_FUN_004451c0_004451c0(void* manager, RenderSlotNode_00448980* entity);

#pragma code_seg(".text$03bucket")
int SprtCtrlBatchView::RenderBucket(int index) {
    RenderSlotNode_00448980* node = *(RenderSlotNode_00448980**)
        ((unsigned char*)this + 0x72DB00 + index * 0x3AC);
    while (node != 0) {
        if ((node->flags & 0x4000000u) == 0) {
            if (node->on_render != 0) {
                node->on_render(node);
            }
            asm_FUN_004451c0_004451c0(this, node);
        }
        node = node->next;
    }
    return 1;
}
#pragma code_seg()
