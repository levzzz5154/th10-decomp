#include "th10/game/result_menu_draw.hpp"

#include <cstdio>
#include <cstring>

static int g_failures;
#define CHECK(x) do { if (!(x)) { std::printf("CHECK failed line %d: %s\n", __LINE__, #x); ++g_failures; } } while (0)

static ResultDrawState g_render;
static RankingGlobals g_globals;
static unsigned char g_score[17276 * 3];
static char g_text[32][192];
static ResultDrawPoint g_points[32];
static unsigned int g_colors[32];
static int g_draw_count;
static int g_grid_count;
static ResultDrawPoint g_grid_point;
static int g_busy_seen;

static const char* g_charshots[] = {"ReimuA", "ReimuB", "ReimuC", "MarisaA", "MarisaB", "MarisaC"};
static const char* g_difficulties[] = {"Easy", "Normal", "Hard", "Lunatic", "Extra"};
static const char* g_stages[] = {"St0", "St1", "St2", "St3", "St4", "St5", "St6", "St7", "St8", "St9"};
static const char* g_score_stages[] = {"Stage 0", "Stage 1", "Stage 2", "Stage 3", "Stage 4"};

static ResultDrawDate DecodeDate(int timestamp) {
	ResultDrawDate d = {2000 + timestamp / 10000, (timestamp / 100) % 100, timestamp % 100};
	return d;
}
static void DrawText(const ResultDrawPoint* point, const char* text) {
	g_busy_seen += g_render.busy == 1;
	g_points[g_draw_count] = *point;
	g_colors[g_draw_count] = g_render.color;
	std::strncpy(g_text[g_draw_count], text, sizeof(g_text[0]) - 1);
	g_text[g_draw_count][sizeof(g_text[0]) - 1] = 0;
	++g_draw_count;
}
static void DrawGrid(ResultMenuView*, const ResultDrawPoint* point) {
	g_busy_seen += g_render.busy == 1;
	g_grid_point = *point;
	++g_grid_count;
}

static ResultDrawEnv MakeEnv() {
	ResultDrawEnv env = {};
	env.render = &g_render;
	env.score_file = g_score;
	env.globals = &g_globals;
	env.character_shot_labels = g_charshots;
	env.difficulty_labels = g_difficulties;
	env.stage_labels = g_stages;
	env.score_stage_labels = g_score_stages;
	env.decode_date = DecodeDate;
	env.draw_text = DrawText;
	env.draw_name_grid = DrawGrid;
	return env;
}
static void Reset() {
	std::memset(&g_render, 0, sizeof(g_render));
	std::memset(&g_globals, 0, sizeof(g_globals));
	std::memset(g_score, 0, sizeof(g_score));
	std::memset(g_text, 0, sizeof(g_text));
	g_draw_count = g_grid_count = g_busy_seen = 0;
}

static void TestReplayList() {
	Reset();
	ResultMenuView menu = {};
	menu.state = 10;
	menu.selected_index = 1;
	ResultReplayInfo info = {"REPLAY", 260724, 1, 2, 3, 4};
	ResultReplaySlot slot = {&info};
	menu.replay_slots[1] = &slot;
	ResultDrawEnv env = MakeEnv();
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_draw_count == 25 && g_grid_count == 0);
	CHECK(std::strcmp(g_text[0], "No.01 -------- --/--/-- ------- - St-") == 0);
	CHECK(std::strcmp(g_text[1], "No.02 REPLAY 26/07/24 MarisaC Lunatic St4") == 0);
	CHECK(g_points[0].x == 48.0f && g_points[0].y == 64.0f);
	CHECK(g_points[24].y == 424.0f);
	CHECK(g_colors[0] == 0xFF808080u && g_colors[1] == 0xFFFFFF00u);
	CHECK(g_render.color == 0xFFFFFFFFu && g_render.busy == 0);
	CHECK(g_busy_seen == 25);

	menu.state = 17;
	g_draw_count = 0;
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_draw_count == 25);
}

static void TestReplayEntryTween() {
	Reset();
	ResultMenuView menu = {};
	menu.state = 11;
	menu.selected_index = 4;
	menu.transition_frame = 5;
	ResultReplayInfo info = {"NAME", 251231, 0, 1, 2, 3};
	ResultDrawEnv env = MakeEnv();
	env.selected_replay = &info;
	g_globals.mode = 7;
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_grid_count == 1 && g_draw_count == 1);
	CHECK(g_grid_point.x == 102.0f && g_grid_point.y == 174.0f);
	CHECK(g_points[0].y == 174.0f);
	CHECK(std::strcmp(g_text[0], "No.05          25/12/31 ReimuB Hard St7") == 0);

	menu.state = 18;
	menu.transition_frame = 10;
	g_grid_count = g_draw_count = 0;
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_grid_point.y == 224.0f && g_points[0].y == 224.0f);
}

static void PutInt(unsigned char* p, int value) { std::memcpy(p, &value, 4); }
static void TestScoreRanking() {
	Reset();
	ResultMenuView menu = {};
	menu.state = 12;
	menu.selected_index = 2;
	g_globals.character = 0;
	g_globals.stage = 0;
	g_globals.difficulty = 1;
	unsigned char* row0 = g_score + 240;
	PutInt(row0 + 24, 123456789);
	row0[28] = 2;
	row0[29] = 4;
	std::memcpy(row0 + 30, "ABCDEFGHIJ", 10);
	PutInt(row0 + 40, 240102);
	unsigned char* row2 = row0 + 48;
	PutInt(row2 + 24, 42);
	row2[29] = 1;
	std::memcpy(row2 + 30, "EMPTY     ", 10);

	ResultDrawEnv env = MakeEnv();
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_draw_count == 11 && g_grid_count == 1);
	CHECK(std::strcmp(g_text[0], "            Score Ranking!!") == 0);
	CHECK(std::strcmp(g_text[1], " 1 ABCDEFGHIJ 1234567894 24/01/02 Stage 2") == 0);
	CHECK(std::strcmp(g_text[3], " 3 EMPTY      0000000421 --/--/-- Stage -") == 0);
	CHECK(g_grid_point.x == 75.0f && g_grid_point.y == 132.0f);
	CHECK(g_colors[3] == 0xFFFFFF00u);
	CHECK(g_points[1].y == 96.0f && g_points[10].y == 258.0f);
	CHECK(g_render.color == 0xFFFFFFFFu);

	menu.state = 19;
	menu.suppress_grid = 1;
	g_draw_count = g_grid_count = 0;
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_grid_count == 0 && g_draw_count == 11);
	for (int i = 1; i < 11; ++i) CHECK(g_colors[i] == 0xFF808080u);
}

static void TestDefault() {
	Reset();
	ResultMenuView menu = {};
	menu.state = 15;
	ResultDrawEnv env = MakeEnv();
	CHECK(ResultMenu_DrawReplayAndRanking(&menu, &env) == 1);
	CHECK(g_draw_count == 0 && g_grid_count == 0 && g_render.busy == 0);
}

int main() {
	TestReplayList();
	TestReplayEntryTween();
	TestScoreRanking();
	TestDefault();
	if (g_failures) return 1;
	std::printf("recovery_batch26_test passed\n");
	return 0;
}
