#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

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

// Shared body of the pause/result menu constructors: state, clock, the two
// interface effect VMs, and window placement.
void MenuOpenCommon(OverlayMenu* menu, int state, int secondary_script,
                    OverlayMenuEnv* env) {
	menu->state = state;
	ResetClock(&menu->clock, env->frame_scale);
	*env->supervisor_flags |= 0x10u;

	ResultEffectVm* vm = env->acquire_effect();
	vm->layer = 0xF;
	vm->flags |= 0x40000000u;
	env->assign_script(vm, 0);
	env->register_front(env->manager);
	menu->owner_primary = menu;

	env->position_window(menu, 0x20, 0x10, 0x180, 0x1C0);
	menu->hud_handle = *env->hud_score_handle;

	vm = env->acquire_effect();
	vm->layer = 0xF;
	vm->flags |= 0x40000000u;
	env->assign_script(vm, secondary_script);
	env->register_front(env->manager);
	menu->owner_secondary = menu;
}

} // namespace

// 0x00422AB0 - opens the pause menu: freezes the supervisor, spawns the two
// interface effects, captures the background, plays the pause sound, drops
// the active script, and forces the global speed to 1.
void PauseMenu_Open(OverlayMenu* menu, PauseOpenEnv* env) {
	MenuOpenCommon(menu, 1, 0x79, &env->common);

	env->capture_background();
	env->play_sound(env->sound_manager, 0);
	env->play_named_sound("Pause", 6, 0);

	if (*env->active_script_slot != 0) {
		env->release_script(env->common.manager, *env->active_script_slot);
		*env->active_script_slot = 0;
	}

	menu->saved_speed = *env->common.global_speed;
	*env->common.global_speed = 1.0f;
}

// 0x004231D0 - opens the result/continue menu. When a retry is already
// pending it only records the retry mode; otherwise it builds the menu,
// starts the staff-roll music, and marks the score file dirty.
void ResultMenu_Open(OverlayMenu* menu, ResultOpenEnv* env) {
	if (*env->pending_slot == 1) {
		*env->retry_mode_slot =
		    ((env->config_flags & 0x1000u) != 0) ? 2u : 4u;
		return;
	}

	MenuOpenCommon(menu, 6, 0x80, &env->common);

	env->play_music(0, "bgm/th10_17.wav");
	if ((env->sound_config & 0x10u) != 0) {
		env->play_named_sound("dummy", 4, 0);
	}
	env->play_named_sound("dummy", 2, 0);

	*env->score_dirty_flag = 1;
	menu->practice_flag = 0;
	menu->saved_speed = *env->common.global_speed;
	*env->common.global_speed = 1.0f;
}
