#include "th10/source_views/fun_a1dd06_0.hpp"
int GameFrameAdvance(GameFrame* frame) {
    frame->frame_time = FrameTimer_GetDelta();
    if (frame->frame_time < frame->previous_time) frame->next_tick_time = frame->frame_time;
    frame->previous_time = frame->frame_time;
    if (frame->frame_time > frame->next_tick_time) {
        while (frame->next_tick_time < frame->frame_time) frame->next_tick_time += 1.0 / 60.0;
        g_sprt_ctrl->Flush();
        RenderStage_00439390* stage = &g_application.stages[1];
        g_application.active_stage = stage;
        stage->camera.ApplyDefault();
        g_d3d_device->Viewport(&g_application.active_stage->camera.viewport_x);
        g_application.stage_index = 1;
        int task = asm_FUN_00449c00_00449c00(g_func_ctrl);
        asm_FUN_0043ddf0_0043ddf0(g_sound_manager);
        if (task == 0) {
            g_frame_worker.Stop();
            return 1;
        }
        if (task == -1) {
            g_frame_worker.Stop();
            return 2;
        }
        const unsigned char& limit = g_frame_limit;
        ++frame->tick;
        if (limit + 1 <= frame->tick) {
            typedef long (__stdcall *BeginScene_00439390)(void*);
            RenderDevice* device = g_d3d_device;
            ((BeginScene_00439390)device->vtable[0xA4 / 4])(device);
            SprtCtrlBatchView* manager = g_sprt_ctrl;
            TexturedVertex* buffer = (TexturedVertex*)((unsigned char*)manager + 0x3ADACC);
            manager->quad_count = 0;
            manager->cursor = buffer;
            manager->batch_start = buffer;
            g_application.fog_enabled = 0xFF;
            g_application.DisableFog();
            asm_FUN_00449d40_00449d40(g_func_ctrl);
            g_sprt_ctrl->Flush();
            g_d3d_device->Texture(0, 0);
            typedef long (__stdcall *EndScene_00439390)(void*);
            device = g_d3d_device;
            ((EndScene_00439390)device->vtable[0xA8 / 4])(device);
            frame->tick = 0;
            asm_FUN_004391f0_004391f0();
        }
        g_frame_leftover_time = FrameTimer_GetDelta() - frame->frame_time;
    } else {
        imp_Sleep(0);
    }
    return 0;
}
