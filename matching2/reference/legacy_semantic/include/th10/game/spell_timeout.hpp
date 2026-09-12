#pragma once

// Spell/attack timeout transition entry (retail 0x004269D0).
// --- 0x004269D0: spell/attack timeout teardown ------------------------------
struct SpellTimeoutTimer {
	int target;
	int current;
	int previous_bits;
	float* speed;
	unsigned flags;
};

struct SpellTimeoutAnimationPair {
	int marker;
	int primary_handle;
	int secondary_handle;
};

struct SpellTimeoutHost {
	int phase;
	SpellTimeoutTimer short_timer;
	SpellTimeoutTimer grace_timer;
	SpellTimeoutAnimationPair animation_pairs[4];
	int caution_active;
	void* sound_owner;
};

struct SpellTimeoutPlayer {
	int stage_frames;
	int charge;
	unsigned main_flags;
	unsigned option_flags[8];
};

struct SpellTimeoutEnv {
	int* bonus_pool;
	int* countdown;
	int* transition_gauge;
	float* frame_speed;
	SpellTimeoutPlayer* player;
	int warning_mode;
	void (*publish_countdown)(int value);
	void (*stop_sound)(void* owner);
	void (*retire_animation)(int handle);
	void (*show_caution)(const char* text);
};

// Timeout transition: decay the bonus toward 5000, reset both timers, retire
// four animation pairs, optionally show "Caution!", clear vulnerable player
// flags after frame 60, and move the transition gauge toward -1024.
void SpellTimeout_EnterTransition(SpellTimeoutHost* host,
                                  SpellTimeoutEnv* env);
