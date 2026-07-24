#pragma once

#include "th10/math/timer.hpp"

// Fragment of a score-side timed value record. Retail layout:
//   +0x0C : integer target value stored as one tenth of the input
//   +0x14 : embedded five-word frame timer (target, current, previous,
//           speed pointer, sentinel flags at +0x24)
// The leading words are untouched by the recovered leaves and stay
// reserved.
struct ScoreGaugeTimedValue {
    unsigned int reserved_00[3];  // +0x00..+0x08
    int target_tenth;             // +0x0C
    unsigned int reserved_10;     // +0x10
    EmbeddedTimerState timer;     // +0x14 (retail offsets +0x14..+0x24)
};

// 0x00418B80 - Store value / 10 as the gauge target and disable the
// embedded timer, initializing the retail sentinel on first use.
void ScoreGauge_SetTargetTenthAndDisableTimer(ScoreGaugeTimedValue* state,
                                              int value);

// 0x00418A90 - Advance the score counter word at retail state+0x50 by
// one, clamping the result at 9.
void Score_IncrementCounterClampedNine(int* counter);
