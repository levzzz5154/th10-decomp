// 0x00448620..0x00448692 (115 bytes): one frame render task - republish the
// first render stage as the active one and draw animation bucket 3.
//
// The body is the first-stage selection inlined: it points the render state's
// active stage at the record 0x00491D7C (= 0x00491C28 + 0x154, the first
// 0x118-byte stage record), reapplies that record's *default* camera, hands the
// record's +0xCC viewport block to the render device, publishes stage index 0
// and then draws animation bucket 3 with the task's owner - the animation
// manager - as the bucket renderer's base.  Unlike the second-stage tasks
// 0x00448770/0x004487C0/0x00448810 it also consumes the pending-fog flag at
// +0x750: while that flag is set it flushes the quad batch, clears the flag and
// turns D3DRS_FOGENABLE (28) off before drawing.  The frame code writes 0xFF
// there when it invalidates the fog state (0x00439390 does), so the pair is a
// "fog state is dirty, restore it" handshake.
//
// Retail reaches this body with the manager in ECX: the scheduler dispatches
// every task's +0x08 callback as `node->render(node->owner)`, so ECX is the
// owner the task was registered with.  The body keeps its declared __thiscall
// convention (which is why the layout roots it), keeps the owner in EBX across
// the two mid-body calls and hands it to the bucket renderer 0x00448980 in EDI
// while the bucket index travels in EAX.  The camera member is the recovered
// model in src/game/mother/camera_setup.cpp and the bucket renderer is the cluster's
// compiled ABI anchor, so this body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/anm_batch_flush_00442f50.json.
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera at offset 0 followed by the fields that
// make the record the 0x118 bytes SelectStage indexes with. The camera sits at
// offset 0, so the viewport block the device receives is the record's +0xCC.
struct RenderStage5 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide render state at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 (= 0x00491FAC), the active index
// at +0x388 (= 0x00491FB0) and the pending-fog flag at +0x750 (= 0x00492378).
// Reading the flag and the index through the modelled state - not through bare
// global declarations - is a measured code-generation lever: it is what makes
// the backend keep the flush block's store, its argument pushes and the device
// vtable load in retail's order.
struct RenderStageState5 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage5 stages[2];              // +0x154, stride 0x118
    RenderStage5* active_stage;          // +0x384
    int stage_index;                             // +0x388
    unsigned char reserved_38C[0x750 - 0x38C];
    int fog_dirty;                               // +0x750
};
extern "C" RenderStageState5 g_application;

// 0x00448980 reads its manager from EDI and its bucket index from EAX; the
// declaration only fixes the argument shape, the cluster anchor supplies the
// registers.
extern "C" int __cdecl asm_AnimationManager_RenderBucket_00448980(void* manager, int index);

#pragma code_seg(".text$08layer3")
int SprtCtrlBatchView::RenderStage0Bucket3() {
    RenderStage5* stage = &g_application.stages[0];
    g_application.active_stage = stage;
    stage->camera.ApplyDefault();
    g_d3d_device->Viewport(&g_application.active_stage->camera.viewport_x);
    g_application.stage_index = 0;
    if (g_application.fog_dirty) {
        g_sprt_ctrl->Flush();
        g_application.fog_dirty = 0;
        g_d3d_device->State(0x1C, 0);
    }
    return asm_AnimationManager_RenderBucket_00448980(this, 3);
}
#pragma code_seg()
