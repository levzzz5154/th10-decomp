#include "th10/game/large_player_native.hpp"

// The slot, three distinct timers, pickup array, animation array, indicator
// array and final timer construct in declaration order before this body.
#pragma code_seg(".text$a05body")
PlayerResetBlock::PlayerResetBlock() {
    memset(this, 0, sizeof(*this));
    g_player = this;
}
#pragma code_seg()
