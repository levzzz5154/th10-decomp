#include "th10/game/score.hpp"

extern float g_score_default_speed;

#pragma code_seg(".text$00409d90_fn")
void ScoreState::AddScore(int amount) {
    score += amount / 10;
    if (score >= 1000000000)
        score = 999999999;
}

#pragma code_seg()
