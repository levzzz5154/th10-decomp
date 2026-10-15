#define g_sprt_ctrl stage_front_g_sprt_ctrl
#define g_front stage_front_g_front
#define g_globals stage_front_data
#define g_ascii_manager stage_front_data_004776e0
#define g_enemy_ctrl stage_front_g_enemy_ctrl
#define g_player stage_front_data_00477834
#define g_replay stage_front_data_00477838
#define g_score stage_front_data_0047783c
#define g_game_speed stage_front_data_00476f78
#define g_stage_flags stage_front_data_00491fc4
#define g_main_state stage_front_data_00491fb8
#define g_sound_manager stage_front_data_00492590
// 0x0043E5A0 (356 bytes): configure one animation object from an archive
// resource record.

#include "th10/render/animation_object_0043e5a0.hpp"

#pragma code_seg(".text$0043e5a0_fn")
__declspec(noinline) int Resource_0043e5a0::ConfigureObject(AnimationObject_0043e5a0 *object,
                                                            int index) {
    unsigned char *res = reinterpret_cast<unsigned char *>(this);
    if (*reinterpret_cast<void **>(res + 0x108) == 0 ||
        *reinterpret_cast<unsigned int *>(res + 0x124) != 0)
        return -1;

    object->record_index = static_cast<unsigned short>(index);
    object->resource = this;
    object->record = *reinterpret_cast<unsigned char **>(res + 0x118) + index * 0x44;
    object->width = *reinterpret_cast<float *>(object->record + 0x34);
    object->height = *reinterpret_cast<float *>(object->record + 0x30);
    object->block_a.SetIdentity();
    object->block_b.SetIdentity();
    unsigned char *rec = object->record;
    object->block_a.values[0][0] = object->width * 0.00390625f;
    object->block_a.values[1][1] = object->height * 0.00390625f;
    object->block_b.values[0][0] =
        (*reinterpret_cast<float *>(rec + 0x38) / *reinterpret_cast<float *>(rec + 0x1C)) *
        object->width;
    object->block_b.values[1][1] =
        (*reinterpret_cast<float *>(rec + 0x3C) / *reinterpret_cast<float *>(rec + 0x18)) *
        object->height;
    object->block_copy = object->block_a;
    return 0;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
