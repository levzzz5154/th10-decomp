#include "th10/game/score_hud.hpp"
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
