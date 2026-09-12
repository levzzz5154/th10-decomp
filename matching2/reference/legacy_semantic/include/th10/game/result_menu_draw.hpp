#pragma once

// Result-menu replay/name-entry/ranking renderer (retail 0x00422660).
//
// Retail function 0x00422660 (__stdcall, 1072 bytes). It owns the three
// result-menu drawing states used twice by the state machine (10/17, 11/18,
// 12/19), including replay-slot dates, the animated name-entry grid, and the
// ten score-file ranking rows. Every renderer/global edge is injected so the
// reconstruction is deterministic in host-side tests.

struct ResultDrawPoint {
	float x;
	float y;
	int z;
};

struct ResultDrawDate {
	int year;  // full year; renderer emits year % 100
	int month; // 1..12
	int day;
};

// Metadata reached through replay_slot->payload in states 10/17 and through
// selected_replay in states 11/18. Offsets in the retail payload are
// +0 name, +12 timestamp, +80 character, +84 shot, +88 difficulty, +92 stage.
struct ResultReplayInfo {
	const char* name;
	int timestamp;
	int character;
	int shot;
	int difficulty;
	int stage;
};

struct ResultReplaySlot {
	const ResultReplayInfo* payload;
};

struct ResultMenuView {
	int unused_0;
	int state;                 // +4
	int unused_8[3];
	int transition_frame;      // +20
	int unused_24[3];
	int selected_index;        // +36
	int unused_40[112];
	int suppress_grid;         // +488; nonzero disables ranking cursor
	ResultReplaySlot* replay_slots[25]; // +492
};

struct RankingGlobals {
	int character;
	int stage;
	int difficulty;
	int mode; // state 11/18 uses this as the final label index
};

struct ResultDrawState {
	unsigned int color; // game-thread +0x8974
	int busy;           // game-thread +0x8988
};

struct ResultDrawEnv {
	ResultDrawState* render;
	const unsigned char* score_file; // 17276-byte character/stage records
	RankingGlobals* globals;
	const ResultReplayInfo* selected_replay; // retail Block->payload
	const char* const* character_shot_labels; // [character * 3 + shot]
	const char* const* difficulty_labels;
	const char* const* stage_labels;
	const char* const* score_stage_labels; // indexed by score row byte +28
	ResultDrawDate (*decode_date)(int timestamp);
	void (*draw_text)(const ResultDrawPoint* point, const char* text);
	void (*draw_name_grid)(ResultMenuView* menu, const ResultDrawPoint* point);
};

// 0x00422660 - Draw the active replay/name-entry/ranking result-menu state.
// Returns 1 and brackets every state, including defaults, with busy = 1/0.
int ResultMenu_DrawReplayAndRanking(ResultMenuView* menu,
                                    const ResultDrawEnv* env);
