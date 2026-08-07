#pragma once

// Main menu state dispatch (retail 0x004223F0).
#include <cstdint>

#include "th10/game/player_motion.hpp"

// --- 0x004223F0 --------------------------------------------------------------
int MainMenu_DispatchState(void* context, int state, int skip_demo_config,
                           int demo_input_pressed, int replay_ready,
                           int frame_count, void (*open_game_menu)(void*),
                           void (*run_pause_menu)(void*),
                           void (*run_sub_menu)(void*),
                           PlayerDeathClock* clock, float span_low,
                           float span_high, float frame_step,
                           long long (*float_to_long)(float value));

struct MenuTimerRuntimeBindings {
	void (*open_game_menu)(void*);
	void (*run_pause_menu)(void*);
	void (*run_sub_menu)(void*);
	int (*draw_menu)(void*);
};

void MenuTimerRuntime_SetBindings(const MenuTimerRuntimeBindings* bindings);
int MenuTimerRuntime_Initialize(void* state);

// 0x004236F0 - Replay/result submenu update (the menu record is the retail
// a1; raw record offsets: +4 state, +16 position floats, +20 timer,
// +36 selection, +40 previous selection, +44 wrap base, +244 flag,
// +252/+256 name cursor + previous, +260 name length, +460 flag,
// +468 task handle, +480 name length counter, +484/+488 flags,
// +492..+592 the 25 replay handles, +692 the 8-char name buffer).
// Side effects route through the env (the recovered callee twins); null
// hooks are elided and the record mirrors stay authoritative.
struct SubmenuEnv {
	void* game_state{};        // Block (dword_4776E8)
	void* name_table{};        // dword_47783C (the 120952/120260 name slots)
	uint32_t input{};          // dword_474E36
	uint32_t input_byte{};     // byte_474E34 (the byte twin of the input masks)
	uint32_t pressed{};        // dword_474E30 (the pressed-edge source)
	int difficulty{};          // dword_474C7C
	int stage{};               // dword_474C68
	int mode{};                // dword_474C6C
	int subslot{};             // dword_474C74
	int highscore{};           // dword_474C44
	int flags_ca0{};           // dword_474CA0 (bit 0x10 = the ranking gate)
	int* mode_latch{};         // dword_491FB8 (write-back mirror; null = elided)
	const char* chars{};       // off_4746D8[0] (the keyboard table)
	void (*sound)(int){};                       // sub_43DC90
	void (*position_reset)(float*){};           // sub_405410
	void (*stage_reset)(){};                    // sub_421F60
	void (*name_entry)(void*){};                // sub_423570
	void (*task_remove)(void*){};               // sub_4495E0
	void (*task_register)(void*, void*){};      // sub_40C4D0
	void (*select_sprite)(void*, void*, int){}; // sub_449470
	void (*wrap)(int*, int){};                  // sub_44BEA0
	void (*cursor_set)(int*){};                 // sub_44BE20
	int (*find_sprite)(int, int, int*, void*){};// sub_4497D0
	void (*confirm_action)(void*, void*){};     // sub_4243F0
	int (*pressed_edge)(unsigned int){};        // sub_40ACE0
	int (*replay_check)(const char*){};         // sub_4296F0
	void (*replay_release)(void*){};            // sub_4294A0
	void (*replay_write)(void*, const char*, const char*){}; // sub_429B60
	void (*teardown)(void*){};                  // sub_423510
	void (*set_mode)(int, int){};               // sub_40AC90
	void (*clamp)(int, int*){};                 // sub_40AD20
	void (*free)(void*){};                      // j__free
};
int RunSubmenuUpdate(void* ctx, const SubmenuEnv& env);
