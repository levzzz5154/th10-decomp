#include "th10/game/score_hud_00417040.hpp"
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
