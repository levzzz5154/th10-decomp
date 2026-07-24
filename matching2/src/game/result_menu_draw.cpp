#include "th10/game/result_menu_draw.hpp"

#include <cstdio>
#include <cstdarg>
#include <cstring>

namespace {
const int kRecordStride = 17276;
const unsigned int kDim = 0xFF808080u;
const unsigned int kHighlight = 0xFFFFFF00u;

void Draw(const ResultDrawEnv* env, ResultDrawPoint* point,
          const char* format, ...) {
	char text[192];
	va_list args;
	va_start(args, format);
	std::vsnprintf(text, sizeof(text), format, args);
	va_end(args);
	env->draw_text(point, text);
}

ResultDrawDate Date(const ResultDrawEnv* env, int timestamp) {
	return env->decode_date(timestamp);
}

const char* ReplayLabel(const ResultDrawEnv* env,
                        const ResultReplayInfo* info) {
	return env->character_shot_labels[3 * info->character + info->shot];
}

void DrawReplayList(ResultMenuView* menu, const ResultDrawEnv* env) {
	ResultDrawPoint point = {48.0f, 64.0f, 0};
	for (int i = 0; i < 25; ++i) {
		env->render->color = i == menu->selected_index ? kHighlight : kDim;
		ResultReplaySlot* slot = menu->replay_slots[i];
		if (slot && slot->payload) {
			const ResultReplayInfo* info = slot->payload;
			ResultDrawDate date = Date(env, info->timestamp);
			Draw(env, &point, "No.%.2d %s %.2d/%.2d/%.2d %s %s %s",
			     i + 1, info->name, date.year % 100, date.month, date.day,
			     ReplayLabel(env, info),
			     env->difficulty_labels[info->difficulty],
			     env->stage_labels[info->stage]);
		} else {
			Draw(env, &point, "No.%.2d -------- --/--/-- ------- - St-", i + 1);
		}
		point.y += 15.0f;
	}
	env->render->color = 0xFFFFFFFFu;
}

void DrawReplayEntry(ResultMenuView* menu, const ResultDrawEnv* env) {
	float y;
	if (menu->transition_frame >= 10) {
		y = 224.0f;
	} else {
		float selected_y = menu->selected_index * 15.0f + 64.0f;
		y = (224.0f - selected_y) * menu->transition_frame * 0.1f + selected_y;
	}
	ResultDrawPoint grid = {102.0f, y, 0};
	env->draw_name_grid(menu, &grid);

	const ResultReplayInfo* info = env->selected_replay;
	ResultDrawDate date = Date(env, info->timestamp);
	ResultDrawPoint point = {48.0f, y, 0};
	Draw(env, &point, "No.%.2d          %.2d/%.2d/%.2d %s %s %s",
	     menu->selected_index + 1, date.year % 100, date.month, date.day,
	     ReplayLabel(env, info), env->difficulty_labels[info->difficulty],
	     env->stage_labels[env->globals->mode]);
}

void DrawScoreRanking(ResultMenuView* menu, const ResultDrawEnv* env) {
	ResultDrawPoint point = {48.0f, 64.0f, 0};
	Draw(env, &point, "            Score Ranking!!");

	int selected = menu->suppress_grid ? -1 : menu->selected_index;
	if (!menu->suppress_grid) {
		ResultDrawPoint grid = {75.0f, menu->selected_index * 18.0f + 96.0f, 0};
		env->draw_name_grid(menu, &grid);
	}

	point.x = 48.0f;
	point.y = 96.0f;
	const int record_index = 3 * env->globals->character + env->globals->stage;
	const unsigned char* rows = env->score_file + kRecordStride * record_index +
	                            240 * env->globals->difficulty;
	for (int i = 0; i < 10; ++i) {
		const unsigned char* row = rows + 24 * i;
		int score = 0;
		int timestamp = 0;
		std::memcpy(&score, row + 24, sizeof(score));
		std::memcpy(&timestamp, row + 40, sizeof(timestamp));
		char name[11];
		std::memcpy(name, row + 30, 10);
		name[10] = 0;
		env->render->color = i == selected ? kHighlight : kDim;
		if (timestamp) {
			ResultDrawDate date = Date(env, timestamp);
			Draw(env, &point, "%2d %s %.9ld%d %.2d/%.2d/%.2d %s",
			     i + 1, name, (long)score, (int)(signed char)row[29],
			     date.year % 100, date.month, date.day,
			     env->score_stage_labels[(int)(signed char)row[28]]);
		} else {
			Draw(env, &point, "%2d %s %.9ld%d --/--/-- Stage -",
			     i + 1, name, (long)score, (int)(signed char)row[29]);
		}
		point.y += 18.0f;
	}
	env->render->color = 0xFFFFFFFFu;
}
} // namespace

// 0x00422660 - replay/name-entry/score-ranking renderer.
int ResultMenu_DrawReplayAndRanking(ResultMenuView* menu,
                                    const ResultDrawEnv* env) {
	env->render->busy = 1;
	switch (menu->state) {
	case 10:
	case 17:
		DrawReplayList(menu, env);
		break;
	case 11:
	case 18:
		DrawReplayEntry(menu, env);
		break;
	case 12:
	case 19:
		DrawScoreRanking(menu, env);
		break;
	default:
		break;
	}
	env->render->busy = 0;
	return 1;
}
