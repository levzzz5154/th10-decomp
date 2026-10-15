#define g_sprt_ctrl stage_requests_g_sprt_ctrl
#define g_front stage_requests_g_front
#define g_globals stage_requests_data_00474c40
#define g_ascii_manager stage_requests_data_004776e0
#define g_enemy_ctrl stage_requests_g_enemy_ctrl
#define g_player stage_requests_data_00477834
#define data_00477838 stage_requests_data_00477838
#define data_0047783c stage_requests_data_0047783c
#define g_game_speed stage_requests_data_00476f78
#define data_00491fc4 stage_requests_data_00491fc4
#define data_00491fb8 stage_requests_data_00491fb8
#define g_sound_manager stage_requests_data_00492590
#include "th10/render/resource_registrar_0043e460.hpp"

#pragma code_seg(".text$0043e460_fn")

char* AnimationManager_0043e460::RegisterResource(const char* name, int resource, int parameter) {
    int index = 0;
    for (; index < 31; ++index) {
        if (records[index].resource == 0) {
            records[index].resource = resource;
            records[index].parameter = parameter;
            char* out = records[index].name;
            const char* text = name;
            while ((*out++ = *text++) != 0) {}
            records[index].state = 0;
            return const_cast<char*>(text);
        }
    }
    return (char*)(long)index;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
