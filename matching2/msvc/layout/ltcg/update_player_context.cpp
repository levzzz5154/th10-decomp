#include "update_player_dependencies/player_update.cpp"
#pragma code_seg(".text$160context")
int __stdcall PlayerUpdateContext(PlayerUpdateState_00405750** players,int count) {
    for(int i=0;i<count;++i) players[i]->Update();
    return count;
}
#pragma code_seg()
