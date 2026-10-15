#include "th10/source_views/fun_a1dd06_0.hpp"
int GameFrameAdvance_00439390(GameFrame_00439390* frame) {
    frame->frame_time = FrameTimer_GetDelta();
    if (frame->frame_time < frame->previous_time) frame->next_tick_time = frame->frame_time;
    frame->previous_time = frame->frame_time;
    if (frame->frame_time > frame->next_tick_time) {
        while (frame->next_tick_time < frame->frame_time) frame->next_tick_time += 1.0 / 60.0;
        g_sprt_ctrl->Flush();
        RenderStage_00439390* stage = &data_00491c28.stages[1];
        data_00491c28.active_stage = stage;
        stage->camera.ApplyDefault();
        data_00491c30->Viewport(&data_00491c28.active_stage->camera.viewport_x);
        data_00491c28.stage_index = 1;
        int task = asm_FUN_00449c00_00449c00(g_func_ctrl);
        asm_FUN_0043ddf0_0043ddf0(data_00492590);
        if (task == 0) {
            data_00492254.Stop();
            return 1;
        }
        if (task == -1) {
            data_00492254.Stop();
            return 2;
        }
        const unsigned char& limit = data_00491d66;
        ++frame->tick;
        if (limit + 1 <= frame->tick) {
            typedef long (__stdcall *BeginScene_00439390)(void*);
            RenderDevice* device = data_00491c30;
            ((BeginScene_00439390)device->vtable[0xA4 / 4])(device);
            SprtCtrlBatchView* manager = g_sprt_ctrl;
            TexturedVertex* buffer = (TexturedVertex*)((unsigned char*)manager + 0x3ADACC);
            manager->quad_count = 0;
            manager->cursor = buffer;
            manager->batch_start = buffer;
            data_00491c28.fog_enabled = 0xFF;
            data_00491c28.DisableFog();
            asm_FUN_00449d40_00449d40(g_func_ctrl);
            g_sprt_ctrl->Flush();
            data_00491c30->Texture(0, 0);
            typedef long (__stdcall *EndScene_00439390)(void*);
            device = data_00491c30;
            ((EndScene_00439390)device->vtable[0xA8 / 4])(device);
            frame->tick = 0;
            asm_FUN_004391f0_004391f0();
        }
        data_004923a0 = FrameTimer_GetDelta() - frame->frame_time;
    } else {
        data_004660ac(0);
    }
    return 0;
}
