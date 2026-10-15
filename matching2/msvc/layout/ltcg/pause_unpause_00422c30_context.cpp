// Compiler-only array walker, not selected game code.
#include "../../src/game/pause/pause_unpause.cpp"
#include "animation_lookup_anchors.cpp"
#pragma code_seg(".text$06context")
int __stdcall UnpauseContext_00422c30(PauseOwner_00422c30* owners, int count) {
 for(int i=0;i<count;++i) owners[i].Unpause();
 return count;
}
#pragma code_seg()
