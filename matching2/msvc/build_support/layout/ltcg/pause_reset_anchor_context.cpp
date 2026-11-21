#include "../../../src/game/player/player_reset_for_stage.cpp"
#pragma code_seg(".text$05context")
extern "C" int __stdcall PauseResetCompilerContext(PlayerResetView** owners,int count) {
 for (int i=0;i<count;++i) Player_ResetForStage(owners[i]);
 return 0;
}
#pragma code_seg()
