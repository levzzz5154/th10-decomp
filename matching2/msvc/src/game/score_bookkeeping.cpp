#include "th10/game/score.hpp"

extern float g_score_default_speed;

#pragma code_seg(".text$10addscore")
void ScoreState::AddScore(int amount) {
    score += amount / 10;
    if (score >= 1000000000)
        score = 999999999;
}

#pragma code_seg(".text$30reducegauge")
void ScoreState::ReduceGauge(int amount) {
    gauge += amount / -10;
    if (gauge < 5000)
        gauge = 5000;
}

#pragma code_seg(".text$50increment")
void ScoreState::IncrementCappedCount() {
    ++capped_count;
    if (capped_count >= 10)
        capped_count = 9;
}

#pragma code_seg(".text$70setgauge")
void ScoreState::SetGauge(int amount) {
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

#pragma code_seg(".text$90addgauge")
void ScoreState::AddGauge(int amount) {
    gauge += amount / 10;
    if (gauge > 99999)
        gauge = 99999;
}
#pragma code_seg()
