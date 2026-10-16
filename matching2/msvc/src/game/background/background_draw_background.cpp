// 0x00402850: the stage background's first draw task.
//
// Unless the background is hidden it installs the stage camera and fog,
// clears the depth buffer and the playfield, starts the screen effect of a
// fade, draws the flat backdrop sprites and the eight far object layers.
// It calls the batch flush, the camera apply, the stage selectors and the
// timer on their whole-program registers, so it is compiled in the cluster
// build_support/layout/ltcg/anm_batch_flush.json.
#include "th10/game/background_draw.hpp"

// The parts of the render state at 0x00491C28 other units define.
struct RenderStageState2 {
    __declspec(noinline) void SelectDefaultStage(int index);
};
struct RenderStageState4 {
    __declspec(noinline) int DisableFog();
};
// 0x00405410: the out-of-line copy of FrameTimer::Set.
struct PlayerSchedulerRecord {
    __declspec(noinline) void SetSchedulerValue(int value);
};
struct Screen;
__declspec(noinline) Screen* __stdcall Screen_Create(
    int priority, int mode, int first, int second, int third, int fourth);

struct PlayfieldRect { int left, top, right, bottom; };

#pragma code_seg(".text$000pl_stagebg")
int __stdcall BackGround_DrawBackground(BackGround* stage) {
    if (stage->flags & 8) return 1;
    if (!(stage->flags & 4) || stage->fade_timer.current < 60) {
        g_sprt_ctrl->Flush();
        stage->view.camera.clip_x = g_application.stages[0].camera.clip_x;
        stage->view.camera.clip_y = g_application.stages[0].camera.clip_y;
        g_application.stages[0] = stage->view;
        g_application.SelectStage(0);
        StageSetRenderState(0x0E, 1);
        StageSetRenderState(0x17, 4);
        StageSetRenderState(0x22, stage->view.fog_color);
        StageSetRenderState(0x24, stage->view.fog_start);
        StageSetRenderState(0x25, stage->view.fog_end);
        g_d3d_device->Clear(0, 0, 2, 0, 1.0f, 0);
        if ((stage->flags & 4) && stage->clear_timer.current < 34) {
            PlayfieldRect rect = {32, 16, 416, 464};
            g_d3d_device->Clear(1, &rect, 1, 0, 1.0f, 0);
        } else {
            PlayfieldRect rect = {32, 16, 416, 464};
            g_d3d_device->Clear(1, &rect, 1, stage->view.fog_color & 0xFFFFFF, 1.0f, 0);
        }
    }
    if (stage->flags & 4) {
        if (stage->fade_timer.current < 30) {
            Screen_Create(15, 3, 30, 0, 0, 0);
            stage->flags |= 1;
            reinterpret_cast<PlayerSchedulerRecord*>(&stage->fade_timer)->SetSchedulerValue(1);
        } else {
            reinterpret_cast<unsigned char*>(&stage->fade_color)[3] = 0;
            stage->flags &= ~1u;
        }
    }
    if (reinterpret_cast<unsigned char*>(&stage->fade_color)[3] != 0) {
        unsigned int color = stage->fade_color;
        g_sprt_ctrl->fade_enabled = 1;
        *reinterpret_cast<unsigned int*>(&g_sprt_ctrl->fade_blue) = color;
    }
    stage->drawn_objects = 0;
    stage->culled_objects = 0;
    stage->drawn_quads = 0;
    if (stage->flags & 1) {
        if (stage->sprites[0].texture) {
            reinterpret_cast<RenderStageState2*>(&g_application)->SelectDefaultStage(0);
            reinterpret_cast<RenderStageState4*>(&g_application)->DisableFog();
            g_sprt_ctrl->Flush();
            StageSetRenderState(0x0E, 0);
            for (int i = 0; i < 8; ++i) {
                if (stage->sprites[i].texture) {
                    asm_FUN_004451c0_004451c0(g_sprt_ctrl, &stage->sprites[i]);
                }
            }
            StageSetRenderState(0x0E, 1);
            g_application.SelectStage(0);
        }
        StageSetFog(1);
        BackGround_DrawLayer(stage, 0);
        BackGround_DrawLayer(stage, 1);
        BackGround_DrawLayer(stage, 2);
        BackGround_DrawLayer(stage, 3);
        BackGround_DrawLayer(stage, 4);
        BackGround_DrawLayer(stage, 5);
        BackGround_DrawLayer(stage, 6);
        BackGround_DrawLayer(stage, 7);
        g_sprt_ctrl->Flush();
        if (stage->sprite_frames) ++stage->sprite_frames;
    }
    g_sprt_ctrl->fade_enabled = 0;
    *reinterpret_cast<unsigned int*>(&g_sprt_ctrl->fade_blue) = 0x80808080;
    if (stage->dimmed) {
        g_sprt_ctrl->fade_enabled = 1;
        *reinterpret_cast<unsigned int*>(&g_sprt_ctrl->fade_blue) = 0xFF404040;
    }
    StageSetRenderState(0x0E, 0);
    StageSetRenderState(0x17, 8);
    return 1;
}
#pragma code_seg()
