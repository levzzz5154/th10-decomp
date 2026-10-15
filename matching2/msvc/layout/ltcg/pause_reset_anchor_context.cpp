#include "../../src/game/player/pause_menu_reset.cpp"
#pragma code_seg(".text$05context")
extern "C" int __stdcall PauseResetCompilerContext(PauseState_00424d90** owners,int count) {
 for (int i=0;i<count;++i) ReplayPauseReset_00424d90(owners[i]);
 return 0;
}
#pragma code_seg()
