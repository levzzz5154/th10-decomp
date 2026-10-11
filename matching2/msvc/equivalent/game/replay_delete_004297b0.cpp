// 0x004297B0, which destroys and frees an opened replay, as the replay save
// screen 0x00433570 calls it: compiler context of that equivalent recovery
// (the maintained form is
// src/game/platform_deleting_destructor_with_release_004297b0.cpp).
#include "th10/game/replay_save_update_00433570.hpp"
#pragma code_seg(".text$004297b0_fn")
void __stdcall ReplayFile_Delete_004297b0(ReplayFile_004315c0* replay) {
    if (replay) {
        ReplayFile_Destroy_004294a0(replay);
        free(replay);
    }
}
#pragma code_seg()
