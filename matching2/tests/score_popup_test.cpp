#include "th10/game/score_popup.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>

static void TestPositiveAndTimerInitialization() {
    ScorePopupQueue queue;
    std::memset(&queue, 0, sizeof(queue));
    const float position[3] = {12.5f, -4.0f, 9.25f};
    const float speed = 1.0f;

    ScorePopupRecord* record = ScorePopup_Enqueue(
        &queue, 12034, 0xff40a0ffu, position, &speed);
    assert(record == &queue.records[0]);
    assert(queue.next_index == 1 && record->active == 1);
    assert(record->digit_count == 5);
    assert(record->digits[0] == 4 && record->digits[1] == 3);
    assert(record->digits[2] == 0 && record->digits[3] == 2);
    assert(record->digits[4] == 1);
    assert(record->position[0] == 12.5f);
    assert(record->position[1] == -4.0f);
    assert(record->position[2] == 9.25f);
    assert(record->color == 0xff40a0ffu);
    assert(record->timer.target == -1);
    assert(record->timer.current == 0 && record->timer.previous == 0);
    assert(record->timer.speed == &speed);
    assert((record->timer.flags & 1u) != 0);
}

static void TestZeroMinusAndWrap() {
    ScorePopupQueue queue;
    std::memset(&queue, 0, sizeof(queue));
    const float position[3] = {0, 0, 0};
    const float speed = 1.0f;

    ScorePopupRecord* zero = ScorePopup_Enqueue(
        &queue, 0, 0xffffffffu, position, &speed);
    assert(zero->digit_count == 1 && zero->digits[0] == 0);

    ScorePopupRecord* negative = ScorePopup_Enqueue(
        &queue, -9876, 0xffff4040u, position, &speed);
    assert(negative->digit_count == 1 && negative->digits[0] == 10);

    queue.next_index = SCORE_POPUP_CAPACITY;
    ScorePopupRecord* wrapped = ScorePopup_Enqueue(
        &queue, 7, 0xff00ff00u, position, &speed);
    assert(wrapped == &queue.records[0]);
    assert(queue.next_index == 1);
    assert(wrapped->digit_count == 1 && wrapped->digits[0] == 7);
}

static void TestInitializedTimerKeepsSpeedPointer() {
    ScorePopupQueue queue;
    std::memset(&queue, 0, sizeof(queue));
    const float original_speed = 0.5f;
    const float replacement_speed = 2.0f;
    const float position[3] = {1, 2, 3};
    queue.records[0].timer.flags = 1;
    queue.records[0].timer.speed = &original_speed;
    queue.records[0].timer.target = 42;
    queue.records[0].timer.current = 12;
    queue.records[0].timer.previous = 11;

    ScorePopupRecord* record = ScorePopup_Enqueue(
        &queue, 9, 0, position, &replacement_speed);
    assert(record->timer.speed == &original_speed);
    assert(record->timer.target == -1);
    assert(record->timer.current == 0 && record->timer.previous == 0);
}

int main() {
    TestPositiveAndTimerInitialization();
    TestZeroMinusAndWrap();
    TestInitializedTimerKeepsSpeedPointer();
    return 0;
}
