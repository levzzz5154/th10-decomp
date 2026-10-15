#include "th10/source_views/score_bookkeeping_7e27a0_0.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_1.hpp"
void ScoreState::ReduceGauge(int amount) {
    gauge += amount / -10;
    if (gauge < 5000)
        gauge = 5000;
}
