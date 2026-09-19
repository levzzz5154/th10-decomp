// 0x004487C0..0x00448807 (72 bytes): one frame render task - republish the
// second render stage as the active one and draw animation bucket 0x10.
//
// Byte-for-byte the same body as 0x00448770 apart from the bucket index; see
// src/unidentified/FUN_00448770_00448770.cpp for what the body is, why the
// manager arrives in ECX and why it lives in the camera cluster.
#include "th10/render/camera_batch.hpp"

struct RenderStage_004487c0 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

struct RenderStageState_004487c0 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage_004487c0 stages[2];              // +0x154, stride 0x118
    RenderStage_004487c0* active_stage;          // +0x384
    int stage_index;                             // +0x388
};
extern "C" RenderStageState_004487c0 data_00491c28;

extern "C" int __cdecl asm_AnimationManager_RenderBucket_00448980(void* manager, int index);

#pragma code_seg(".text$08stage10")
int AnimationManager_00442F50::RenderStage1Bucket10() {
    RenderStage_004487c0* stage = &data_00491c28.stages[1];
    data_00491c28.active_stage = stage;
    stage->camera.ApplyDefault();
    data_00491c30->Viewport(&data_00491c28.active_stage->camera.viewport_x);
    data_00491c28.stage_index = 1;
    return asm_AnimationManager_RenderBucket_00448980(this, 0x10);
}
#pragma code_seg()
