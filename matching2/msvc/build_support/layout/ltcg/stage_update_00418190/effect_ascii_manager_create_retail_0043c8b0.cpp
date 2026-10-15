#define g_sprt_ctrl stage_effect_g_sprt_ctrl
#define g_front stage_effect_g_front
#define g_globals stage_effect_data_00474c40
#define g_ascii_manager stage_effect_data_004776e0
#define g_enemy_ctrl stage_effect_g_enemy_ctrl
#define g_player stage_effect_data_00477834
#define g_replay stage_effect_data_00477838
#define g_score stage_effect_data_0047783c
#define g_game_speed stage_effect_data_00476f78
#define g_stage_flags stage_effect_data_00491fc4
#define g_main_state stage_effect_data_00491fb8
#define g_sound_manager stage_effect_data_00492590
#include "th10/core/screen.hpp"

#pragma code_seg(".text$0043c8b0_fn")

// The native closure supplies the draw priority in EBX and the five effect
// parameters on the stack. The inline constructor retains the original
// timer flag access before the complete state wipe.
Screen* __stdcall Screen_Create(
        int priority, int mode, int first, int second, int third, int fourth) {
    Screen* owner = new Screen;
    if (owner) {
        owner->Configure(priority, mode, first, second, third, fourth);
    }
    return owner;
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
