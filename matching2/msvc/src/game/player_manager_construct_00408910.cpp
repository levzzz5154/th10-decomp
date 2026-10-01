// 0x00408910: construct the player manager. The three sprite pools and the
// frame timer are built as members, then the whole block is cleared, marked
// and published. The compiler-generated cleanups at 0x004654E0 and
// 0x004654F9 destroy the pools already built if a later one throws.
#include "th10/game/player_manager_construct_00408910.hpp"

#pragma code_seg(".text$01construct")
PlayerManager_00408910::PlayerManager_00408910() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    data_004776f4 = this;
}
#pragma code_seg()
