// 0x00405300 - Select the active render stage and reapply the *default* camera:
// point the state's active stage at the indexed 0x118-byte stage record, hand
// that record to the camera-default routine at 0x00421480, give its viewport
// block to the render device and publish the index.
//
// Retail reaches the body with the state object in ESI and the index in EBX -
// the only call site (0x00402AEC, the game thread) loads the state's address
// 0x00491C28 into ESI and zeroes EBX - and 0x00421480 reads its record from
// EDI. Those are whole-program register choices, so the body is compiled
// through the native-LTCG cluster
// layout/ltcg/render_stage_select_00405300.json.
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera the default setup rewrites followed by
// the fields that make the record the 0x118 bytes the index stride shows. The
// camera sits at offset 0, so the viewport block the device receives is the
// record's +0xCC.
struct RenderStage_00405300 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide state object at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 and the active index at +0x388.
struct RenderStageState_00405300 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage_00405300 stages[2];              // +0x154, stride 0x118
    RenderStage_00405300* active_stage;          // +0x384
    int stage_index;                             // +0x388

    __declspec(noinline) void SelectDefaultStage(int index);
};

// 0x00421480. Its record arrives in EDI, which no declaration names; the
// cluster's driver carries the ABI anchor for it. The symbol is the maintained
// assembly region, so nothing about it is invented.
extern "C" void __cdecl asm_Camera_ApplyRetail_00421480(RenderCamera* camera);

#pragma code_seg(".text$01select")
void RenderStageState_00405300::SelectDefaultStage(int index) {
    active_stage = &stages[index];
    asm_Camera_ApplyRetail_00421480(&active_stage->camera);
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = index;
}
#pragma code_seg()
