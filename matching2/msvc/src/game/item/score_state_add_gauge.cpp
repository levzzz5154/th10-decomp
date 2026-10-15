#include "th10/source_views/score_bookkeeping_7e27a0_0.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_1.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_2.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_3.hpp"
#include "th10/source_views/score_bookkeeping_7e27a0_4.hpp"
void ScoreState::AddGauge(int amount) {
    gauge += amount / 10;
    if (gauge > 99999)
        gauge = 99999;
}
