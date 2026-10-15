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
#pragma code_seg(".text$004188a0_fn")
void HudGameState::AddLives(int amount) {
    lives += amount;
    if (lives > 9) lives = 9;
    else {
        data_00492590.Queue(44,0);
        ResultAnimationHandle* banner = &data_0047770c->secondary;
        banner->Release();
        banner->id = ResultAnimation_CreatePrimary(data_0047770c->captions,75,15);
    }
    data_0047770c->SetActiveCount(data_00474c40.lives);
}
#pragma code_seg(".text$00413790_fn")
void ScoreHud_00417040::SetActiveCount(int count) {
    int index=0;
    for (;index<count;++index)
        life_icons[index].flags |= 2;
    if (index>=9) return;
    for (;index<9;++index)
        life_icons[index].flags &= ~2u;
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
