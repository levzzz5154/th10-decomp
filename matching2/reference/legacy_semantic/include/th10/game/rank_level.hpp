#pragma once

#include <cstdint>

// 0x004175E0 - Advance the rank level at state+0x3C (clamped at 7) and
// re-publish the current rank-table row pointer through the retail
// global at 0x00477848 (rows are 0x30 words apart in the table at
// 0x00474788, matching the raw pseudocode's pointer arithmetic).
void RankLevel_AdvanceAndPublish(uint8_t* state);
