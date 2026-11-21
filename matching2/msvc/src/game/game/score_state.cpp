// 0x00418A90..0x00418B80: ScoreState::IncrementContinues, ScoreState::SetGauge
#include "th10/source_views/score_bookkeeping_7e27a0_0.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_1.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_2.hpp"
void ScoreState::IncrementContinues() {
    ++continues;
    if (continues >= 10)
        continues = 9;
}


#include "../../../include/th10/source_views/score_bookkeeping_7e27a0_3.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_0.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_1.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_2.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_3.hpp"
void ScoreState::SetGauge(int amount) {
    gauge = amount / 10;
    if (!(gauge_timer.flags & 1)) {
        gauge_timer.current = 0;
        gauge_timer.previous = -999999;
        gauge_timer.elapsed = 0;
        gauge_timer.speed = &g_game_speed;
        gauge_timer.flags |= 1;
    }
    gauge_timer.current = 0;
    gauge_timer.elapsed = 0;
    gauge_timer.previous = -1;
}

