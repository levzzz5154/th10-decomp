#pragma once

// Result menu open path with window descriptor and BGM setup (retail 0x00423370).
#include "th10/game/sprite_descriptor.hpp"

struct MenuWindowDescriptor {
	int reserved0;
	int sprite_handle;
	int x;
	int y;
	int width;
	unsigned int flags;
	int resource_08;
	int resource_0c;
	int resource_34;
	int resource_30;
	int trailing;
};
struct MenuWindowEnv {
	SpriteNode* (*resolve)(int handle);
	int (*float_to_long)(float value);
};
int WindowDescriptor_Configure(MenuWindowDescriptor* descriptor, int handle,
                               int x, int y, int width, unsigned int flags,
                               MenuWindowEnv* env);

// --- 0x00423370 -------------------------------------------------------------
struct ResultMenu {
	int state;
	int clock_previous, clock_frame;
	float clock_timer;
	float* clock_control;
	unsigned int clock_flags;
	int primary_owner;
	int secondary_owner;
	int selected_handle;
	float saved_frame_scale;
	int active;
};
struct ResultMenuEnv {
	int supervisor_mode;
	unsigned int input_flags;
	int* supervisor_result_state;
	float* frame_scale;
	void (*set_supervisor_flag)(unsigned int flag);
	int (*create_effect)(int script, int layer);
	void (*register_effect)(int effect_handle);
	void (*position_window)(int owner, int x, int y, int width, int height);
	int selected_handle;
	void (*play_bgm)(const char* path);
	bool extra_sound_enabled;
	void (*load_sound)(const char* name, int slot);
	void (*mark_result_seen)();
};
void ResultMenu_OpenRecovered(ResultMenu* menu,
                              ResultMenuEnv* env);
