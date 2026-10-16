// 0x004297B0, which destroys and frees an opened replay, as the replay save
// screen 0x00433570 calls it: compiler context of that equivalent recovery
// (the maintained form is
// src/game/replay/platform_deleting_destructor_with_release.cpp).
#include "th10/game/replay_save_update.hpp"
#pragma code_seg(".text$004297b0_fn")
void __stdcall ReplayFile_Delete(ReplayFile* replay) {
    if (replay) {
        ReplayFile_Destroy(replay);
        free(replay);
    }
}
#pragma code_seg()
