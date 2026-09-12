#include "th10/game/rank_level.hpp"

#include <cstring>

// Rank table (retail 0x00474788, rows of 0x30 32-bit words).
extern uint32_t DAT_00474788[];
// Published current-row pointer (retail 0x00477848).
uint32_t* DAT_00477848;

// 0x004175E0 - Advance the rank level. Retail carries the state in EAX;
// the level word at +0x3C saturates at 7 and the published pointer
// always tracks the (possibly unchanged) level afterwards.
void RankLevel_AdvanceAndPublish(uint8_t* state) {
    int32_t level;
    memcpy(&level, state + 0x3C, sizeof(level));
    if (level < 7) {
        ++level;
        memcpy(state + 0x3C, &level, sizeof(level));
    }
    DAT_00477848 = DAT_00474788 + (size_t)level * 0x30;
}
