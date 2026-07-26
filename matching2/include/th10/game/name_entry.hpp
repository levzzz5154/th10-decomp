#pragma once

// Name entry character grid draw and init (retail 0x004224C0, 0x00423570).
#include "th10/util/scalars.hpp"

struct NameGridEntry {
	Word cursor_index;
};

struct NameGridEnv {
	const char* charset;
	void* text_out;
	Word* color_slot;
	void (*draw_name_row)(void* text_out);
	void (*draw_cursor)(void* text_out);
	void (*draw_glyph)(void* text_out, char glyph);
	float line_height;
	float* row_y; // starts at 320.0f
};

void NameEntry_DrawCharGrid(const NameGridEntry* entry, NameGridEnv* env);

struct NameEntry {
	int rank;
	int rank_cap;
	int active;
	int cursor;
	int charset_len; // input: signed cursor seed; output: charset length
	int done_flag;
	int name_len;
	int extra_mode; // non-zero on extra-capable saves
	int failed;
	char name[12];
};

struct NameInitEnv {
	int* difficulty;
	int* difficulty_shadow;
	const void** score_table_slot;
	const void* extra_table;
	const void* normal_table;
	int (*find_rank)(void);
	const char* charset;
	const char* default_name;
	void (*on_existing_name)(int amount);
};

void NameEntry_Init(NameEntry* entry, NameInitEnv* env);

struct NameEntryMenuInput { unsigned held, pressed; };
struct NameEntryMenuOps {
	void* context;
	const char* charset;
	void (*set_phase)(void*, int);
	void (*move_cursor)(void*, NameEntry*, int);
	void (*play_sound)(void*, int);
	void (*commit_name)(void*, const char*);
	void (*close_view)(void*, int);
};

// 0x00432CB0 - high-score name-entry update state machine.
int NameEntry_UpdateMenu(NameEntry* entry, int* phase, int phase_timer,
	                    const NameEntryMenuInput* input,
	                    const NameEntryMenuOps* ops);
