// 0x00402CA0: the stage background's draw task.
//
// Unless the background is hidden it installs the stage camera, draws the two
// background animation buckets (the first with fog), sets the stage's fog
// parameters, draws the four object layers, and steps the fade-out timer.
// It calls the batch flush, the camera apply, the bucket renderer and the
// timer on their whole-program registers, so it is compiled in the cluster
// build_support/layout/ltcg/anm_batch_flush.json.
#include "th10/game/background_draw.hpp"

#pragma code_seg(".text$000pm_stagedraw")
int __stdcall BackGround_Draw(BackGround* stage) {
    if (stage->flags & 8) return 1;
    if (!(stage->flags & 4) || stage->fade_timer.current < 60) {
        g_sprt_ctrl->Flush();
        stage->view.camera.clip_x = g_application.stages[0].camera.clip_x;
        stage->view.camera.clip_y = g_application.stages[0].camera.clip_y;
        g_application.stages[0] = stage->view;
        g_application.SelectStage(0);
        StageSetFog(1);
        StageSetRenderState(0x0E, 0);
        StageSetRenderState(0x17, 8);
        asm_AnimationManager_RenderBucket_00448980(g_sprt_ctrl, 0x11);
        StageSetRenderState(0x17, 4);
        StageSetFog(0);
        asm_AnimationManager_RenderBucket_00448980(g_sprt_ctrl, 0x12);
        StageSetRenderState(0x17, 4);
        StageSetRenderState(0x22, stage->view.fog_color);
        StageSetRenderState(0x24, stage->view.fog_start);
        StageSetRenderState(0x25, stage->view.fog_end);
    }
    if ((stage->flags & 4) && stage->fade_timer.current >= 30) {
        reinterpret_cast<unsigned char*>(&stage->fade_color)[3] = 0;
    }
    if (stage->flags & 1) {
        StageSetRenderState(0x0E, 0);
        StageSetFog(1);
        BackGround_DrawLayer(stage, 8);
        BackGround_DrawLayer(stage, 9);
        BackGround_DrawLayer(stage, 10);
        BackGround_DrawLayer(stage, 11);
        g_sprt_ctrl->Flush();
    }
    SprtCtrlBatchView* manager = g_sprt_ctrl;
    manager->fade_enabled = 0;
    *reinterpret_cast<unsigned int*>(&manager->fade_blue) = 0x80808080;
    if (stage->dimmed) {
        manager->fade_enabled = 1;
        *reinterpret_cast<unsigned int*>(&manager->fade_blue) = 0xFF404040;
    }
    StageSetRenderState(0x0E, 0);
    StageSetRenderState(0x17, 8);
    if (stage->fade_timer.current > 0) {
        stage->fade_timer.Advance(-1.0f);
        if (stage->fade_timer.current <= 0) {
            reinterpret_cast<unsigned char*>(&stage->fade_color)[3] = 0xFF;
            if (stage->flags & 2) stage->flags |= 8;
            stage->fade_color = 0xFFFFFF;
            stage->flags &= ~6u;
        }
    }
    StageSetRenderState(0x0E, 0);
    StageSetRenderState(0x17, 8);
    StageSetFog(0);
    return 1;
}
#pragma code_seg()
