#include "th10/game/result_menu_open.hpp"
#include "th10/render/projection_quads.hpp"

#include <cmath>
#include <cstring>

namespace {

void ResetMenuClock(ResultMenu* menu, float* scale) {
	if ((menu->clock_flags & 1u) == 0) {
		menu->clock_frame=0; menu->clock_previous=(int)0xFFF0BDC1u;
		menu->clock_timer=0; menu->clock_control=scale; menu->clock_flags|=1u;
	}
	menu->clock_frame=0; menu->clock_timer=0; menu->clock_previous=-1;
}
}

// 0x00423370 - opens the recovered result menu, including its supervisor-only
// shortcut, paired effects, window descriptor, BGM/sound setup, seen marker,
// and temporary normalization of the global frame scale.
void ResultMenu_OpenRecovered(ResultMenu* menu,
                              ResultMenuEnv* env) {
	if (env->supervisor_mode == 1) {
		*env->supervisor_result_state = (env->input_flags & 0x1000u) ? 2 : 4;
		return;
	}
	menu->state = 6; ResetMenuClock(menu, env->frame_scale);
	env->set_supervisor_flag(0x10u);
	int effect = env->create_effect(0, 0xF); env->register_effect(effect);
	menu->primary_owner = effect;
	env->position_window(effect, 0x20, 0x10, 0x180, 0x1C0);
	menu->selected_handle = env->selected_handle;
	effect = env->create_effect(0x81, 0xF); env->register_effect(effect);
	menu->secondary_owner = effect;
	env->play_bgm("bgm/th10_17.wav");
	if (env->extra_sound_enabled) env->load_sound("dummy", 4);
	env->load_sound("dummy", 2);
	env->mark_result_seen();
	menu->active = 1;
	menu->saved_frame_scale = *env->frame_scale;
	*env->frame_scale = 1.0f;
}
