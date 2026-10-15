#define data_00491c10 stage_hud_data_00491c10
#define data_0047770c stage_hud_data_0047770c
#define data_00474c40 stage_hud_data_00474c40
#define g_ascii_manager stage_hud_data_004776e0
#define data_00477704 stage_hud_data_00477704
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
    Entity* object = reinterpret_cast<ResultAnimationPool*>(data_00491c10)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = layer;
    object->flags_35C = flags | 0x40000000;
    reinterpret_cast<ResultAnimationResource*>(file)->InitializeObject(object,script);
    return reinterpret_cast<ResultAnimationLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
