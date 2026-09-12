#include "th10/game/ending_screen.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x0042D300 - ending screen state dispatch: state 0 loads the background
// texture, samples the text color, and clamps the pending delay before
// falling through to the frame-count check; state 2 waits for input to end
// the ending; state 4 pops back to the previous menu after half a second.
int EndingState_Dispatch(EndingScreen* screen, EndingEnv* env) {
	switch (screen->state) {
	case 0:
		if (env->load_background(env->state_manager, screen->script_id) == 0) {
			env->advance_script(screen);
			env->advance_script(screen);
			screen->color = *env->sample_color(screen->text_page, 0, 0xF);
		}
		env->set_state(1);
		if (screen->pending_delay == 0) {
			screen->state_timer = 0;
		} else if (screen->pending_delay < 1) {
			screen->state_timer = screen->pending_delay - 1;
		} else {
			screen->state_timer = 0;
		}
		[[fallthrough]];
	case 1:
		if (10 < screen->frame) {
			env->set_state(2);
			return 1;
		}
		break;
	case 2:
		if ((env->input_flags & 0x160B) != 0) {
			env->play_sound(0x5A);
			env->set_state(4);
			env->stop_music(env->music_channel, 0);
			env->begin_fade_out();
			return 1;
		}
		break;
	case 3:
		break;
	case 4:
		if (0x1D < screen->frame) env->pop_state(2);
		break;
	default:
		break;
	}
	return 1;
}
