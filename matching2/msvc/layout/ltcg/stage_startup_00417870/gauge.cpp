// Compiler context only: the body of 0x00418B80 (recovered as
// ScoreState::SetGauge in src/game/score_bookkeeping.cpp) on this cluster's
// view of the game state. These bytes are not selected.
#include "th10/game/stage_startup_00417870.hpp"

#pragma code_seg(".text$00418b80_fn")
void StageRunState_00417870::SetGauge(int amount) {
    gauge = amount / 10;
    if (!(gauge_timer.flags & 1)) {
        gauge_timer.current = 0;
        gauge_timer.previous = -999999;
        gauge_timer.elapsed = 0;
        gauge_timer.speed = &g_score_default_speed;
        gauge_timer.flags |= 1;
    }
    gauge_timer.current = 0;
    gauge_timer.elapsed = 0;
    gauge_timer.previous = -1;
}
#pragma code_seg()
