#include "th10/game/name_entry.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x004224C0 - draws the name-entry character grid: the current name row,
// the underline cursor, then every charset glyph with the selected index
// highlighted (0xFFFFFF00) and the rest dimmed (0xFF808080). Rows wrap
// every 13 glyphs.
void NameEntry_DrawCharGrid(const NameGridEntry* entry,
                            NameGridEnv* env) {
	int length = (int)std::strlen(env->charset);

	env->draw_name_row(env->text_out);
	*env->color_slot = 0xFFFFFF00u;
	env->draw_cursor(env->text_out);
	*env->color_slot = 0xFFFFFFFFu;

	*env->row_y = 320.0f;
	for (int i = 0; i < length; ++i) {
		*env->color_slot = (entry->cursor_index == (Word)i)
		                       ? 0xFFFFFF00u
		                       : 0xFF808080u;
		env->draw_glyph(env->text_out, env->charset[i]);
		if (i % 13 == 12) {
			*env->row_y += env->line_height;
		}
	}
	*env->color_slot = 0xFFFFFFFFu;
}

// 0x00423570 - initializes the name-entry screen: finds the score rank
// (temporarily switching to the extra table when needed), seeds the cursor,
// copies the default name, and trims trailing spaces.
void NameEntry_Init(NameEntry* entry, NameInitEnv* env) {
	bool swapped = (*env->difficulty == 7 && entry->extra_mode != 0);
	if (swapped) {
		*env->score_table_slot = env->extra_table;
		*env->difficulty = 8;
		*env->difficulty_shadow = 8;
	}
	int rank = env->find_rank();
	if (swapped) {
		*env->score_table_slot = env->normal_table;
		*env->difficulty = 7;
		*env->difficulty_shadow = 7;
	}

	if (rank < 0) {
		entry->failed = 1;
		return;
	}

	entry->rank_cap = 0x19;
	entry->active = 1;
	if (entry->rank_cap != 0 && entry->rank_cap <= rank) {
		rank = entry->rank_cap - 1;
	}
	entry->rank = rank;

	int seed = entry->charset_len;
	if (seed == 0) {
		entry->cursor = 0;
	} else if (seed < 1) {
		entry->cursor = seed - 1;
	} else {
		entry->cursor = 0;
	}
	entry->charset_len = (int)std::strlen(env->charset);
	entry->done_flag = 1;

	std::strcpy(entry->name, env->default_name);
	if (std::memcmp(entry->name, "        ", 9) != 0) {
		env->on_existing_name(-1);
	}

	int length = 8;
	while (length > 0 && entry->name[length - 1] == ' ') {
		--length;
	}
	entry->name_len = length;
	entry->failed = 0;
}
