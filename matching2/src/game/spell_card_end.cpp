#include "th10/game/spell_card_end.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x00409C00 - finishes a spell card: flags the side, releases the three
// attached effects and the script, awards the capture bonus (capped) with
// capture-count bookkeeping, or resets the HUD effect on a miss.
void SpellCard_OnEnd(SpellCard* card, SpellEndEnv* env) {
	if ((card->flags & 1u) == 0) {
		return;
	}

	*env->side_flags |= 1u;
	env->release_effect(card);
	env->release_effect(card);
	env->release_effect(card);

	card->flags &= ~1u;
	env->release_script(env->manager, card->script);
	card->script = 0;

	if ((card->flags & 2u) != 0) {
		int divided = card->bonus / 10;
		*env->total_score += divided;
		if (*env->total_score > 999999999) {
			*env->total_score = 999999999;
		}
		env->show_bonus(env->hud, divided, card->bonus);

		if (*env->game_mode != 1) {
			int* per_shot = env->per_shot_capture_count(card->spell_index);
			if (*per_shot < 99999) {
				*per_shot += 1;
			}
			int* overall = env->overall_capture_count(card->spell_index);
			if (*overall < 99999) {
				*overall += 1;
			}
		}
		env->play_sound(env->sound_manager, 0);
	} else {
		env->release_script(env->manager, *env->hud_effect_slot);
		*env->hud_effect_slot = 0;
		*env->hud_effect_slot = env->spawn_hud_effect(env->hud_parent, 0x48, 0xF);
	}
}
