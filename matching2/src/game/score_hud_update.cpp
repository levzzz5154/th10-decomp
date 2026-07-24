#include "th10/game/score_hud_update.hpp"

namespace {
int SmoothStep(int difference) {
	int step = difference / 32;
	if (step == 0) step = 1;
	if (step > 0x8D55E) step = 0x8D55E;
	return step;
}
}

// 0x00417040 - eases the visible score toward the live score, updates the
// high-score/rank snapshot, writes nine least-significant-first digit VMs,
// and awards the next score extend when its threshold is crossed.
int ScoreHud_Update(ScoreHud* hud, ScoreHudEnv* env) {
	const int old_displayed = hud->displayed_score;
	int displayed = old_displayed;
	if (env->target_score != displayed) {
		const int candidate = SmoothStep(env->target_score - displayed);
		if (hud->score_velocity < candidate) hud->score_velocity = candidate;
		const int remaining = env->target_score - displayed;
		if (remaining < hud->score_velocity) hud->score_velocity = remaining;
		displayed += hud->score_velocity;
		hud->displayed_score = displayed;
		if (env->target_score <= displayed) hud->score_velocity = 0;
		if (displayed > 99999999 && old_displayed < 100000000)
			hud->displayed_crossing_script = 4;
	}

	if (env->high_score < displayed) {
		env->flags |= 4u;
		env->previous_rank = env->current_rank;
		env->high_score = displayed;
	}
	if (hud->stage_frame > 19) {
		if (env->high_score > 99999999 && hud->previous_high_score < 100000000)
			hud->high_score_crossing_script = 4;
		hud->previous_high_score = env->high_score;
	}

	int high = env->high_score;
	int score = displayed;
	for (int slot = 0; slot < 9; ++slot) {
		env->set_high_digit(slot, high == 0 ? 8 : high % 10 + 8);
		if (high != 0) high /= 10;
		env->set_score_digit(slot, score == 0 ? 8 : score % 10 + 8);
		if (score != 0) score /= 10;
		env->tick_high_digit(slot);
		env->tick_score_digit(slot);
	}
	env->set_rank_digit(true, env->previous_rank + 8);
	env->set_rank_digit(false, env->current_rank + 8);
	env->tick_rank_digit(true);
	env->tick_rank_digit(false);

	int result = env->threshold_index;
	if ((env->flags & 0x20u) == 0) {
		const int* thresholds = env->game_mode == 4
		                            ? env->special_thresholds
		                            : env->normal_thresholds;
		if (displayed >= thresholds[env->threshold_index]) {
			result = env->award_extend(1);
			env->threshold_index += 1;
		}
	}
	return result;
}
