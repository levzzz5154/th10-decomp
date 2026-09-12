#include "th10/game/spell_timer.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {


void RegisterClock(RegisteredClock* clock, float* frame_scale) {
	if ((clock->flags & 1u) == 0) {
		clock->clock.frame = 0;
		clock->clock.previous = (int)0xFFF0BDC1u;
		clock->clock.timer = 0.0f;
		clock->clock.control = frame_scale;
		clock->flags |= 1u;
	}
}

// Common retail reset: register, then zero the clock with previous = -1.
void ResetClock(RegisteredClock* clock, float* frame_scale) {
	RegisterClock(clock, frame_scale);
	clock->clock.frame = 0;
	clock->clock.timer = 0.0f;
	clock->clock.previous = -1;
}


} // namespace

// 0x004127A0 - spell-card timer bookkeeping. Phase 1 consumes an entry whose
// start frame has been reached (capture path); phase 2 tracks the countdown
// display and consumes the entry on timeout, decaying the bonus pool.
Word SpellTimer_Update(SpellHost* host, SpellTimerEnv* env) {
	for (unsigned int i = 0; i < 8; ++i) {
		SpellEntry* entry = &host->entries[i];
		if (entry->start_frame >= 0) {
			host->display_remaining = host->main_frame - entry->start_frame;
			if (host->main_frame <= entry->start_frame) {
				host->main_frame = entry->start_frame;
				entry->start_frame = -1;
				ResetClock(&host->clock, env->frame_scale);
				host->flags &= ~0x10000u;
				return entry->capture_bonus;
			}
			break;
		}
	}

	unsigned int slot = 0;
	for (;; ++slot) {
		if (slot >= 8) {
			return 0;
		}
		if (host->entries[slot].start_frame >= 0 &&
		    host->entries[slot].end_frame >= 1) {
			break;
		}
	}
	SpellEntry* entry = &host->entries[slot];

	int seconds = ((entry->end_frame - host->clock.clock.frame) + 0x3B) / 0x3C;
	if (seconds > 99) {
		seconds = 99;
	}
	*env->hud_seconds_display = seconds;

	if (host->clock.clock.frame < entry->end_frame) {
		return 0;
	}

	host->main_frame = entry->start_frame;
	entry->start_frame = -1;
	ResetClock(&host->clock, env->frame_scale);
	host->flags |= 0x10000u;

	*env->bonus_pool -= 3000;
	if (*env->bonus_pool < 5000) {
		*env->bonus_pool = 5000;
	}

	SpellPlayer* player = env->player;
	if ((player->flags & 8u) == 0 && player->invuln_timer > 0x3B) {
		player->charge = 0;
		player->flags &= ~2u;
		for (int i = 0; i < 7; ++i) {
			*player->option_flags[i] &= ~2u;
		}
	}
	return entry->timeout_reward;
}
