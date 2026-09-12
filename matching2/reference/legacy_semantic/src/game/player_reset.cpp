#include "th10/game/player_reset.hpp"

#include <cstring>

// Published player block (retail 0x00477834).
uint32_t* DAT_00477834;

// 0x004246C0 - Reset the player block and publish it. Retail clears
// dozens of embedded timer flags and sub-records first, but the final
// full-block wipe (0x111E words from the base) makes every one of those
// stores dead; only the wipe and the publish through 0x00477834 are
// observable. Retail returns the state pointer (a1 in eax).
uint32_t* Player_ResetAndPublish(uint32_t* state) {
    memset(state, 0, kPlayerBlockDwords * sizeof(uint32_t));
    DAT_00477834 = state;
    return state;
}
