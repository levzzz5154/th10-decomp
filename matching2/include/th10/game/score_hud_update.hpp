#pragma once

// Visible-score easing, rank snapshot, and digit VM updates (retail 0x00417040).
struct ScoreHud {
	int displayed_score;
	int score_velocity;
	int previous_high_score;
	int stage_frame;
	unsigned short displayed_crossing_script;
	unsigned short high_score_crossing_script;
};

struct ScoreHudEnv {
	int target_score;
	int high_score;
	int current_rank;
	int previous_rank;
	unsigned int flags;
	int game_mode;
	int threshold_index;
	const int* normal_thresholds;
	const int* special_thresholds;
	void (*set_high_digit)(int slot, int script);
	void (*set_score_digit)(int slot, int script);
	void (*tick_high_digit)(int slot);
	void (*tick_score_digit)(int slot);
	void (*set_rank_digit)(bool previous, int script);
	void (*tick_rank_digit)(bool previous);
	int (*award_extend)(int count);
};

int ScoreHud_Update(ScoreHud* hud, ScoreHudEnv* env);
