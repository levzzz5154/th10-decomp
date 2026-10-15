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
#include <string.h>
#include "front_view.hpp"

struct AnimationManager_0043e710 {
    unsigned char reserved_00[0x4C];
    int script_tick_counter; // +0x4C
};

extern "C" float g_game_speed;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity *object);
extern "C" void __stdcall LoadScript_0043e710(AnimationResourceFile *resource,
                                              AnimationObjectFile *object, int index);

#pragma code_seg(".text$0043e710_fn")
__declspec(noinline) void __stdcall LoadScript_0043e710(AnimationResourceFile *resource,
                                                        AnimationObjectFile *object,
                                                        int index) {
    void *script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return;
    }
    Entity_Init(script, object); // leading slot is dead in this ABI
    uint32_t mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptIndex() = static_cast<int16_t>(index);
    object->ScriptResourceId() = resource->id;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    void *fresh = resource->scripts[index];
    object->ScriptBase() = fresh;
    object->ScriptCursor() = fresh;
    if ((object->flags_06C & 1) == 0) {
        object->current_frame = 0;
        object->previous_frame = static_cast<int32_t>(0xFFF0BDC1u);
        object->frame_elapsed = 0.0f;
        object->time_scale = &g_game_speed;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    uint32_t *flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++reinterpret_cast<AnimationManager_0043e710 *>(g_sprt_ctrl)->script_tick_counter;
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
