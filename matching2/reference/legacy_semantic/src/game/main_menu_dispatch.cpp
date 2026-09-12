#include "th10/game/main_menu_dispatch.hpp"
#include "th10/game/result_choice_menu.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/result_menu_draw.hpp"
#include "th10/game/game_thread_queue.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/runtime/missing_edge.hpp"

#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

extern unsigned int DAT_00491be4;
extern unsigned int DAT_00477810;
extern unsigned int DAT_00474ca0;
extern unsigned int DAT_00474e36;
extern unsigned int DAT_00474e30;
extern unsigned int DAT_00491ff4;
// The submenu update (0x004236F0) globals: the byte input twin, the
// pressed-edge source, the difficulty, the highscore and the mode latch.
extern unsigned int byte_474E34;
extern unsigned int DAT_00474e30;
extern unsigned int DAT_00474c7c;
extern unsigned int DAT_00474c44;
extern unsigned int DAT_00491fb8;
extern float DAT_00476f78;
extern float _DAT_00470b68;
extern float _DAT_00470b64;
// Retail game-state/thread arena (dword_4776E8). The result-menu draw reads
// the render color/busy slots at +0x8974/+0x8988 off it, and the score UI
// release flag at +0x2A18.
extern unsigned int DAT_004776e8;
// Retail selected replay slot; the payload pointer sits at +0x18.
extern unsigned int DAT_00477838;
// Retail ranking character/stage/difficulty and label-mode globals.
extern unsigned int DAT_00474c68;
extern unsigned int DAT_00474c6c;
extern unsigned int DAT_00474c74;
extern unsigned int DAT_0047783c;
// Retail animation-manager arena (HUD score handle at +0x9EC8).
extern unsigned int DAT_0047770c;
// Retail sound-object global; the pause sound call passes its address.
extern unsigned int DAT_00492590;
extern void* g_pGameStateManager;

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

// Retail 0x00422660 feeds each row's timestamp to _localtime and formats
// year/month/day; ResultDrawDate carries the full year (renderer emits
// year % 100).
ResultDrawDate DecodeResultMenuDate(int timestamp) {
	std::time_t time_value = (std::time_t)timestamp;
	std::tm* local = std::localtime(&time_value);
	ResultDrawDate date = {local->tm_year + 1900, local->tm_mon + 1,
	                       local->tm_mday};
	return date;
}

// Retail text rendering goes through 0x00401630 (GameThread_AppendFormatted):
// sub_401530 copies the record x/y/z from a register vector and the color
// from the game-state +0x8974 slot (the env's render->color). The recovery
// models that register vector as the function's vector argument, so the
// callback forwards the draw point through it.
void ResultMenuDrawText(const ResultDrawPoint* point, const char* text) {
	GameThreadQueueWord vector[3];
	std::memcpy(&vector[0], &point->x, sizeof(vector[0]));
	std::memcpy(&vector[1], &point->y, sizeof(vector[1]));
	std::memcpy(&vector[2], &point->z, sizeof(vector[2]));
	GameThread_AppendFormatted((GameThread*)(uintptr_t)DAT_004776e8, vector,
	                           "%s", text);
}

// 0x00422660 - replay/name-entry/score-ranking result-menu draw. The retail
// body brackets every state with the busy/color slots at game-state
// +0x8988/+0x8974 and renders text through the 0x00401630 formatter
// (GameThread_AppendFormatted), whose sub_401530 copies the position vector
// out of EBX - modeled as the recovery's draw_text(point, text) callback.
int __fastcall MenuTimerRuntime_DrawCallback(void* owner) {
	ResultDrawEnv env = {};
	env.render = (ResultDrawState*)((char*)(uintptr_t)DAT_004776e8 + 0x8974);
	// Retail 0x00422660 state 12/19 computes score-row addresses as
	// record*0x437C + difficulty*0xF0 + i*0x18 + 0x28 + mode with a base
	// pointer the raw pseudocode elides; no tree global names that base.
	env.score_file = 0;
	// RankingGlobals mirrors the retail character/stage/difficulty/mode
	// reads at DAT_00474C68, DAT_00474C6C, DAT_00474C74, DAT_0047783C.
	RankingGlobals globals = {(int)DAT_00474c68, (int)DAT_00474c6c,
	                          (int)DAT_00474c74, (int)DAT_0047783c};
	env.globals = &globals;
	// selected_replay: retail payload pointer behind DAT_00477838 (+0x18).
	env.selected_replay = (const ResultReplayInfo*)(
	    *(void**)((char*)(uintptr_t)DAT_00477838 + 0x18));
	// The character/shot, difficulty, stage and score-stage label tables are
	// passed to the 0x00401630 formatter as varargs in the retail body; the
	// raw pseudocode does not expose their global addresses and no tree
	// declaration exists. Left 0.
	env.character_shot_labels = 0;
	env.difficulty_labels = 0;
	env.stage_labels = 0;
	env.score_stage_labels = 0;
	// decode_date: retail formats dates through _localtime on the payload
	// timestamp; the adapter below is the direct CRT mapping.
	env.decode_date = DecodeResultMenuDate;
	// draw_text: retail appends via 0x00401630 at the record position.
	env.draw_text = ResultMenuDrawText;
	// draw_name_grid: 0x004224C0 was recovered under a different contract
	// (NameEntry_DrawCharGrid with a NameGridEnv); no clean binding.
	env.draw_name_grid = 0;
	return ResultMenu_DrawReplayAndRanking((ResultMenuView*)owner, &env);
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
	// The pause/sub-menu edges are wired to the reconstructions (0x00422C80,
	// 0x004236F0); the legacy handler parameters stay for the call sites.
	(void)run_pause_menu;
	(void)run_sub_menu;
	if (state == 0) {
		if (skip_demo_config == 0 && demo_input_pressed != 0 &&
		    replay_ready != 0 && frame_count > 0x1D) {
			if (open_game_menu == 0) {
				// 0x00422AB0 - PauseMenu_Open with the retail-global env.
				PauseOpenEnv env = {};
				// Retail: (DAT_00477810 + 0x58) |= 0x10.
				env.common.supervisor_flags =
				    (Word*)((char*)(uintptr_t)DAT_00477810 + 0x58);
				// The effect/script/sound edges have no clean host binding:
				// acquire_effect (0x00449950), assign_script (0x00449870),
				// register_front (0x00448AC0), position_window (0x00424480),
				// play_sound (0x0043DC90), play_named_sound (0x0043E460),
				// capture_background (0x0040C4D0), release_script (0x004497D0)
				// are exact-overlay or differently-contracted recoveries, so
				// the callbacks stay 0.
				env.common.manager = g_pGameStateManager;
				// Retail: HUD score handle at (DAT_0047770C + 0x9EC8).
				env.common.hud_score_handle =
				    (Word*)((char*)(uintptr_t)DAT_0047770c + 0x9ec8);
				// Retail: clock control and speed both live at DAT_00476F78.
				env.common.global_speed = &DAT_00476f78;
				env.common.frame_scale = &DAT_00476f78;
				// Retail: pause sound plays on the object at DAT_00492590.
				env.sound_manager = (void*)&DAT_00492590;
				// Retail: active script slot at (DAT_00477810 + 0x5C).
				env.active_script_slot =
				    (Word*)((char*)(uintptr_t)DAT_00477810 + 0x5c);
				PauseMenu_Open((OverlayMenu*)context, &env);
			} else {
				open_game_menu(context);
			}
		}
	} else if (state >= 1 && state <= 5) {
		// 0x00422C80 - pause/result menu update (the semantic model in
		// result_choice_menu.cpp; the ops hooks are wired by the
		// standalone - null hooks elide the side effects).  The menu
		// record carries the continue state at +484 (the submenu flag).
		ResultChoiceState* rc = (ResultChoiceState*)context;
		ResultChoiceInput in;
		in.held = DAT_00474e36;
		in.pressed = DAT_00474e30;
		ResultChoiceEnv env;
		env.continue_used = *(int*)((char*)context + 484) != 0;
		env.launch_state = 0;
		ResultChoiceOps ops = {};
		ops.context = context;
		ResultChoiceMenu_Update(rc, &in, &env, &ops);
	} else if (state >= 6 && state <= 0xD) {
		// 0x004236F0 - replay/result submenu update (full reconstruction).
		// The env carries the retail globals; the callee twins (sound,
		// sprite select, task management, replay I/O) are wired by the
		// standalone - null hooks are elided and the record mirrors stay
		// authoritative.
		SubmenuEnv env;
		env.game_state = (void*)(uintptr_t)DAT_004776e8;
		env.name_table = (void*)(uintptr_t)DAT_0047783c;
		env.input = DAT_00474e36;
		env.input_byte = byte_474E34;
		env.pressed = DAT_00474e30;
		env.difficulty = DAT_00474c7c;
		env.stage = DAT_00474c68;
		env.mode = DAT_00474c6c;
		env.subslot = DAT_00474c74;
		env.highscore = DAT_00474c44;
		env.flags_ca0 = DAT_00474ca0;
		env.mode_latch = (int*)&DAT_00491fb8;
		RunSubmenuUpdate(context, env);
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

// Full reconstruction of retail 0x004236F0 (replay/result submenu update).
// The menu record is the retail a1; every branch is byte-grounded from the
// retail body.  Record offsets: +4 state, +16 position floats, +20 timer,
// +36 selection, +40 previous selection, +44 wrap base, +244 flag,
// +252/+256 name cursor + previous, +260 name length, +460 flag,
// +468 task handle, +480 name length counter, +484/+488 flags,
// +492..+592 the 25 replay handles, +692 the 8-char name buffer.
// The env carries the retail globals and the recovered callee twins.
int RunSubmenuUpdate(void* ctx, const SubmenuEnv& env) {
	unsigned char* a1 = (unsigned char*)ctx;
	int* st = (int*)(a1 + 4);
	int* timer = (int*)(a1 + 20);
	int* sel = (int*)(a1 + 36);
	int* prev = (int*)(a1 + 40);
	int* wrap_base = (int*)(a1 + 44);
	int* f244 = (int*)(a1 + 244);
	int* cursor = (int*)(a1 + 252);
	int* prev_cursor = (int*)(a1 + 256);
	int* name_len = (int*)(a1 + 260);
	int* f460 = (int*)(a1 + 460);
	int* nlen = (int*)(a1 + 480);
	int* f484 = (int*)(a1 + 484);
	int* f488 = (int*)(a1 + 488);
	int* replay = (int*)(a1 + 492);
	char* name = (char*)(a1 + 692);
	int result = *st - 6;
	// The keyboard grid length (retail strlen(off_4746D8[0])).
	int chars_len = env.chars ? (int)std::strlen(env.chars) : 0;
	switch (*st) {
	case 6:
		// confirm gate: timer >= 10 + the 0x1001 mask -> sound 10, state 7
		if (*timer >= 10 && (env.input & 0x1001) != 0) {
			if (env.sound) env.sound(10);
			*st = 7;
			if (env.select_sprite) env.select_sprite(a1 + 468, 0, 2);
			if (env.position_reset) env.position_reset((float*)(a1 + 16));
			return 0;
		}
		return result;
	case 7:
		if (*timer < 10) return result;
		if (env.stage_reset) env.stage_reset();
		if ((env.flags_ca0 & 0x10) != 0) {
			// the ranking gate: highscore write into the name-table slot
			if (env.name_table) {
				unsigned char* v4 = (unsigned char*)env.name_table
				    + 34552 * env.stage + 17276 * env.stage + 17276 * env.mode
				    + 48 * env.subslot + 8 * env.difficulty + 1244;
				if (env.highscore > *(int*)v4) *(int*)v4 = env.highscore;
			}
		} else {
			if (env.name_entry) env.name_entry(a1);
			if (env.position_reset) env.position_reset((float*)(a1 + 16));
			if (!*f488) {
				*st = 12;
				if (env.task_remove) env.task_remove(a1 + 468);
				return 0;
			}
		}
		*st = 8;
		*wrap_base = 3;
		*f244 = 1;
		*sel = *wrap_base ? (*wrap_base > 2 ? 2 : *wrap_base - 1) : 2;
		if (env.task_register) env.task_register(a1 + 468, a1);
		if (env.select_sprite) env.select_sprite(a1 + 468, 0, *(short*)(a1 + 36) + 7);
		return 0;
	case 8: {
		*prev = *sel;
		if ((env.input & 0x10) != 0 || (env.input_byte & 0x10) != 0)
			if (env.wrap) env.wrap(sel, -1);
		if ((env.input & 0x20) != 0 || (env.input_byte & 0x20) != 0)
			if (env.wrap) env.wrap(sel, 1);
		result = *sel;
		if (*prev != *sel) {
			if (env.select_sprite) env.select_sprite(a1 + 468, 0, *sel + 7);
			if (env.sound) env.sound(12);
		}
		if ((env.input & 0x1001) != 0) {
			if (env.find_sprite)
				env.find_sprite(*prev, *sel + 124, (int*)(a1 + 52), a1 + 468);
			if (env.confirm_action) env.confirm_action(0, 0);
			if (env.sound) env.sound(10);
			*st = 13;
			if (env.position_reset) env.position_reset((float*)(a1 + 16));
			if (env.stage_reset) env.stage_reset();
			if (*sel == 1) {
				*st = 10;
				if (env.position_reset) env.position_reset((float*)(a1 + 16));
				if (env.task_remove) env.task_remove(a1 + 468);
				if (env.cursor_set) env.cursor_set(sel);
				*wrap_base = 25;
				*f244 = 1;
				*cursor = *wrap_base ? (*wrap_base > 0 ? 0 : *wrap_base - 1) : 0;
				for (int n = 1; n <= 25; ++n) {
					char buffer[64];
					std::snprintf(buffer, sizeof(buffer), "th10_%.2d.rpy", n);
					replay[n - 1] = env.replay_check ? env.replay_check(buffer) : 0;
				}
			} else if (*sel == 2) {
				*st = 13;
				if (env.position_reset) env.position_reset((float*)(a1 + 16));
				if (env.sound) env.sound(10);
			}
		}
		if ((env.input & 0xA) != 0) {
			if (env.sound) env.sound(11);
			if (*sel != 2) {
				*wrap_base = *f244;
				*sel = *wrap_base ? (*wrap_base > 2 ? 2 : *wrap_base - 1) : 2;
				if (env.select_sprite)
					env.select_sprite(a1 + 468, 0, *(short*)(a1 + 36) + 7);
			}
		}
		return result;
	}
	case 0xA:
		if (*timer < 10) return result;
		*prev = *sel;
		if (env.pressed_edge && env.pressed_edge(0x10))
			if (env.wrap) env.wrap(sel, -1);
		if (env.pressed_edge && env.pressed_edge(0x20))
			if (env.wrap) env.wrap(sel, 1);
		if (*prev != *sel)
			if (env.sound) env.sound(12);
		result = (int)env.input;
		if ((env.input & 0x1001) != 0) {
			*st = 11;
			if (env.position_reset) env.position_reset((float*)(a1 + 16));
			*cursor = *name_len ? (*name_len > 0 ? 0 : *name_len - 1) : 0;
			*name_len = chars_len;
			*f460 = 1;  // retail: *(a1+460) = 1
			if (env.game_state) {
				// Block: time() into Block[6]+12; the player record at
				// Block+24 gets the difficulty (or 8) at +92.
				unsigned char* block = (unsigned char*)env.game_state;
				unsigned char* player = *(unsigned char**)(block + 24);
				if (player) *(int*)(player + 92) =
				    (!*f484 || (env.flags_ca0 & 0x10) != 0)
				        ? env.difficulty : 8;
			}
			// name copy from the table at dword_47783C + 120952
			if (env.name_table) {
				const char* src = (const char*)env.name_table + 120952;
				for (int i = 0; src[i]; ++i) name[i] = src[i];
			}
			*nlen = 0;
			if (std::strcmp(name, "        ") != 0)
				if (env.wrap) env.wrap(cursor, -1);
			int i = 8;
			while (i > 0 && *(unsigned char*)(i + a1 + 691) == 32) --i;
			*nlen = i;
			if (env.sound) env.sound(10);
		}
		if ((env.input & 0xA) != 0) {
			*st = 8;
			if (env.position_reset) env.position_reset((float*)(a1 + 16));
			if (env.task_remove) env.task_remove(a1 + 468);
			if (env.cursor_set) env.cursor_set(sel);
			*wrap_base = 3;
			*f244 = 1;
			*sel = *wrap_base ? (*wrap_base > 2 ? 2 : *wrap_base - 1) : 2;
			if (env.select_sprite)
				env.select_sprite(a1 + 468, 0, *(short*)(a1 + 36) + 7);
			for (int n = 0; n < 25; ++n) {
				if (replay[n]) {
					if (env.replay_release) env.replay_release((void*)(uintptr_t)replay[n]);
					if (env.free) env.free((void*)(uintptr_t)replay[n]);
				}
				replay[n] = 0;
			}
			*st = 8;
			if (env.position_reset) env.position_reset((float*)(a1 + 16));
			if (env.sound) env.sound(11);
		}
		return result;
	case 0xB:
		if (*timer < 10) return result;
		*prev_cursor = *cursor;
		if (env.pressed_edge && env.pressed_edge(0x10))
			if (env.wrap) env.wrap(cursor, -13);
		if (env.pressed_edge && env.pressed_edge(0x20))
			if (env.wrap) env.wrap(cursor, 13);
		if (env.pressed_edge && env.pressed_edge(0x40)) {
			if (*cursor % 13) env.wrap(cursor, -1);
			else env.wrap(cursor, 12);
		}
		if (env.pressed_edge && env.pressed_edge(0x80)) {
			if (*cursor % 13 == 12) env.wrap(cursor, -12);
			else env.wrap(cursor, 1);
		}
		if (*prev_cursor != *cursor)
			if (env.sound) env.sound(12);
		if ((env.input & 0x1001) != 0) {
			int v36 = *cursor;
			if (v36 < chars_len - 3) {
				if (*nlen >= 8) *(unsigned char*)(*nlen + a1 + 691) =
				    (unsigned char)env.chars[v36];
				else *(unsigned char*)(*nlen + a1 + 692) =
				    (unsigned char)env.chars[v36];
				++*nlen;
				// the visible-boundary clamp (retail __OFSUB__(nlen, 8))
				if (*nlen - 8 >= 0 && env.clamp) env.clamp(chars_len - 1, cursor);
			} else if (v36 == chars_len - 3) {
				if (*nlen >= 8) *(unsigned char*)(*nlen + a1 + 691) = 32;
				else *(unsigned char*)(*nlen + a1 + 692) = 32;
				++*nlen;
				if (*nlen - 8 >= 0 && env.clamp) env.clamp(chars_len - 1, cursor);
			} else if (v36 == chars_len - 2) {
				if (*nlen) {
					--*nlen;
					*(unsigned char*)(*nlen + a1 + 692) = 32;
					if (env.sound) env.sound(11);
					return 0;
				}
			} else if (v36 == chars_len - 1) {
				// the save column: sound 44, write th10_XX.rpy
				if (env.sound) env.sound(44);
				char buffer[64];
				std::snprintf(buffer, sizeof(buffer), "th10_%.2d.rpy", *sel + 1);
				if (env.replay_write)
					env.replay_write((void*)(uintptr_t)replay[*sel], buffer, name);
				replay[*sel] = env.replay_check ? env.replay_check(buffer) : 0;
				*st = 10;
				if (env.position_reset) env.position_reset((float*)(a1 + 16));
				if (env.name_table) {
					char* src = (char*)env.name_table + 120260;
					for (int i = 0; name[i]; ++i) src[i] = name[i];
				}
				return 0;
			}
			if (env.sound) env.sound(10);
		}
		if ((env.input & 0xA) != 0) {
			if (env.sound) env.sound(11);
			if (*nlen) {
				--*nlen;
				*(unsigned char*)(*nlen + a1 + 692) = 32;
			} else {
				*st = 10;
				if (env.position_reset) env.position_reset((float*)(a1 + 16));
			}
		}
		return result;
	case 0xC:
		if (*timer < 10) return result;
		if (!*f488) {
			*prev_cursor = *cursor;
			if (env.pressed_edge && env.pressed_edge(0x10))
				if (env.wrap) env.wrap(cursor, -13);
			if (env.pressed_edge && env.pressed_edge(0x20))
				if (env.wrap) env.wrap(cursor, 13);
			if (env.pressed_edge && env.pressed_edge(0x40)) {
				if (*cursor % 13) env.wrap(cursor, -1);
				else env.wrap(cursor, 12);
			}
			if (env.pressed_edge && env.pressed_edge(0x80)) {
				if (*cursor % 13 == 12) env.wrap(cursor, -12);
				else env.wrap(cursor, 1);
			}
			if (*prev_cursor != *cursor)
				if (env.sound) env.sound(12);
		}
		if ((env.input & 0x1001) != 0) {
			if (!*f488) {
				int v50 = *cursor;
				if (v50 >= chars_len - 3) {
					if (v50 != chars_len - 3) {
						if (v50 == chars_len - 2) {
							if (*nlen) {
								--*nlen;
								*(unsigned char*)(*nlen + a1 + 692) = 32;
							}
						} else if (v50 == chars_len - 1) {
							// the select column: save the name into the
							// slot table (dword_47783C + 34552*stage +
							// 17276*stage + 17276*mode + 240*subslot +
							// 24*selection + 30)
							if (env.name_table) {
								char* dst = (char*)env.name_table
								    + 34552 * env.stage + 17276 * env.stage
								    + 17276 * env.mode + 240 * env.subslot
								    + 24 * *sel + 30;
								std::strcpy(dst, name);
								const char* src2 = name;
								char* dst2 = (char*)env.name_table + 120260;
								for (int i = 0; src2[i]; ++i) dst2[i] = src2[i];
							}
							if (env.task_remove) env.task_remove(a1 + 468);
							*st = 8;
							*wrap_base = 3;
							*f244 = 1;
							*sel = *wrap_base ? (*wrap_base > 0 ? 0 : *wrap_base - 1) : 0;
							if (env.task_register) env.task_register(a1 + 468, a1);
							if (env.select_sprite)
								env.select_sprite(a1 + 468, 0, *(short*)(a1 + 36) + 7);
						}
						goto LABEL_155;
					}
					// the space column (chars_len - 3)
					if (*nlen >= 8) *(unsigned char*)(*nlen + a1 + 691) = 32;
					else *(unsigned char*)(*nlen + a1 + 692) = 32;
					++*nlen;
					if (*nlen - 8 >= 0 && env.clamp) env.clamp(chars_len - 1, cursor);
					goto LABEL_155;
				}
				// the character columns
				if (*nlen >= 8) *(unsigned char*)(*nlen + a1 + 691) =
				    (unsigned char)env.chars[v50];
				else *(unsigned char*)(*nlen + a1 + 692) =
				    (unsigned char)env.chars[v50];
				++*nlen;
				if (*nlen - 8 >= 0 && env.clamp) env.clamp(chars_len - 1, cursor);
LABEL_155:
				if (env.sound) env.sound(10);
			} else {
				// the 488-armed path: task removal + selection reset
				if (env.task_remove) env.task_remove(a1 + 468);
				*st = 8;
				*wrap_base = 3;
				*f244 = 1;
				*sel = *wrap_base ? (*wrap_base > 0 ? 0 : *wrap_base - 1) : 0;
				if (env.task_register) env.task_register(a1 + 468, a1);
				if (env.select_sprite)
					env.select_sprite(a1 + 468, 0, *(short*)(a1 + 36) + 7);
			}
		}
		if ((env.input & 0xA) != 0) {
			if (*sel < 0) {
				*st = 8;
				*wrap_base = 3;
				*sel = *wrap_base >= 0 ? 0 : *wrap_base - 1;
				if (env.position_reset) env.position_reset((float*)(a1 + 16));
				if (env.sound) env.sound(10);
			} else if (*nlen) {
				if (env.sound) env.sound(11);
				--*nlen;
				*(unsigned char*)(*nlen + a1 + 692) = 32;
			}
		}
		return result;
	case 0xD:
		if (*timer >= 12) {
			if (env.teardown) env.teardown(a1);
			result = *sel;
			*st = 21;
			if (*sel) {
				if (*sel - 1 == 0) {
					// retail: sub_40AC90(&dword_491C28, 4) - the hook drops the
				// unmappable global address
				if (env.set_mode) env.set_mode(0, 4);
					return 0;
				}
				if (*sel - 2 == 0) {
					// retail: sub_40AC90(&dword_491C28, 4) - the hook drops the
				// unmappable global address
				if (env.set_mode) env.set_mode(0, 4);
					return 0;
				}
			} else {
				if (env.mode_latch) *env.mode_latch = *f484 != 0 ? 10 : 13;
			}
		}
		return result;
	default:
		return result;
	}
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
