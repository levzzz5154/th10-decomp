#include "th10/game/score_popup.hpp"

// 0x0042B9C0 - Populate the next entry in the 720-record floating-score ring.
// Retail receives the value and position through registers. The readable ABI
// exposes them explicitly while retaining digit order, minus glyph, lazy timer
// initialization, position/color publication, and ring wrap behavior.
ScorePopupRecord* ScorePopup_Enqueue(ScorePopupQueue* queue, int value,
                                     std::uint32_t color,
                                     const float position[3],
                                     const float* default_speed) {
    if (queue->next_index >= SCORE_POPUP_CAPACITY || queue->next_index < 0) {
        queue->next_index = 0;
    }

    ScorePopupRecord* record = &queue->records[queue->next_index];
    record->active = 1;

    int count = 0;
    if (value < 0) {
        record->digits[0] = 10;
        count = 1;
    } else if (value == 0) {
        record->digits[0] = 0;
        count = 1;
    } else {
        do {
            record->digits[count++] =
                static_cast<std::uint8_t>(value % 10);
            value /= 10;
        } while (value != 0);
    }
    record->digit_count = static_cast<std::uint8_t>(count);
    record->color = color;

    if ((record->timer.flags & 1u) == 0) {
        record->timer.current = 0;
        record->timer.target = static_cast<int>(0xfff0bdc1u);
        record->timer.previous = 0;
        record->timer.speed = default_speed;
        record->timer.flags |= 1u;
    }
    record->timer.current = 0;
    record->timer.previous = 0;
    record->timer.target = -1;

    record->position[0] = position[0];
    record->position[1] = position[1];
    record->position[2] = position[2];

    ++queue->next_index;
    return record;
}
