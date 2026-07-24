#pragma once

// Spell timer update with bonus decay (retail 0x004127A0).
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

struct SpellEntry {
	int start_frame; // -1 once consumed
	int end_frame;
	Word capture_bonus;
	Word timeout_reward;
};

struct SpellHost {
	int main_frame;
	int display_remaining;
	RegisteredClock clock;
	Word flags; // bit 0x10000: timeout phase
	SpellEntry entries[8];
};

struct SpellPlayer {
	Word flags;   // bit 3 checked, bit 1 cleared
	int invuln_timer;    // must exceed 0x3b to clear option flags
	int charge;          // zeroed on timeout
	Word* option_flags[7];
};

struct SpellTimerEnv {
	int* hud_seconds_display;
	int* bonus_pool; // decays by 3000, floored at 5000
	SpellPlayer* player;
	float* frame_scale;
	ClockEnv clock_env;
};

Word SpellTimer_Update(SpellHost* host, SpellTimerEnv* env);
