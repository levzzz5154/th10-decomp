#include "th10/source_views/score_bookkeeping_7e27a0_0.hpp"
void ScoreState::AddScore(int amount) {
    score += amount / 10;
    if (score >= 1000000000)
        score = 999999999;
}
