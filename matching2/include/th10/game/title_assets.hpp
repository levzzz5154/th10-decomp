#pragma once

// Title screen core asset load (retail 0x0041F990).
#include "th10/util/scalars.hpp"

struct TitleScreen {
	void* signature_anm;      // +0x3e0
	int signature_ready;      // +0x3e4
	int interface_ready;      // +0x3e8
	Word* update_flags; // update task flag word
	Word* draw_flags;   // draw task flag word
};

struct TitleEnv {
	void* archive_manager;
	void* (*open_anm)(int slot, void* archive_manager, const char* name);
	void* (*create_title_task)(void);
	void (*report_error)(void* sink, const char* message);
	void* error_sink;
	const char* task_error_text;
	const char* score_error_text;
	void** interface_anm_slot;
	Byte* (*load_score_file)(Word* size_slot, int mode);
	Byte** score_data_slot;
	int (*init_sound_buffers)(void);
	int (*archive_has_file)(const char* name);
	Word config_flags; // bit 0x10 selects midi playback
	int (*start_music_stream)(const char* name);
	void (*select_midi_playback)(void);
	void (*load_score_table)(void);
	void (*enter_title_menu)(void);
	int* failure_state; // set to 3 when core assets are missing
};

int TitleScreen_LoadCoreAssets(TitleScreen* title, TitleEnv* env);
