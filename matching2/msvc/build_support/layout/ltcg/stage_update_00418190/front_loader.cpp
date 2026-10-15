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
#include "th10/game/entity.hpp"
struct AnimationObject_0043e7e0 : Entity {};
struct AnimationResource_0043e7e0 {
    unsigned short id;
    unsigned char reserved_002[0x11A];
    void **scripts;
    unsigned char reserved_120[4];
    int loading;
};
struct AnimationManager_0043e7e0 {
    unsigned char reserved[0x4C];
    int script_tick_counter;
};
struct FrontAnimationLookup;
extern "C" FrontAnimationLookup *g_sprt_ctrl;
extern "C" float g_game_speed;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity *object);
#pragma code_seg(".text$0043e7e0_fn")
__declspec(noinline) void *__stdcall
InitializePreservingLoader_0043e7e0(AnimationResource_0043e7e0 *resource,
                                    AnimationObject_0043e7e0 *object, int index) {
    void *script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return 0;
    }
    object->ScriptIndex() = (short)index;
    object->ScriptResourceId() = resource->id;
    unsigned int mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    void *fresh = resource->scripts[index];
    object->ScriptBase() = fresh;
    object->ScriptCursor() = fresh;
    if ((object->flags_06C & 1) == 0) {
        object->current_frame = 0;
        object->previous_frame = (int)0xFFF0BDC1u;
        object->frame_elapsed = 0.0f;
        object->time_scale = &g_game_speed;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    unsigned int *flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    AnimationManager_0043e7e0 *manager = (AnimationManager_0043e7e0 *)g_sprt_ctrl;
    ++manager->script_tick_counter;
    return manager;
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
