#include "th10/game/game_mode_switch.hpp"

#include <cstdio>

// 0x004218D0 - serializes transitions between the requested and current game
// modes. This preserves the retail switch ordering, including the dedicated
// failure return (4), the gameplay cleanup cases, difficulty publication on
// the results path, and exit-reason publication on the final-menu path.
int GameMode_ApplyRequested(GameModeState* state, GameModeEnv* env) {
	if (state->requested == state->current) {
		return 1;
	}

	env->enter_critical();
	state->critical_depth = (unsigned char)(state->critical_depth + 1);
	const int requested = state->requested;
	state->previous_request = requested;
	state->fade_color = 0xFF000000u;

	switch (state->current) {
	case kGameModeBoot:
		state->current = kGameModeLoading;
		state->loading_owner = env->create_loading_owner();
		if (state->loading_owner == 0) {
			state->current = kGameModeFailure;
			env->show_failure();
			env->finalize_failure();
			return 4;
		}
		break;
	case kGameModeFailure:
		env->show_failure();
		env->finalize_failure();
		return 4;
	case kGameModeMenu:
		switch (requested) {
		case kGameModeLoading:
		case 2:
			break;
		case kGameModeGameplay:
			env->leave_gameplay();
			break;
		case kGameModeCleanup:
			env->prepare_cleanup();
			break;
		default:
			goto commit_menu;
		}
		goto finish;
	case kGameModeGameplay:
		if (requested == kGameModeMenu) {
			env->release_bullets();
		}
		state->gameplay_variant = 1;
		env->enter_gameplay();
		break;
	case kGameModeResults:
		env->leave_gameplay();
		state->gameplay_variant = 1;
		state->current = kGameModeGameplay;
		if (env->active_difficulty_record != 0) {
			const char* base = static_cast<const char*>(env->difficulty_table);
			*env->active_difficulty_record =
			    base + env->selected_difficulty * env->difficulty_stride;
		}
		if (env->active_difficulty != 0) {
			*env->active_difficulty = env->selected_difficulty;
		}
		env->enter_gameplay();
		break;
	case kGameModeReplay:
		state->gameplay_variant = 0;
		if (requested == kGameModeGameplay) {
			env->leave_gameplay();
		}
		state->current = kGameModeGameplay;
		env->enter_gameplay();
		break;
	case kGameModeRestart:
		if (requested == kGameModeMenu) {
			env->release_bullets();
		}
		state->current = kGameModeGameplay;
		state->gameplay_variant = 1;
		env->enter_gameplay();
		break;
	case kGameModeReturn:
		env->leave_gameplay();
		state->gameplay_variant = 1;
		state->current = kGameModeGameplay;
		env->enter_gameplay();
		break;
	case kGameModeCleanup:
		if (requested == kGameModeGameplay) {
			env->leave_gameplay();
		}
		env->prepare_restart();
		break;
	case kGameModeExit:
		if (requested != 2) {
			if (requested == kGameModeGameplay) {
				env->leave_gameplay();
			} else if (requested == kGameModeCleanup) {
				env->prepare_cleanup();
			} else {
				break;
			}
		}
		state->current = kGameModeMenu;
		if (env->exit_reason != 0) {
			*env->exit_reason = 3;
		}
commit_menu:
		env->commit_menu();
		break;
	default:
		break;
	}

finish:
	state->requested = state->current;
	env->leave_critical();
	state->critical_depth = (unsigned char)(state->critical_depth - 1);
	return 1;
}
