#include "th10/game/stage_entry.hpp"

#include <cstring>

namespace {

// Per character/stage record stride in the score file (retail 17276; the
// record index is 3*character + stage).
const int kScoreRecordStride = 17276;

// Shared failure exit (retail LABEL_38): mark the context failed, release
// the overlay handles, publish the result words, and kill both task nodes.
// The entry bit (flag bit 2) intentionally stays set.
int FailStageEntry(StageContext* context, const StageEntryEnv* env) {
	context->flags |= 8u;
	env->release_overlay_anm(env->anm_slots);
	env->globals->result_492264 = 0;
	env->globals->result_492260 = 1;
	if (context->update_task)
		context->update_task->flags |= 2u;
	if (context->draw_task)
		context->draw_task->flags |= 2u;
	return -1;
}

} // namespace

// 0x00417870 - Stage entry orchestrator.
int StageContext_Enter(StageContext* context,
                       const StageEntryEnv* env) {
	StageGlobals* g = env->globals;

	// Mark the stage as entering, then wait for the sync pair to go
	// negative. The UI abort bit 0x80 fails the entry from inside the wait.
	context->flags |= 4u;
	for (;;) {
		if (g->sync[0] < 0 && g->sync[1] < 0)
			break;
		if ((g->ui_flags & 0x80u) != 0)
			return FailStageEntry(context, env);
		env->sleep(1);
	}

	g->frame_scale = 1.0f;
	g->counter_474c88 = 0;
	g->counter_474c8c = 0;

	if (g->fresh_run) {
		// Stage practice (mode 7) forces difficulty 4 before the record
		// lookup (retail writes dword_474C74 as well).
		int difficulty = g->difficulty;
		if (g->mode == 7) {
			difficulty = 4;
			g->difficulty = 4;
		}
		const int difficulty_offset = 240 * difficulty;
		const unsigned char* record =
			env->score_file +
			kScoreRecordStride * (3 * g->character + g->stage);
		int starting_score = 0;
		std::memcpy(&starting_score, record + difficulty_offset + 24, 4);
		g->score_seed = starting_score;
		g->power_seed = record[difficulty_offset + 29];
		if ((g->game_flags & 8u) == 0)
			g->power_474c90 = 0;
		g->score_current = 0;
		env->seed_extend_threshold(&g->score_seed, 50000);
		if ((g->game_flags & 0x10u) != 0)
			g->lives = g->continues ? g->continues - 1 : 9;
		else
			g->lives = 2;
		g->bomb_fragments = g->mode != 1 ? 0x50 : 0;
		g->game_flags &= ~4u;
		if (!context->replay_handle) {
			// Play-count increment, capped at 99999.
			unsigned char* count_slot =
				env->score_file +
				kScoreRecordStride * (3 * g->character + g->stage) + 1224;
			int play_count = 0;
			std::memcpy(&play_count, count_slot, 4);
			if (play_count < 99999) {
				++play_count;
				std::memcpy(count_slot, &play_count, 4);
			}
		}
		g->counter_474c9c = 0;
		g->counter_474c98 = (g->game_flags & 8u) != 0 ? -512 : 0;
	} else if (g->score_current > g->score_seed) {
		g->score_seed = g->score_current;
	}
	g->extend_index = 9;

	// Register the update task (callback 0x004187C0, priority 10) and the
	// draw task (callback 0x004187D0, priority 4).
	StageTaskNode* update_node = env->create_task(0);
	update_node->flags &= ~2u;
	update_node->context = context;
	env->register_update(10, update_node, env->scheduler);
	context->update_task = update_node;
	StageTaskNode* draw_node = env->create_task(1);
	draw_node->flags &= ~2u;
	draw_node->context = context;
	env->register_draw(4, draw_node, env->scheduler);
	context->draw_task = draw_node;

	// Stage descriptor and number.
	std::memcpy(context->descriptor, env->stage_descriptor,
	            sizeof(context->descriptor));
	context->stage_number = env->stage_record->number;

	int stage_state;
	if ((g->game_flags & 2u) != 0) {
		// Replay run: reset the replay block, seed it from the game state,
		// and load the stage script (0x00413A20's result is ignored).
		env->replay_reset();
		env->replay_seed(env->game);
		stage_state =
			env->load_stage_script(env->stage_record->script_name, 0);
	} else {
		if (!env->init_side_panel(context->replay_handle, env->key_buffer) ||
		    !env->load_stage_script(env->stage_record->script_name, 0) ||
		    !env->init_414830() || !env->init_425020() ||
		    !env->init_406060() || !env->init_41aed0() ||
		    !env->create_score_manager() || !env->init_422360() ||
		    !env->init_419090()) {
			return FailStageEntry(context, env);
		}
		stage_state = env->create_stage_state();
	}
	if (!stage_state)
		return FailStageEntry(context, env);

	// Spell-practice runs (game flags bits 0/3) reset the practice path;
	// otherwise the enemy manager is constructed from the stage record.
	if ((g->game_flags & 9u) != 0)
		env->spell_practice_reset(env->spell_practice_state);
	else if (!env->create_enemy_manager(env->stage_record->enemy_script))
		return FailStageEntry(context, env);

	if (!env->create_bullet_manager() || !env->init_4056b0() ||
	    !env->init_408c90()) {
		return FailStageEntry(context, env);
	}

	// Stage music unless suppressed by game flag bit 5.
	if ((g->game_flags & 0x20u) == 0) {
		env->music_reset();
		env->music_load(0, env->stage_record->music_name);
		env->music_load(1, env->stage_record->music_loop);
	}

	// Camera shake reset and player spawn arm.
	g->camera_b = 0.0;
	g->camera_a = 0.0;
	env->reset_player_spawn(context->spawn, 0);

	// Wait out the background loader.
	while (g->loader_busy)
		env->sleep(16);

	if (g->pending_474c84)
		g->counter_474c8c = 0;
	g->pending_474c84 = 0;
	env->release_pending_anm(env->anm_slots);

	context->flags &= ~4u;
	g->game_flags &= 0xFFFFFFF4u;
	g->result_492264 = 0;
	g->result_492260 = 1;
	g->counter_4918a4 = 0;
	env->request_callback_removal(context);
	return 0;
}

// 0x004187C0 - Update-task adapter (`push ecx; call sub_418190; retn`).
int StageTask_UpdateThunk(void* context, int (*stage_update)(void* context)) {
	return stage_update(context);
}

// 0x004187D0 - Draw-task callback: clear the camera-interpolator words
// while no stage entry is in progress.
int StageTask_ClearCameraOnIdle(const StageContext* context,
                                int* camera_words) {
	if ((context->flags & 4u) == 0) {
		camera_words[20] = 0;
		camera_words[21] = 0;
		camera_words[19] = 0;
		camera_words[22] = 0;
	}
	return 1;
}
