#pragma once

// Pause menu timer reset (retail 0x00424D90).
#include "th10/game/registered_clock.hpp"

struct PauseMenu {
	int active;                    // +0x458
	RegisteredClock fade;    // +0x460
	RegisteredClock cursor;  // +0x474
	RegisteredClock slide;   // +0x488
	int script_handle;             // +0x329c
};

struct PauseResetEnv {
	float* frame_scale;
	void* state_manager;
	void (*release_script)(float* frame_scale, void* state_manager, int script);
	void (*play_music)(int track);
	int music_track;
};

void PauseMenu_ResetTimers(PauseMenu* menu, PauseResetEnv* env);
