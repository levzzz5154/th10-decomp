// 0x00405300 - Select the active render stage and reapply the *default* camera:
// point the state's active stage at the indexed 0x118-byte stage record, hand
// that record to the camera-default routine at 0x00421480, give its viewport
// block to the render device and publish the index.
//
// Retail reaches the body with the state object in ESI and the index in EBX -
// the only call site (0x00402AEC, the game thread) loads the state's address
// 0x00491C28 into ESI and zeroes EBX - and 0x00421480 reads its record from
// EDI.  Those are whole-program register choices, so both the body and its
// callee are compiled in the native-LTCG cluster
// build_support/layout/ltcg/anm_batch_flush.json; the callee is now the recovered
// member, so no ABI anchor stands in for it.
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera the default setup rewrites followed by
// the fields that make the record the 0x118 bytes the index stride shows. The
// camera sits at offset 0, so the viewport block the device receives is the
// record's +0xCC.
struct RenderStage2 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide state object at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 and the active index at +0x388.
struct RenderStageState2 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage2 stages[2];              // +0x154, stride 0x118
    RenderStage2* active_stage;          // +0x384
    int stage_index;                             // +0x388

    __declspec(noinline) void SelectDefaultStage(int index);
};

#pragma code_seg(".text$000zselect")
void RenderStageState2::SelectDefaultStage(int index) {
    active_stage = &stages[index];
    active_stage->camera.ApplyDefault();
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = index;
}
#pragma code_seg()
