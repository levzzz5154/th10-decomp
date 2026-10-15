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
#include "hud_view.hpp"
#pragma code_seg(".text$004188a0_fn")
void HudGameState::AddLives(int amount) {
    lives += amount;
    if (lives > 9) lives = 9;
    else {
        g_sound_manager.Queue(44,0);
        ResultAnimationHandle* banner = &g_front->secondary;
        banner->Release();
        banner->id = ResultAnimation_CreatePrimary(g_front->captions,75,15);
    }
    g_front->SetActiveCount(g_globals.lives);
}
#pragma code_seg(".text$00413790_fn")
void FrontScoreView::SetActiveCount(int count) {
    int index=0;
    for (;index<count;++index)
        life_icons[index].flags |= 2;
    if (index>=9) return;
    for (;index<9;++index)
        life_icons[index].flags &= ~2u;
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
