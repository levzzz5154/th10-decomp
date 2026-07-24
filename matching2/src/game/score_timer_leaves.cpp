#include "th10/game/score_timer_leaves.hpp"

extern float DAT_00476f78;  // default timer speed sentinel (1.0f)

// 0x00418B80 - Store one tenth of the incoming value as the gauge target
// at +0x0C and disable the embedded timer at +0x14. The five-word timer
// sentinel follows the shared retail pattern (see EmbeddedTimer_Reset at
// 0x004050D0 and GameState_DisableTimerWithOwner at 0x0042C5C0): on first
// use the target is seeded with -999999, the speed pointer is wired to
// the global default at DAT_00476f78, and the initialized bit is set;
// every call then clears current/previous and parks the target at -1.
void ScoreGauge_SetTargetTenthAndDisableTimer(ScoreGaugeTimedValue* state,
                                              int value) {
    state->target_tenth = value / 10;
    EmbeddedTimerState* timer = &state->timer;
    if ((timer->flags & 1u) == 0) {
        timer->current = 0;
        timer->target = (int)0xFFF0BDC1;  // -999999 first-use sentinel
        timer->previous = 0;
        timer->speed = &DAT_00476f78;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->previous = 0;
    timer->target = -1;
}

// 0x00418A90 - Increment the score counter word (retail state+0x50) and
// clamp the result at 9.
void Score_IncrementCounterClampedNine(int* counter) {
    const int advanced = *counter + 1;
    *counter = advanced;
    if (advanced > 9) {
        *counter = 9;
    }
}
