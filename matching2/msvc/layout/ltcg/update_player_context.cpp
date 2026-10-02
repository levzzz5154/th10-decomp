#include "update_player_dependencies/player_update.cpp"
#include "th10/game/item_scatter_flush.hpp"
#pragma code_seg(".text$160context")
int __stdcall PlayerUpdateContext(PlayerUpdateState_00405750** players,int count) {
    for(int i=0;i<count;++i) players[i]->Update();
    data_004776f0->ActivateAll(count);
    ((DropSource_0040c9a0*)players[0])->FlushDrops((ItemDrops_0040c9a0*)players[1]);
    return count;
}
#pragma code_seg()
