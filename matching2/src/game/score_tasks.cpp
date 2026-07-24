#include "th10/game/score_tasks.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {


void RegisterClock(RegisteredClock* clock, float* frame_scale) {
	if ((clock->flags & 1u) == 0) {
		clock->clock.frame = 0;
		clock->clock.previous = (int)0xFFF0BDC1u;
		clock->clock.timer = 0.0f;
		clock->clock.control = frame_scale;
		clock->flags |= 1u;
	}
}

// Common retail reset: register, then zero the clock with previous = -1.
void ResetClock(RegisteredClock* clock, float* frame_scale) {
	RegisterClock(clock, frame_scale);
	clock->clock.frame = 0;
	clock->clock.timer = 0.0f;
	clock->clock.previous = -1;
}


} // namespace

#include <cmath>

namespace {

// Shared retail clock idioms (same semantics as earlier batches).

} // namespace

// 0x0042AF20 - allocates and initializes the global score data block
// (0x1DCB4 bytes in retail), storing it in the global slot.
void ScoreData_CreateGlobal(ScoreCreateEnv* env) {
	void* block = env->allocate(0x1DCB4u);
	if (block != 0) {
		*env->global_slot = env->initialize(block);
	} else {
		*env->global_slot = 0;
	}
}

// 0x00413A20 - builds the score task: creates the task object, loads the
// score file (or adopts a preloaded block), and resets the HUD fields.
int ScoreTask_Init(ScoreHost* host, ScoreInitEnv* env) {
	host->task = env->create_task(0x1C, env->manager, env->task_name);
	if (host->task == 0) {
		env->fatal_error(env->error_sink, env->error_text);
		return -1;
	}

	if (env->preloaded_data != 0 && *env->preloaded_data != 0) {
		host->data = *env->preloaded_data;
		*env->preloaded_data = 0;
	} else {
		std::strcpy(env->path_buffer, env->score_path);
		host->data = env->load_file(0, 0);
		if (host->data == 0) {
			env->fatal_error(env->error_sink, env->error_text);
			return -1;
		}
	}

	ResetClock(&host->clock, env->frame_scale);
	host->clock.clock.previous = -1;
	host->hud_a = -1;
	host->hud_b = -1;
	host->saved_score = env->current_score;
	return 0;
}

// 0x0041C330 - per-frame walk over the score-task list. Every node is either
// retired (its destroy callback runs, the node is unlinked with the retail
// sentinel convention, the live count drops, the cursor is repaired, and the
// node is freed) or ticked (its update callback runs and, when it returns 0,
// the embedded clock advances). Retirement triggers on a nonzero retire
// counter reaching 2, on kill_flag == 1, or on a nonzero update result.
// Returns 1 like retail.
int ScoreTaskList_Tick(ScoreTaskList* list, const ClockEnv* clock_env) {
	ScoreTaskNode* node = list->head_sentinel.next;
	while (node != 0) {
		ScoreTaskNode* next = node->next;
		int retire = 0;
		if (node->retire_count != 0) {
			node->retire_count = (Byte)(node->retire_count + 1);
			if (node->retire_count >= 2) {
				retire = 1;
			}
		}
		if (!retire) {
			if (node->kill_flag == 1) {
				retire = 1;
			} else if (node->update(node) == 0) {
				node->clock.previous = node->clock.frame;
				float control = *node->clock.control;
				if (control <= clock_env->span_low ||
				    clock_env->span_high <= control) {
					node->clock.timer += control;
					node->clock.frame =
					    (int)clock_env->float_to_long(node->clock.timer);
				} else {
					node->clock.timer += clock_env->frame_step;
					node->clock.frame += 1;
				}
				node = next;
				continue;
			} else {
				retire = 1;
			}
		}
		node->destroy(node);
		list->live_count -= 1;
		node->prev->next = node->next;
		if (node->next != 0) {
			node->next->prev = node->prev;
		}
		if (list->cursor == node) {
			list->cursor = node->prev;
		}
		list->free_node(node);
		node = next;
	}
	return 1;
}
