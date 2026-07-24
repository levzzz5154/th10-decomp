#pragma once

// Spell card end handling (retail 0x00409C00).
#include "th10/util/scalars.hpp"

struct SpellCard {
	Word flags; // bit 0 active, bit 1 captured
	Word script;
	int bonus;
	int spell_index;
};

struct SpellEndEnv {
	Word* side_flags; // |= 1
	void (*release_effect)(SpellCard* card); // invoked three times
	void (*release_script)(void* manager, Word handle);
	void* manager;
	int* total_score; // capped at 999999999
	void (*show_bonus)(void* hud, int divided, int bonus);
	void* hud;
	int* game_mode; // capture counters skip when == 1
	int* (*per_shot_capture_count)(int spell_index);
	int* (*overall_capture_count)(int spell_index);
	void (*play_sound)(void* sound_manager, int id);
	void* sound_manager;
	Word* hud_effect_slot;
	Word (*spawn_hud_effect)(Word parent, int a, int b);
	Word hud_parent;
};

void SpellCard_OnEnd(SpellCard* card, SpellEndEnv* env);
