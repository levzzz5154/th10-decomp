// 0x00448770..0x004487B7 (72 bytes): one frame render task - republish the
// second render stage as the active one and draw animation bucket 0x0F.
//
// The body is the second-stage selection inlined: it points the render state's
// active stage at the record 0x00491E94 (= 0x00491C28 + 0x154 + 0x118, i.e. the
// second 0x118-byte stage record), reapplies that record's *default* camera,
// hands the record's +0xCC viewport block to the render device, publishes index
// 1 (= 0x00491FB0) and then draws animation bucket 0x0F with the task's owner -
// the animation manager - as the bucket renderer's base.
//
// Retail reaches this body with the manager in ECX: the scheduler dispatches
// every task's +0x08 callback as `node->render(node->owner)`, so ECX is the
// owner the task was registered with, and the callback address lives in the
// task node, which is why the body keeps its declared __thiscall convention and
// the layout roots it. The two callees read their record from EDI (0x00421480)
// and the manager from EDI with the bucket index in EAX (0x00448980); the
// camera member is the recovered model in src/game/mother/camera_setup.cpp and the
// bucket renderer is the compiled ABI anchor below, so the body is compiled in
// the native-LTCG cluster build_support/layout/ltcg/anm_batch_flush_00442f50.json.
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera at offset 0 followed by the fields that
// make the record the 0x118 bytes SelectStage indexes with. The camera sits at
// offset 0, so the viewport block the device receives is the record's +0xCC.
struct RenderStage6 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide render state at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 (= 0x00491FAC) and the active
// index at +0x388 (= 0x00491FB0).
struct RenderStageState6 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage6 stages[2];              // +0x154, stride 0x118
    RenderStage6* active_stage;          // +0x384
    int stage_index;                             // +0x388
};
extern "C" RenderStageState6 g_application;

// 0x00448980 reads its manager from EDI and its bucket index from EAX; the
// declaration only fixes the argument shape, the compiled anchor below supplies
// the registers.
extern "C" int __cdecl asm_AnimationManager_RenderBucket_00448980(void* manager, int index);

#pragma code_seg(".text$08stage0f")
int SprtCtrlBatchView::RenderStage1Bucket0F() {
    RenderStage6* stage = &g_application.stages[1];
    g_application.active_stage = stage;
    stage->camera.ApplyDefault();
    g_d3d_device->Viewport(&g_application.active_stage->camera.viewport_x);
    g_application.stage_index = 1;
    return asm_AnimationManager_RenderBucket_00448980(this, 0x0F);
}
#pragma code_seg()

// The per-object draw 0x00448980 dispatches; an absolute binding, never a
// compiler-visible body in this link.
extern "C" void __cdecl asm_FUN_004451c0_004451c0(unsigned char* object, void* manager);

// 0x00448980's own body, modelled only for its argument shape: it walks one
// animation bucket's list, runs each object's hook and dispatches its draw -
// which keeps the manager live across two calls, the pressure that earns it
// EDI, and reads the bucket index once, which leaves it in EAX, exactly as
// retail enters. These bytes are the cluster's compiled ABI anchor and are
// never selected as recovered code: the image keeps the maintained assembly
// region at 0x00448980 (its two internal call shapes are not modelled, so this
// body is 4 bytes off retail and does not promote that region).
#pragma code_seg(".text$09bucket")
extern "C" __declspec(noinline) int __cdecl asm_AnimationManager_RenderBucket_00448980(
        void* manager, int index) {
    unsigned char* base = (unsigned char*)manager;
    unsigned char* object = *(unsigned char**)(base + 0x72DB00 + index * 0x3AC);
    while (object != 0) {
        if ((*(unsigned int*)(object + 0x35C) & 0x4000000u) == 0) {
            void (*hook)(unsigned char*) = *(void (**)(unsigned char*))(object + 0x39C);
            if (hook != 0) {
                hook(object);
            }
            asm_FUN_004451c0_004451c0(object, manager);
        }
        object = *(unsigned char**)(object + 0x1C);
    }
    return 1;
}
#pragma code_seg()
