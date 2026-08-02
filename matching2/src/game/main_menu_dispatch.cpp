#include "th10/game/main_menu_dispatch.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstring>

extern unsigned int DAT_00491be4;
extern unsigned int DAT_00477810;
extern unsigned int DAT_00474ca0;
extern unsigned int DAT_00474e36;
extern unsigned int DAT_00491ff4;
extern float DAT_00476f78;
extern float _DAT_00470b68;
extern float _DAT_00470b64;

namespace {
MenuTimerRuntimeBindings g_menu_timer_bindings = {};

long long TruncateMenuClock(float value) {
	return (long long)value;
}

int __fastcall MenuTimerRuntime_UpdateCallback(void* owner) {
	unsigned char* bytes = (unsigned char*)owner;
	const int state = *(int*)(bytes + 4);
	int replay_ready = 0;
	if (DAT_00477810 != 0) {
		unsigned char* replay = reinterpret_cast<unsigned char*>(
		    static_cast<uintptr_t>(DAT_00477810));
		unsigned int callback = *(unsigned int*)(replay + 8);
		replay_ready = callback != 0 &&
		    (*reinterpret_cast<unsigned char*>(
		         static_cast<uintptr_t>(callback + 4)) &
		     2u) != 0;
	}
	const int demo_input =
	    (DAT_00474e36 & 8u) != 0 || (DAT_00491ff4 & 0x10u) != 0;
	PlayerDeathClock* clock = (PlayerDeathClock*)(bytes + 0x10);
	return MainMenu_DispatchState(
	    owner, state, (DAT_00474ca0 & 0x20u) != 0, demo_input,
	    replay_ready, clock->frame, g_menu_timer_bindings.open_game_menu,
	    g_menu_timer_bindings.run_pause_menu,
	    g_menu_timer_bindings.run_sub_menu, clock, _DAT_00470b68,
	    _DAT_00470b64, 1.0f, TruncateMenuClock);
}

int __fastcall MenuTimerRuntime_DrawCallback(void* owner) {
	if (g_menu_timer_bindings.draw_menu == 0)
		Runtime_MissingEdge(0x00422660u, "result/menu draw");
	return g_menu_timer_bindings.draw_menu(owner);
}
}  // namespace

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
			if (open_game_menu == 0)
				Runtime_MissingEdge(0x00422AB0u, "pause/menu open");
			open_game_menu(context);
		}
	} else if (state >= 1 && state <= 5) {
		if (run_pause_menu == 0)
			Runtime_MissingEdge(0x00422C80u, "pause/result menu update");
		run_pause_menu(context);
	} else if (state >= 6 && state <= 0xD) {
		if (run_sub_menu == 0)
			Runtime_MissingEdge(0x004236F0u, "replay/result submenu update");
		run_sub_menu(context);
	}
	AdvanceFrameClock(clock, span_low, span_high, frame_step, float_to_long);
	return 1;
}

void MenuTimerRuntime_SetBindings(const MenuTimerRuntimeBindings* bindings) {
	if (bindings != 0)
		g_menu_timer_bindings = *bindings;
	else
		std::memset(&g_menu_timer_bindings, 0, sizeof(g_menu_timer_bindings));
}

// 0x00422150 - Install the update/draw pair and initialize the embedded
// frame clock at +0x10. The owner was published by 0x004220E0.
int MenuTimerRuntime_Initialize(void* state) {
	if (state == 0 || DAT_00491be4 == 0)
		return -1;
	unsigned char* bytes = (unsigned char*)state;
	SchedulerCallback* update =
	    SchedulerCallback_Create(MenuTimerRuntime_UpdateCallback);
	if (update == 0)
		return -1;
	update->flags &= ~2u;
	update->owner = state;
	Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
	*(SchedulerCallback**)(bytes + 8) = update;

	SchedulerCallback* draw =
	    SchedulerCallback_Create(MenuTimerRuntime_DrawCallback);
	if (draw == 0) {
		Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
		*(SchedulerCallback**)(bytes + 8) = 0;
		return -1;
	}
	draw->flags &= ~2u;
	draw->owner = state;
	Scheduler_RegisterSecondary(draw, 0, (void*)(uintptr_t)DAT_00491be4);
	*(SchedulerCallback**)(bytes + 12) = draw;

	unsigned int* flags = (unsigned int*)(bytes + 0x20);
	if ((*flags & 1u) == 0) {
		*(int*)(bytes + 0x14) = 0;
		*(int*)(bytes + 0x10) = (int)0xFFF0BDC1u;
		*(int*)(bytes + 0x18) = 0;
		*(unsigned int*)(bytes + 0x1C) =
		    (unsigned int)(unsigned long)&DAT_00476f78;
		*flags |= 1u;
	}
	*(int*)(bytes + 0x14) = 0;
	*(int*)(bytes + 0x18) = 0;
	*(int*)(bytes + 0x10) = -1;
	return 0;
}
