#include "th10/game/score_hud_update.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace {
int g_high[9], g_score[9], g_high_ticks, g_score_ticks;
int g_rank_previous, g_rank_current, g_rank_ticks, g_awards;
void SetHigh(int slot, int script) { g_high[slot] = script; }
void SetScore(int slot, int script) { g_score[slot] = script; }
void TickHigh(int) { ++g_high_ticks; }
void TickScore(int) { ++g_score_ticks; }
void SetRank(bool previous, int script) {
	(previous ? g_rank_previous : g_rank_current) = script;
}
void TickRank(bool) { ++g_rank_ticks; }
int Award(int count) { g_awards += count; return 77; }

ScoreHudEnv MakeEnv(const int* normal, const int* special) {
	ScoreHudEnv env;
	std::memset(&env, 0, sizeof(env));
	env.normal_thresholds = normal;
	env.special_thresholds = special;
	env.set_high_digit = SetHigh;
	env.set_score_digit = SetScore;
	env.tick_high_digit = TickHigh;
	env.tick_score_digit = TickScore;
	env.set_rank_digit = SetRank;
	env.tick_rank_digit = TickRank;
	env.award_extend = Award;
	return env;
}

void TestScoreHudUpdate() {
	int normal[] = {90, 1000, 10000};
	int special[] = {200, 2000, 20000};
	ScoreHudEnv env = MakeEnv(normal, special);
	ScoreHud hud = {};
	hud.displayed_score = 90;
	hud.stage_frame = 20;
	env.target_score = 110;
	env.high_score = 95;
	env.current_rank = 3;
	env.previous_rank = 2;
	g_high_ticks = g_score_ticks = g_rank_ticks = g_awards = 0;
	assert(ScoreHud_Update(&hud, &env) == 77);
	assert(hud.displayed_score == 91); // difference/32 rounds to zero -> minimum 1
	assert(hud.score_velocity == 1);
	assert(env.high_score == 95); // visible score has not passed it yet
	assert(env.threshold_index == 1 && g_awards == 1);
	assert(g_score[0] == 9 && g_score[1] == 17 && g_score[2] == 8);
	assert(g_high[0] == 13 && g_high[1] == 17 && g_high[2] == 8);
	assert(g_high_ticks == 9 && g_score_ticks == 9 && g_rank_ticks == 2);
	assert(g_rank_previous == 10 && g_rank_current == 11);

	// A larger difference grows velocity and publishes a new high score/rank.
	env.target_score = 10000;
	env.high_score = 50;
	env.flags = 0x20; // suppress extend checks for this step
	int old = hud.displayed_score;
	ScoreHud_Update(&hud, &env);
	assert(hud.displayed_score > old && hud.score_velocity > 1);
	assert(env.high_score == hud.displayed_score);
	assert((env.flags & 4u) != 0 && env.previous_rank == env.current_rank);

	// Clamp the last step to the target and clear velocity.
	hud.displayed_score = 9999;
	hud.score_velocity = 500;
	env.target_score = 10000;
	ScoreHud_Update(&hud, &env);
	assert(hud.displayed_score == 10000 && hud.score_velocity == 0);
}

void TestCrossingMarkers() {
	int thresholds[] = {200000000};
	ScoreHudEnv env = MakeEnv(thresholds, thresholds);
	ScoreHud hud = {};
	hud.displayed_score = 99999999;
	hud.score_velocity = 2;
	hud.previous_high_score = 99999999;
	hud.stage_frame = 21;
	env.target_score = 100000001;
	env.high_score = 100000001;
	env.flags = 0x20;
	ScoreHud_Update(&hud, &env);
	assert(hud.displayed_crossing_script == 4);
	assert(hud.high_score_crossing_script == 4);
}
} // namespace

int main() {
	TestScoreHudUpdate();
	TestCrossingMarkers();
	std::puts("BATCH18_TESTS_PASS");
	return 0;
}
