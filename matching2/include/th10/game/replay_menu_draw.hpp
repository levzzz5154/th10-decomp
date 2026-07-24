#pragma once

// Replay-management menu renderer for list and name states (retail 0x00433B30).
// Retail function 0x00433B30 (__stdcall, 960 bytes).

struct ReplayMenuPoint { float x; float y; int z; };
struct ReplayMenuDate { int year; int month; int day; int hour; int minute; };

struct ReplayMenuInfo {
	const char* name;
	int timestamp;
	float clear_percent;
	int character;
	int shot;
	int difficulty;
	int stage;
};
struct ReplayMenuSlot { const ReplayMenuInfo* payload; };

struct ReplayMenu {
	int state;                  // retail +32: 2=list, 3=name entry
	int selected_index;         // +36
	int transition_frame;       // +692; name UI appears at 10
	float transition_progress;  // +696; tween term used while frame < 10
	int entry_index;            // +23004
	char entered_name[12];      // +22748
	int name_cursor;            // +22760
	int charset_cursor;         // +22772
	ReplayMenuSlot* replay_slots[25]; // +23012
};

struct ReplayMenuDrawState { unsigned int color; int busy; };
struct ReplayMenuDrawEnv {
	ReplayMenuDrawState* render;
	const ReplayMenuInfo* selected_replay; // retail Block->payload
	const char* charset;
	const char* const* character_shot_labels;
	const char* const* difficulty_labels;
	const char* const* stage_labels;
	const char* all_stages_label;
	ReplayMenuDate (*decode_date)(int timestamp);
	void (*draw_text)(const ReplayMenuPoint* point, const char* text);
};

// 0x00433B30 - Draw replay-management states 2 and 3. Returns 1.
int ReplayManager_Draw(ReplayMenu* menu, const ReplayMenuDrawEnv* env);
