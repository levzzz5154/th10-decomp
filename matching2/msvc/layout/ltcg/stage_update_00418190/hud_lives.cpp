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
#pragma code_seg(".text$004188a0_fn")
void HudGameState::AddLives(int amount) {
    lives += amount;
    if (lives > 9) lives = 9;
    else {
        data_00492590.Queue(44,0);
        ResultAnimationHandle* banner = &g_front->secondary;
        banner->Release();
        banner->id = ResultAnimation_CreatePrimary(g_front->captions,75,15);
    }
    g_front->SetActiveCount(data_00474c40.lives);
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
