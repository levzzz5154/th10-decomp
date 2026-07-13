#pragma once

#include "th10/game/entity.hpp"

// Partial layout for the score/counter object used by 0x0041BE80.
struct ScoreCounter {
    uint32_t field_000[3];
    int32_t value;  // +0x0C, capped at 99,999

    void AddScaled(int32_t amount);
};
