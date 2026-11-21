#define g_sprt_ctrl stage_hud_g_sprt_ctrl
#define g_front stage_hud_g_front
#define g_globals stage_hud_data_00474c40
#define g_ascii_manager stage_hud_data_004776e0
#define g_enemy_ctrl stage_hud_g_enemy_ctrl
#define g_player stage_hud_data_00477834
#define g_replay stage_hud_data_00477838
#define g_score stage_hud_data_0047783c
#define g_game_speed stage_hud_data_00476f78
#define g_stage_flags stage_hud_data_00491fc4
#define g_main_state stage_hud_data_00491fb8
#define g_sound_manager stage_hud_data_00492590
#include "th10/game/stage_update/hud_view.hpp"
// 0x0043DC90
#define TH10_SOUND_QUEUE_SECTION ".text$0043dc90_fn"
#include "../../../../src/core/sound/sound_queue.cpp"

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
