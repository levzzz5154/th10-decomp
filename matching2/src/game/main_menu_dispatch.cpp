#include "th10/game/main_menu_dispatch.hpp"
#include "th10/game/player_motion.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.

// Shared per-frame clock advance used by the update callbacks below. When
// the global frame-scale control sits inside the normal span the frame
// counter simply increments; otherwise the scaled control value is
// accumulated and the frame is re-derived by truncation.
static void AdvanceFrameClock(PlayerDeathClock* clock, float span_low,
                              float span_high, float frame_step,
                              long long (*float_to_long)(float value)) {
	float control = *clock->control;
	clock->previous = clock->frame;
	if (span_low < control && control < span_high) {
		clock->timer += frame_step;
		clock->frame += 1;
	} else {
		clock->timer += control;
		clock->frame = (int)float_to_long(clock->timer);
	}
}

// 0x004223F0 - Main menu state dispatcher. State 0 (title/demo) opens the
// game menu once demo input arrives with a ready replay past frame 0x1D and
// the config does not suppress it; states 1-5 run the pause-menu handler and
// states 6-13 the sub-menu handler. Always advances the menu frame clock.
int MainMenu_DispatchState(void* context, int state, int skip_demo_config,
                           int demo_input_pressed, int replay_ready,
                           int frame_count, void (*open_game_menu)(void*),
                           void (*run_pause_menu)(void*),
                           void (*run_sub_menu)(void*),
                           PlayerDeathClock* clock, float span_low,
                           float span_high, float frame_step,
                           long long (*float_to_long)(float value)) {
	if (state == 0) {
		if (skip_demo_config == 0 && demo_input_pressed != 0 &&
		    replay_ready != 0 && frame_count > 0x1D) {
			open_game_menu(context);
		}
	} else if (state >= 1 && state <= 5) {
		run_pause_menu(context);
	} else if (state >= 6 && state <= 0xD) {
		run_sub_menu(context);
	}
	AdvanceFrameClock(clock, span_low, span_high, frame_step, float_to_long);
	return 1;
}
