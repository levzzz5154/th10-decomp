#pragma once

#include <cstdint>

#include "th10/math/timer.hpp"

enum { SCORE_POPUP_CAPACITY = 720, SCORE_POPUP_DIGIT_CAPACITY = 12 };

struct ScorePopupRecord {
    std::uint8_t digits[SCORE_POPUP_DIGIT_CAPACITY];
    float position[3];
    std::uint32_t color;
    EmbeddedTimerState timer;
    std::uint8_t active;
    std::uint8_t digit_count;
};

struct ScorePopupQueue {
    int next_index;
    ScorePopupRecord records[SCORE_POPUP_CAPACITY];
};

// Queue a colored integer at a world position. Decimal digits are stored
// least-significant first, as consumed by the retail renderer; 10 is the
// dedicated minus-sign glyph.
ScorePopupRecord* ScorePopup_Enqueue(ScorePopupQueue* queue, int value,
                                     std::uint32_t color,
                                     const float position[3],
                                     const float* default_speed);
