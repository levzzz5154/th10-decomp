// 0x00402440: GameState destructor. Unregisters the three scheduler tasks,
// frees the stage buffers and the script bank loaded for this state.
#include "th10/game/game_state.hpp"
#include "th10/game/manager_teardown_helpers.hpp"

extern "C" {
extern unsigned char data_00474ca0;
void __cdecl entry_free_00452422(void* memory);
}

#pragma code_seg(".text$02dtor")
GameState_00402230::~GameState_00402230() {
    RemoveSchedulerTask(primary);
    RemoveSchedulerTask(secondary);
    RemoveSchedulerTask(after_draw);
    if (block_0010) {
        entry_free_00452422(block_0010);
        block_0010 = 0;
    }
    if (block_2a44) {
        entry_free_00452422(block_2a44);
        block_2a44 = 0;
    }
    block_2a44 = 0;
    if (block_017c) {
        entry_free_00452422(block_017c);
        block_017c = 0;
    }
    // Each of the two states owns the script bank loaded for it.
    if (!(data_00474ca0 & 1))
        ReleaseAnimationBank(reinterpret_cast<AnimationBanks_00402440*>(data_00491c10),
                             (stage_flags & 1) + 4);
    if (data_004776e8 == this)
        data_004776e8 = 0;
    if (data_004776e4 == this)
        data_004776e4 = 0;
}
#pragma code_seg()
