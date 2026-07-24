#pragma once

// Ending screen state dispatch (retail 0x0042D300).
#include "th10/util/scalars.hpp"

struct EndingScreen {
	int state;         // +0x20
	int state_timer;   // +0x24
	int pending_delay; // +0x2c
	int frame;         // +0x2b4
	int script_id;     // +0x424
	Word color;  // +0x684
	void* text_page;   // +0x18
};

struct EndingEnv {
	void* state_manager;
	int (*load_background)(void* state_manager, int script_id);
	void (*advance_script)(EndingScreen* screen);
	const Word* (*sample_color)(void* text_page, int line, int column);
	void (*set_state)(int state);
	Word input_flags;
	void (*play_sound)(int id);
	void* music_channel;
	void (*stop_music)(void* channel, int argument);
	void (*begin_fade_out)(void);
	void (*pop_state)(int count);
};

int EndingState_Dispatch(EndingScreen* screen, EndingEnv* env);
