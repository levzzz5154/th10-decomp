#pragma once

// Pause and result menu open paths (retail 0x00422AB0, 0x004231D0).
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

struct OverlayMenu {
	int state;
	RegisteredClock clock;
	void* owner_primary;
	void* owner_secondary;
	Word hud_handle;
	float saved_speed;
	int practice_flag;
};

struct OverlayMenuEnv {
	Word* supervisor_flags; // |= 0x10
	ResultEffectVm* (*acquire_effect)(void);
	void (*assign_script)(ResultEffectVm* vm, int script);
	void (*register_front)(void* manager);
	void* manager;
	void (*position_window)(OverlayMenu* menu, int x, int y, int w, int h);
	Word* hud_score_handle;
	float* global_speed;
	float* frame_scale;
};

struct PauseOpenEnv {
	OverlayMenuEnv common;
	void (*play_sound)(void* sound_manager, int id);
	void* sound_manager;
	void (*play_named_sound)(const char* name, int a, int b);
	void (*capture_background)(void);
	Word* active_script_slot;
	void (*release_script)(void* manager, Word handle);
};

void PauseMenu_Open(OverlayMenu* menu, PauseOpenEnv* env);

struct ResultOpenEnv {
	OverlayMenuEnv common;
	Word* pending_slot; // when 1, only sets the retry mode
	Word config_flags;  // bit 0x1000 selects retry mode 2
	Word* retry_mode_slot;
	void (*play_music)(int channel, const char* path);
	void (*play_named_sound)(const char* name, int a, int b);
	Word sound_config; // bit 0x10 adds an extra named sound
	Byte* score_dirty_flag;
};

void ResultMenu_Open(OverlayMenu* menu, ResultOpenEnv* env);
