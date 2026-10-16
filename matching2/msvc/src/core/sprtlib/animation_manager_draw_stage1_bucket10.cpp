// 0x004487C0..0x00448807 (72 bytes): one frame render task - republish the
// second render stage as the active one and draw animation bucket 0x10.
//
// Byte-for-byte the same body as 0x00448770 apart from the bucket index; see
// src/core/sprtlib/animation_manager_draw_stage1_bucket0f.cpp for what the body is, why the
// manager arrives in ECX and why it lives in the camera cluster.
#include "th10/render/camera_batch.hpp"

struct RenderStage7 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

struct RenderStageState7 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage7 stages[2];              // +0x154, stride 0x118
    RenderStage7* active_stage;          // +0x384
    int stage_index;                             // +0x388
};
extern "C" RenderStageState7 g_application;

extern "C" int __cdecl asm_AnimationManager_RenderBucket_00448980(void* manager, int index);

#pragma code_seg(".text$08stage10")
int SprtCtrlBatchView::RenderStage1Bucket10() {
    RenderStage7* stage = &g_application.stages[1];
    g_application.active_stage = stage;
    stage->camera.ApplyDefault();
    g_d3d_device->Viewport(&g_application.active_stage->camera.viewport_x);
    g_application.stage_index = 1;
    return asm_AnimationManager_RenderBucket_00448980(this, 0x10);
}
#pragma code_seg()
