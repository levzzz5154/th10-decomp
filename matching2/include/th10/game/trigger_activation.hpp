#pragma once

// Trigger active-state entry with lead effect and companions (retail 0x00426CF0).
struct TriggerClock {
	int previous;
	int frame;
	float timer;
	float* control;
	unsigned int flags;
};

// --- 0x00426CF0: activate a stage trigger -----------------------------------
struct TriggerActivation {
	int mode;
	TriggerClock activation_clock;
	TriggerClock cooldown_clock;
	unsigned short animation_handle;
};

struct TriggerActivationEnv {
	float* frame_scale;
	bool sound_suppressed;
	void (*spawn_effect)(int script, TriggerActivation* owner);
	void (*play_sound)(int id);
	void (*set_animation)(unsigned short handle);
	int stage_counter;
	unsigned int* stage_flags[8];
	int* stage_latch;
};

void TriggerRegion_Activate(TriggerActivation* trigger,
                            TriggerActivationEnv* env);
