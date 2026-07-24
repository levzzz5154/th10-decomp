#include "th10/game/replay_menu_draw.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace {
const unsigned int kDim = 0xFF808080u;
const unsigned int kHighlight = 0xFFFFFF00u;
void Draw(const ReplayMenuDrawEnv* env, ReplayMenuPoint* point, const char* format, ...) {
	char text[192];
	va_list args;
	va_start(args, format);
	std::vsnprintf(text, sizeof(text), format, args);
	va_end(args);
	env->draw_text(point, text);
}
const char* Shot(const ReplayMenuDrawEnv* env, const ReplayMenuInfo* info) {
	return env->character_shot_labels[3 * info->character + info->shot];
}
void DrawReplay(const ReplayMenuDrawEnv* env, ReplayMenuPoint* point, int number,
                const char* name, const ReplayMenuInfo* info,
                const char* stage_label) {
	ReplayMenuDate d = env->decode_date(info->timestamp);
	Draw(env, point, "No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%",
	     number, name, d.year % 100, d.month, d.day, d.hour, d.minute,
	     Shot(env, info), env->difficulty_labels[info->difficulty],
	     stage_label, (double)info->clear_percent);
}
void DrawList(ReplayMenu* menu, const ReplayMenuDrawEnv* env) {
	env->render->busy = 1;
	ReplayMenuPoint p = {58.0f, 80.0f, 0};
	for (int i = 0; i < 25; ++i) {
		env->render->color = i == menu->selected_index ? kHighlight : kDim;
		ReplayMenuSlot* slot = menu->replay_slots[i];
		if (slot && slot->payload)
			DrawReplay(env, &p, i + 1, slot->payload->name, slot->payload,
			           env->stage_labels[slot->payload->stage]);
		else
			Draw(env, &p, "No.%.2d -------- --/--/-- --:-- ------- ------- --- ---%%", i + 1);
		p.y += 15.0f;
	}
}
void DrawEntry(ReplayMenu* menu, const ReplayMenuDrawEnv* env) {
	float y = 240.0f;
	if (menu->transition_frame < 10) {
		float source = (float)(15 * menu->entry_index + 80);
		y = (10.0f - menu->transition_progress) * (source - 240.0f) * 0.1f + 240.0f;
	}
	ReplayMenuPoint p = {58.0f, y, 0};
	DrawReplay(env, &p, menu->entry_index + 1, "        ", env->selected_replay,
	           env->all_stages_label);
	if (menu->transition_frame < 10)
		return;

	p.x = 112.0f; p.y = 240.0f;
	env->render->color = 0xFFFFFFFFu;
	Draw(env, &p, "%s", menu->entered_name);
	p.x = 112.0f + 9.0f * menu->name_cursor;
	if (menu->name_cursor == 8) p.x -= 9.0f;
	env->render->color = kHighlight;
	Draw(env, &p, "_");

	const int length = (int)std::strlen(env->charset);
	p.x = 212.0f; p.y = 360.0f;
	for (int i = 0; i < length; ++i) {
		env->render->color = i == menu->charset_cursor ? kHighlight : kDim;
		int glyph;
		if (i < length - 3) glyph = (unsigned char)env->charset[i];
		else if (i == length - 3) glyph = 129;
		else if (i == length - 2) glyph = 127;
		else glyph = 128;
		Draw(env, &p, "%c", glyph);
		if (i % 13 == 12) { p.x = 212.0f; p.y += 16.0f; }
		else p.x += 18.0f;
	}
}
} // namespace

// 0x00433B30 - replay-management renderer.
int ReplayManager_Draw(ReplayMenu* menu, const ReplayMenuDrawEnv* env) {
	if (menu->state == 2) DrawList(menu, env);
	else if (menu->state == 3) DrawEntry(menu, env);
	else return 1;
	env->render->color = 0xFFFFFFFFu;
	env->render->busy = 0;
	return 1;
}
