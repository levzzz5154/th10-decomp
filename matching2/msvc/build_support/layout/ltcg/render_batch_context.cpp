// Compiler context only; no context bytes count as recovered code.
#include "../../../src/core/screen/texture_stage_reset.cpp"
#include "th10/render/camera_batch.hpp"

// The state object the ECL thread hands to SelectStage in ESI. Declared rather
// than included: the model is a separate additional_source translation unit.
struct RenderStageState {
    unsigned char reserved_000[0x388];
    __declspec(noinline) void SelectStage(int index);
};
extern "C" RenderStageState g_application;

// 0x00405300's body is the modelled member of the recovered source; declared
// here so this context keeps it alive without pinning its declared __thiscall
// ABI through `roots`, exactly as 0x00401D20 is kept alive by the call below.
struct GameFrame_00439390;
int GameFrameAdvance_00439390(GameFrame_00439390* frame);
extern "C" GameFrame_00439390 data_004924f0;

struct RenderStageState_00405300 {
    unsigned char reserved_000[0x388];
    __declspec(noinline) void SelectDefaultStage(int index);
};

// 0x004091C0's model (src/game/release_flagged_entity_arrays_score_runtime_state
// _004091c0.cpp) is kept alive by the call below - deliberately not by a `roots`
// entry, which would pin its declared __thiscall ABI.  Retail enters that body
// with the state in EBX, the private receiver its caller 0x00409270 supplies.
struct CardRuntime_004091c0 {
    unsigned char reserved_0000[0x378C];
    unsigned char release_flag_378C;
    unsigned char reserved_378D[0x400];
    __declspec(noinline) int ReleaseFlaggedEntityArrays();
};


// 0x00420C90/0x00420D10/0x00420D50 have no retail caller; these calls keep the
// switches in the link without pinning their EDI receiver.
struct RenderStageState_00439390 {
    __declspec(noinline) int EnableFog();
    __declspec(noinline) int EnableDepthWrite();
    __declspec(noinline) int DisableDepthWrite();
};

extern "C" __declspec(noinline) int EntityDrawMirrored_00443480(RenderEntity* entity,
                                                               SprtCtrlBatchView* manager);
#pragma code_seg(".text$07context")
int __stdcall RenderBatchContext(const ScreenRect** rects, const unsigned int* colors, int count,
                                  const RenderEntity** entities, const void** vertices, RenderCamera** cameras) {
    for (int i = 0; i < count; ++i) {
        DrawGradientQuad(rects[i], colors[4*i], colors[4*i+1], colors[4*i+2], colors[4*i+3]);
        g_sprt_ctrl->DrawStrip(entities[i], vertices[i], colors[i]);
        g_sprt_ctrl->DrawQuad(entities[i], (const TexturedVertex*)vertices[i]);
        g_sprt_ctrl->DrawFan(entities[i], vertices[i], colors[i]);
        g_sprt_ctrl->DrawSolidStrip(entities[i], vertices[i], colors[i]);
        g_sprt_ctrl->DrawSolidFan(entities[i], vertices[i], colors[i]);
        g_sprt_ctrl->SubmitSpriteQuad(entities[i], colors[i]);
        g_sprt_ctrl->SubmitSpriteQuadMirrored(entities[i], colors[i]);
        EntityDrawMirrored_00443480((RenderEntity*)entities[i], g_sprt_ctrl);
        cameras[i]->Apply();
        cameras[i]->ApplyDefault();
        GameFrameAdvance_00439390(&data_004924f0);
    }
    g_application.SelectStage(0);
    ((RenderStageState_00405300*)&g_application)->SelectDefaultStage(0);
    // keeps the 0x004091C0 model in the link without pinning its receiver
    ((CardRuntime_004091c0*)&g_application)->ReleaseFlaggedEntityArrays();
    count += ((RenderStageState_00439390*)&g_application)->EnableFog();
    count += ((RenderStageState_00439390*)&g_application)->EnableDepthWrite();
    count += ((RenderStageState_00439390*)&g_application)->DisableDepthWrite();
    return count;
}
#pragma code_seg()
// --- dispatcher ABI anchors (compiled, never exported) ---
extern "C" void __cdecl entry_free_004524a1(void* memory);

#pragma code_seg(".text$06b01anchor")
extern "C" __declspec(noinline) int EntityDraw_00443080(RenderEntity* entity, SprtCtrlBatchView* manager) {
    int a = (int)entity->flags;
    int b = (int)entity->strip_count;
    entry_free_004524a1(entity);
    a += (int)entity->flags;
    entry_free_004524a1((void*)&manager);
    b += (int)entity->color;
    return a + b;
}
#pragma code_seg()

// 0x00443B60's billboard projection enters with the entity in EAX and no
// arguments; 0x00444240's quad projection enters with the entity in EAX and the
// manager on the stack.  The two real bodies are recovered in other clusters,
// which cannot be co-compiled here, so these anchor bodies stand at their
// retail addresses and earn those conventions: a member whose body touches the
// receiver first gets the register, and the second statement decides which of
// the remaining pair goes on the stack.
struct ProjectionManager_00444240;
struct ProjectedEntity_00444240 {
    unsigned char reserved_0000[0x334];
    __declspec(noinline) int ProjectQuad(ProjectionManager_00444240* manager);
};
struct BillboardSource_00443B60 {
    unsigned char reserved_0000[0x35C];
    __declspec(noinline) int BuildProjectedQuad();
};

#pragma code_seg(".text$06b04z01anchor")
int BillboardSource_00443B60::BuildProjectedQuad() {
    entry_free_004524a1(this);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$06b0602anchor")
int ProjectedEntity_00444240::ProjectQuad(ProjectionManager_00444240* manager) {
    entry_free_004524a1(this);
    entry_free_004524a1(manager);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$06b08anchor")
extern "C" __declspec(noinline) int FadedQuadDraw_004445c0(SprtCtrlBatchView* manager, RenderEntity* entity) {
    entry_free_004524a1((void*)1);
    entry_free_004524a1(entity);
    entry_free_004524a1(manager);
    return 0;
}
#pragma code_seg()


#pragma code_seg(".text$04ap")
extern "C" __declspec(noinline) void SyncRenderState_004423e0(
        SprtCtrlBatchView* manager, RenderEntity* entity) {
    int a = (int)entity->flags;
    entry_free_004524a1((void*)1);
    if (manager->quad_count) manager->Flush();
    a += (int)entity->strip_count;
    entry_free_004524a1(entity->texture);
    entry_free_004524a1((void*)(size_t)a);
}
#pragma code_seg()
