#include "th10/game/spell_card_dispatch.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>

namespace {


} // namespace

// 0x0042A6A0 - spell-card dispatch on the manager state word. State 0 records
// the just-declared card: it allocates a zeroed history record, publishes it
// into the per-difficulty history table, snapshots the active spell id,
// stamps the difficulty, and mirrors bit 0 of the global capture flag into
// the record flags. State 1 activates the card for display: the
// per-difficulty slot latches its current values, its counter clears, and
// the record's bonus, capture word, gauge value (times ten), duration
// (preloading the shared spell clock), and trailing fields are published to
// the UI globals. Any other state is a no-op, exactly like retail.
void SpellCard_Dispatch(SpellManager* manager, SpellDispatchEnv* env) {
	SpellUiGlobals* ui = &env->ui;
	int difficulty = *env->difficulty;

	if (manager->state != kSpellStateDeclare) {
		if (manager->state == kSpellStateActivate) {
			SpellSlot* slot = &manager->slots[difficulty];
			slot->previous_a = slot->current_a;
			slot->previous_b = slot->current_b;
			slot->counter = 0;
			SpellRecord* record = slot->record;
			*ui->active_spell_id = record->spell_id;
			*ui->active_spell_aux = 0;
			*ui->bonus_value = record->bonus_initial;
			*ui->bonus_active = record->bonus_active;
			ui->store_gauge(ui->gauge, record->bonus_gauge * 10);
			ui->spell_clock->clock.frame = record->duration;
			if ((ui->spell_clock->flags & 1u) == 0) {
				ui->spell_clock->flags |= 1u;
				ui->spell_clock->clock.control = ui->frame_scale;
			}
			ui->spell_clock->clock.timer = (float)record->duration;
			ui->spell_clock->clock.previous = record->duration - 1;
			*ui->activation_param_a = record->activation_param_a;
			*ui->activation_param_b = record->activation_param_b;
			*ui->history_captures = record->history_captures;
			*ui->history_attempts = record->history_attempts;
		}
		return;
	}

	SpellRecord* record = env->allocate_record();
	manager->history[difficulty] = record;
	record->spell_id = *ui->active_spell_id;
	*ui->active_spell_aux = 0;
	record->difficulty = (short)difficulty;
	record->flags =
	    record->flags ^ ((record->flags ^ *ui->capture_flag) & 1u);
}
