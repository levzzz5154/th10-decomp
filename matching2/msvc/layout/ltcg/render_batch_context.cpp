// Compiler context only; no context bytes count as recovered code.
#include "../../src/render/texture_stage_reset.cpp"
#include "th10/render/camera_batch.hpp"

// The state object the ECL thread hands to SelectStage in ESI. Declared rather
// than included: the model is a separate additional_source translation unit.
struct RenderStageState {
    unsigned char reserved_000[0x388];
    __declspec(noinline) void SelectStage(int index);
};
extern "C" RenderStageState data_00491c28;

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

#pragma code_seg(".text$07context")
int __stdcall RenderBatchContext(const ScreenRect** rects, const unsigned int* colors, int count,
                                  const RenderEntity** entities, const void** vertices, RenderCamera** cameras) {
    for (int i = 0; i < count; ++i) {
        DrawGradientQuad(rects[i], colors[4*i], colors[4*i+1], colors[4*i+2], colors[4*i+3]);
        data_00491c10->DrawStrip(entities[i], vertices[i], colors[i]);
        data_00491c10->DrawQuad(entities[i], (const TexturedVertex*)vertices[i]);
        data_00491c10->DrawFan(entities[i], vertices[i], colors[i]);
        data_00491c10->DrawSolidStrip(entities[i], vertices[i], colors[i]);
        data_00491c10->DrawSolidFan(entities[i], vertices[i], colors[i]);
        data_00491c10->SubmitSpriteQuad(entities[i], colors[i]);
        data_00491c10->SubmitSpriteQuadMirrored(entities[i], colors[i]);
        cameras[i]->Apply();
        cameras[i]->ApplyDefault();
        GameFrameAdvance_00439390(&data_004924f0);
    }
    data_00491c28.SelectStage(0);
    ((RenderStageState_00405300*)&data_00491c28)->SelectDefaultStage(0);
    return count;
}
#pragma code_seg()
