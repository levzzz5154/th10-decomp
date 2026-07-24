#include "th10/game/pause_menu_reset.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {


// Lazy interpolator registration: bind the control pointer to the global
// frame-scale slot the first time the block is used.
void RegisterClock(RegisteredClock* registered, float* frame_scale) {
	if ((registered->flags & 1) == 0) {
		registered->clock.frame = 0;
		registered->clock.previous = (int)0xFFF0BDC1u;
		registered->clock.timer = 0.0f;
		registered->clock.control = frame_scale;
		registered->flags |= 1;
	}
}

} // namespace

// 0x00424D90 - pause menu interpolator reset: marks the menu active,
// registers the three timer blocks against the global frame scale and
// resets them to their initial values, releases the held script handle,
// and restarts the menu music.
void PauseMenu_ResetTimers(PauseMenu* menu, PauseResetEnv* env) {
	menu->active = 1;
	RegisterClock(&menu->fade, env->frame_scale);
	menu->fade.clock.frame = -1;
	menu->fade.clock.timer = -1.0f;
	menu->fade.clock.previous = -2;
	RegisterClock(&menu->cursor, env->frame_scale);
	menu->cursor.clock.frame = 0;
	menu->cursor.clock.timer = 0.0f;
	menu->cursor.clock.previous = -1;
	RegisterClock(&menu->slide, env->frame_scale);
	menu->slide.clock.frame = 0;
	menu->slide.clock.timer = 0.0f;
	menu->slide.clock.previous = -1;
	env->release_script(env->frame_scale, env->state_manager,
	                    menu->script_handle);
	menu->script_handle = 0;
	env->play_music(env->music_track);
}
