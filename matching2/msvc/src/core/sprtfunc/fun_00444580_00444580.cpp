// 0x00444580..0x004445BC (60 bytes): rebuild the entity's projected quad,
// submit it as a plain sprite quad and give the four shared quad vertices the
// opaque depth value.
//
// The dispatcher reaches this helper with the entity in ESI and the manager in
// EDI, which no declaration names, so the body is a selected function of the
// render-batch cluster (layout/ltcg/anm_batch_flush_00442f50.json).
//
// Both callees enter on registers no prototype expresses either: the entity
// quad projection takes its source in EAX with the manager on the stack - the
// `push edi` that opens retail's body is that stack argument, and the callee
// pops it - and SubmitSpriteQuad (0x00442670, a definition of this cluster)
// takes the entity in EAX as well.  Their bodies are co-compiled as ABI anchors
// so the pass reproduces those conventions; see the anchor block of
// layout/ltcg/render_batch_context.cpp.
//
// The four depth stores run back to front in retail (0x497920, 0x497904,
// 0x4978E8, 0x4978CC), which is the order the source lists them in.
#include "th10/render/quad_batch.hpp"

struct ProjectionManager_00444240;
struct ProjectedEntity_00444240 {
    unsigned char reserved_0000[0x334];
    __declspec(noinline) int ProjectQuad(ProjectionManager_00444240* manager);
};

#pragma code_seg(".text$06b07fade")
extern "C" __declspec(noinline) void EntityDraw_00444580(AnimationManager_00442F50* manager,
                                                         RenderEntity* entity) {
    ((ProjectedEntity_00444240*)entity)->ProjectQuad((ProjectionManager_00444240*)manager);
    manager->SubmitSpriteQuad(entity, 0);
    data_004978c0[3].rhw = 1.0f;
    data_004978c0[2].rhw = 1.0f;
    data_004978c0[1].rhw = 1.0f;
    data_004978c0[0].rhw = 1.0f;
}
#pragma code_seg()
