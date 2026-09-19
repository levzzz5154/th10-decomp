// 0x004451C0..0x00445298 (216 bytes): dispatch one animation entity's quad to
// the drawing routine its type selects.
//
// The routine is entered with the animation manager in ECX and the entity in
// EAX - every retail call site loads that pair, `mov ecx,[data_00491c10]` then
// `lea eax,[entity+0x10]`.  It reads the entity's flag word at +0x35C once and
// rejects the entity unless bits 0 and 1 are set and the alpha byte at +0x2FF
// is nonzero, then switches on `(flags >> 22) & 0xF` through a ten-entry jump
// table and returns the selected routine's result, or 0 for a type outside the
// table.  The guard writes the three rejections as separate early returns; the
// compiler tail-merges them into retail's single `or eax,-1; ret` block, and it
// keeps ESI and EDI because the case bodies use them as argument registers.
//
// Nine of the ten case targets are still assembly, and each one enters on
// registers no MSVC declaration names (EAX, EDX, ESI, EDI or the stack), so
// each is compiled into this cluster as a compiled ABI anchor placed at its
// retail address by the layout's gaps: see the dispatcher anchor block in
// layout/ltcg/render_batch_context.cpp.  None of those bodies is recovered
// code; only their parameter homes matter.
//
// The tenth, 0x00444CE0, is the recovered AnimationManager::DrawStrip, whose
// body is a definition in this same link (layout/ltcg/anm_batch_flush_00442f50
// .json co-compiles src/render/edge_strip_draw.cpp).  That is what earns case 9
// the no-move marshalling retail has - `DrawStrip` enters on (ECX manager, EAX
// entity, two stack arguments) only when its own call graph is visible, and it
// is also the third case that wants the entity in EAX, which is what keeps the
// dispatcher's entry pair at (ECX, EAX) instead of letting the pass re-home the
// entity in ESI.
//
// Two declaration-level levers shape the remaining marshalling:
//
//   * 0x004436C0 and 0x00443910 enter on (ECX manager, EDX entity) and are
//     reached with a tail jump, so they are declared __fastcall.  Retail moves
//     the entity from EAX to EDX at each site (`mov edx,eax; jmp`) and so does
//     this model.  Anchoring them instead lets the pass hand them the entry
//     pair itself, and declaring them with a call convention makes the pass
//     re-home the dispatcher's own entity in EDX.
//
//   * 0x00444580 and 0x00443FB0 enter on (ESI entity, EDI manager) and
//     (EDI entity, ESI manager), which no convention names; the pass derives
//     both from the anchor bodies.  Their parameters are declared in the order
//     the callee's register pair implies - (manager, entity) - because the pass
//     assigns the declared first parameter the *second* register of the pair it
//     picks: with the natural order it emitted `mov esi,ecx; mov edi,eax`
//     instead of retail's `mov esi,eax; mov edi,ecx`.
#include "th10/render/quad_batch.hpp"

extern "C" __declspec(noinline) int EntityDraw_00443080(RenderEntity* entity,
                                                               AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int __fastcall QuadDrawChecked_004436c0(AnimationManager_00442F50* manager,
                                                                    RenderEntity* entity);
extern "C" __declspec(noinline) int EntityDraw_00443290(RenderEntity* entity,
                                                               AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int __fastcall QuadDrawCheckedAlt_00443910(AnimationManager_00442F50* manager,
                                                                       RenderEntity* entity);
extern "C" __declspec(noinline) int EntityDraw_00443f80(RenderEntity* entity,
                                                               AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int EntityDraw_00444580(AnimationManager_00442F50* manager,
                                                               RenderEntity* entity);
extern "C" __declspec(noinline) int EntityDraw_00443fb0(AnimationManager_00442F50* manager,
                                                               RenderEntity* entity);
extern "C" __declspec(noinline) int FadedQuadDraw_004445c0(AnimationManager_00442F50* manager,
                                                                  RenderEntity* entity);
extern "C" __declspec(noinline) int EntityDraw_00444760(RenderEntity* entity,
                                                               AnimationManager_00442F50* manager);

#pragma code_seg(".text$06hdispatch")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        AnimationManager_00442F50* manager, RenderEntity* entity) {
    unsigned int flags = entity->flags;
    if (!(flags & 1)) return -1;
    if (!(flags & 2)) return -1;
    if (((const unsigned char*)&entity->color)[3] == 0) return -1;
    switch ((flags >> 22) & 0xF) {
    case 0: return EntityDraw_00443080(entity, manager);
    case 1: return QuadDrawChecked_004436c0(manager, entity);
    case 4: return EntityDraw_00443f80(entity, manager);
    case 5: return EntityDraw_00444580(manager, entity);
    case 6: return EntityDraw_00443fb0(manager, entity);
    case 7: return FadedQuadDraw_004445c0(manager, entity);
    case 8: return EntityDraw_00444760(entity, manager);
    case 9: return manager->DrawStrip(entity, entity->strip_vertices, entity->strip_count * 2);
    case 2: return EntityDraw_00443290(entity, manager);
    case 3: return QuadDrawCheckedAlt_00443910(manager, entity);
    }
    return 0;
}
#pragma code_seg()
