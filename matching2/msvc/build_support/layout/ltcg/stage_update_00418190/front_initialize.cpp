#define g_sprt_ctrl stage_front_g_sprt_ctrl
#define g_front stage_front_g_front
#define g_globals stage_front_data_00474c40
#define g_ascii_manager stage_front_data_004776e0
#define g_enemy_ctrl stage_front_g_enemy_ctrl
#define g_player stage_front_data_00477834
#define g_replay stage_front_data_00477838
#define g_score stage_front_data_0047783c
#define g_game_speed stage_front_data_00476f78
#define g_stage_flags stage_front_data_00491fc4
#define g_main_state stage_front_data_00491fb8
#define g_sound_manager stage_front_data_00492590
// 0x00449870: reset animation vectors and start a script while preserving object state.
#include "th10/game/entity_script_start.hpp"
#include "front_view.hpp"
struct AnimationObject_0043e7e0;
struct AnimationResource_0043e7e0;
__declspec(noinline) void *__stdcall
InitializePreservingLoader_0043e7e0(AnimationResource_0043e7e0 *resource,
                                    AnimationObject_0043e7e0 *object, int index);
struct AnimationFlagValue {
    unsigned int value;
    AnimationFlagValue(unsigned int bits) : value(bits) {}
    AnimationFlagValue operator|(unsigned int bits) const {
        return AnimationFlagValue(value | bits);
    }
};

#pragma code_seg(".text$00449870_fn")
void FrontAnimationResource::InitializeObject(Entity *object, int index) {
    AnimationFlagValue flags = *reinterpret_cast<AnimationFlagValue *>(&object->AnimationFlags());
    object->Position() = Vector3Value(0.0f, 0.0f, 0.0f);
    object->BasePosition() = Vector3Value(0.0f, 0.0f, 0.0f);
    object->AnimationFlags() = (flags | 0x40000000u).value;
    object->ScriptIndex() = static_cast<short>(index);
    object->RenderOffset() = Vector3Value(0.0f, 0.0f, 0.0f);
    EntityTail(object)->layer_3a1 = 0x10;
    EntityTail(object)->layer_3a0 = 0x10;
    InitializePreservingLoader_0043e7e0((AnimationResource_0043e7e0 *)this,
                                        (AnimationObject_0043e7e0 *)object, index);
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
