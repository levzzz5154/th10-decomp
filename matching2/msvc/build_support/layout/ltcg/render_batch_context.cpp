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
struct GameFrame;
int GameFrameAdvance(GameFrame* frame);
extern "C" GameFrame g_main_window;

struct RenderStageState2 {
    unsigned char reserved_000[0x388];
    __declspec(noinline) void SelectDefaultStage(int index);
};

// 0x004091C0's model (src/game/release_flagged_entity_arrays_score_runtime_state
// _004091c0.cpp) is kept alive by the call below - deliberately not by a `roots`
// entry, which would pin its declared __thiscall ABI.  Retail enters that body
// with the state in EBX, the private receiver its caller 0x00409270 supplies.
struct CardRuntime {
    unsigned char reserved_0000[0x378C];
    unsigned char release_flag_378C;
    unsigned char reserved_378D[0x400];
    __declspec(noinline) int ReleaseFlaggedEntityArrays();
};


// 0x00420C90/0x00420D10/0x00420D50 have no retail caller; these calls keep the
// switches in the link without pinning their EDI receiver.
struct RenderStageState4 {
    __declspec(noinline) int EnableFog();
    __declspec(noinline) int EnableDepthWrite();
    __declspec(noinline) int DisableDepthWrite();
};

extern "C" __declspec(noinline) int EntityDrawMirrored(RenderEntity* entity,
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
        EntityDrawMirrored((RenderEntity*)entities[i], g_sprt_ctrl);
        cameras[i]->Apply();
        cameras[i]->ApplyDefault();
        GameFrameAdvance(&g_main_window);
    }
    g_application.SelectStage(0);
    ((RenderStageState2*)&g_application)->SelectDefaultStage(0);
    // keeps the 0x004091C0 model in the link without pinning its receiver
    ((CardRuntime*)&g_application)->ReleaseFlaggedEntityArrays();
    count += ((RenderStageState4*)&g_application)->EnableFog();
    count += ((RenderStageState4*)&g_application)->EnableDepthWrite();
    count += ((RenderStageState4*)&g_application)->DisableDepthWrite();
    return count;
}
#pragma code_seg()
// --- dispatcher ABI anchors (compiled, never exported) ---
extern "C" void __cdecl crt_free_startup(void* memory);

#pragma code_seg(".text$06b01anchor")
extern "C" __declspec(noinline) int EntityDraw(RenderEntity* entity, SprtCtrlBatchView* manager) {
    int a = (int)entity->flags;
    int b = (int)entity->strip_count;
    crt_free_startup(entity);
    a += (int)entity->flags;
    crt_free_startup((void*)&manager);
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
struct ProjectionManager;
struct ProjectedEntity {
    unsigned char reserved_0000[0x334];
    __declspec(noinline) int ProjectQuad(ProjectionManager* manager);
};
struct BillboardSource {
    unsigned char reserved_0000[0x35C];
    __declspec(noinline) int BuildProjectedQuad();
};

#pragma code_seg(".text$06b04z01anchor")
int BillboardSource::BuildProjectedQuad() {
    crt_free_startup(this);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$06b0602anchor")
int ProjectedEntity::ProjectQuad(ProjectionManager* manager) {
    crt_free_startup(this);
    crt_free_startup(manager);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$06b08anchor")
extern "C" __declspec(noinline) int FadedQuadDraw(SprtCtrlBatchView* manager, RenderEntity* entity) {
    crt_free_startup((void*)1);
    crt_free_startup(entity);
    crt_free_startup(manager);
    return 0;
}
#pragma code_seg()


#pragma code_seg(".text$04ap")
extern "C" __declspec(noinline) void SyncRenderState2(
        SprtCtrlBatchView* manager, RenderEntity* entity) {
    int a = (int)entity->flags;
    crt_free_startup((void*)1);
    if (manager->quad_count) manager->Flush();
    a += (int)entity->strip_count;
    crt_free_startup(entity->texture);
    crt_free_startup((void*)(size_t)a);
}
#pragma code_seg()
