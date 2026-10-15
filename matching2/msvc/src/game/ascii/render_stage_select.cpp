// 0x00401D20 - Select the active render stage: point the state's active stage
// at the indexed 0x118-byte stage record, reapply that camera, hand its
// viewport block to the render device and publish the index.
//
// Retail reaches the body with the state object in ESI and the index in EBX -
// the only call site (0x0040E8A1, the ECL thread) loads the state's address
// 0x00491C28 into ESI and zeroes EBX - and it calls RenderCamera::Apply with
// the camera in EDI. Those are whole-program register choices, so the body is
// compiled inside the native-LTCG cluster
// layout/ltcg/anm_batch_flush_00442f50.json, whose link already contains
// RenderCamera::Apply (src/game/mother/camera_apply.cpp).
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera Retail reapplies followed by the fields
// that make the record the 0x118 bytes the index stride shows. The camera sits
// at offset 0, so the viewport block the device receives is the record's +0xCC.
struct RenderStage {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide state object at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 and the active index at +0x388.
struct RenderStageState {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                 // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage stages[2];                // +0x154, stride 0x118
    RenderStage* active_stage;            // +0x384
    int stage_index;                      // +0x388

    __declspec(noinline) void SelectStage(int index);
};

#pragma code_seg(".text$000pgselect")
void RenderStageState::SelectStage(int index) {
    active_stage = &stages[index];
    active_stage->camera.Apply();
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = index;
}
#pragma code_seg()
