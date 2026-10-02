#include "update_player_dependencies/player_update.cpp"
#include "th10/game/item_scatter_flush.hpp"
#include "th10/game/enemy_death_release_0040e5f0.hpp"
#pragma code_seg(".text$160context")
int __stdcall PlayerUpdateContext(PlayerUpdateState_00405750** players,int count) {
    for(int i=0;i<count;++i) players[i]->Update();
    data_004776f0->ActivateAll(count);
    ((DropSource_0040c9a0*)players[0])->FlushDrops((ItemDrops_0040c9a0*)players[1]);
    Enemy_ReleaseOnDeath_0040e5f0((Enemy_0040e5f0*)players[2]);
    EnemyManager_SweepDeaths_0040e6a0((EnemyManager_0040e5f0*)players[3]);
    data_00477818->ConvertItems();
    return count;
}
#pragma code_seg()
