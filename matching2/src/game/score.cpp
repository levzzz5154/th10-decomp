// 0x0041BE80 - Add one tenth of amount to the counter, saturating at 99,999.
#include "th10/game/score.hpp"

void ScoreCounter::AddScaled(int32_t amount) {
    value += amount / 10;
    if (value > 99999) {
        value = 99999;
    }
}
