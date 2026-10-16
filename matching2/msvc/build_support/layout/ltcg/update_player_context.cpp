#include "update_player_dependencies/player_update.cpp"
#include "th10/game/item_scatter_flush.hpp"
#include "th10/game/enemy_death_release.hpp"
#pragma code_seg(".text$160context")
int __stdcall PlayerUpdateContext(BombState** players,int count) {
    for(int i=0;i<count;++i) players[i]->Update();
    g_bullet_manager->ActivateAll(count);
    ((DropSource*)players[0])->FlushDrops((ItemDrops2*)players[1]);
    Enemy_ReleaseOnDeath((Enemy6*)players[2]);
    EnemyCtrl_SweepDeaths((EnemyCtrlDeathView*)players[3]);
    g_item_manager->ConvertItems();
    return count;
}
#pragma code_seg()
