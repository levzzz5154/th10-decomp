#define g_sprt_ctrl stage_hud_g_sprt_ctrl
#define g_front stage_hud_g_front
#define data_00474c40 stage_hud_data_00474c40
#define g_ascii_manager stage_hud_data_004776e0
#define g_enemy_ctrl stage_hud_g_enemy_ctrl
#define g_player stage_hud_data_00477834
#define data_00477838 stage_hud_data_00477838
#define data_0047783c stage_hud_data_0047783c
#define data_00476f78 stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define data_00492590 stage_hud_data_00492590
#include "hud_view.hpp"
#pragma code_seg(".text$00448d00_fn")
ResultAnimationId __stdcall ResultAnimation_CreatePrimary(void* file, int script, int layer) {
    Entity* object = reinterpret_cast<ResultAnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = layer;
    object->flags_35C = flags | 0x40000000;
    reinterpret_cast<ResultAnimationResource*>(file)->InitializeObject(object,script);
    return reinterpret_cast<ResultAnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
