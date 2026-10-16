// 0x00420000 (177 bytes): the application's draw task. Forget the animation
// manager's cached render state, select and apply the second render stage's
// camera, and clear the depth buffer.
//
// The task receives the application state (0x00491C28) in ECX and calls
// RenderCamera::Apply with the camera in EDI, so the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/anm_batch_flush.json.
#include "th10/render/camera_batch.hpp"

struct RenderStage3 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

struct RenderStageState3 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage3 stages[2];              // +0x154, stride 0x118
    RenderStage3* active_stage;          // +0x384
    int stage_index;                             // +0x388
    unsigned char reserved_38C[0x780 - 0x38C];
    unsigned int clear_color;                    // +0x780

    __declspec(noinline) int BeginFrame();
};

// The one application state object; g_d3d_device and g_main_clear_color are its
// device and clear colour.
extern "C" RenderStageState3 g_application;

// The manager's fade colour is four byte channels written as one word here.
inline unsigned int& ManagerFadeColor(SprtCtrlBatchView* manager) {
    return *reinterpret_cast<unsigned int*>(&manager->fade_blue);
}

// The first word after the cached state block (+0x3ADA70).
inline int& ManagerCachedTail(SprtCtrlBatchView* manager) {
    return *reinterpret_cast<int*>(manager->unknown5);
}

#pragma code_seg(".text$001z3gapa0frame")
int RenderStageState3::BeginFrame() {
    SprtCtrlBatchView* manager = g_sprt_ctrl;
    ManagerCachedTail(manager) = 0;
    manager->cached_texture = 0;
    manager->cached_unknown_69 = 0xff;
    manager->cached_blend = 3;
    manager->cached_unknown_6b = 0xff;
    manager->cached_unknown_6c = 0xff;
    manager->fade_enabled = 0;
    ManagerFadeColor(manager) = 0x80808080;
    manager->cached_filter = 0xff;
    manager->origin_y = 0.0f;
    manager->origin_x = 0.0f;
    manager->cached_format = 0xff;
    active_stage = &stages[1];
    active_stage->camera.Apply();
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = 1;
    g_application.device->Clear(0, 0, 1, g_application.clear_color, 1.0f, 0);
    return 1;
}
#pragma code_seg()
