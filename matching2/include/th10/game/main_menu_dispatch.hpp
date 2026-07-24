#pragma once

// Main menu state dispatch (retail 0x004223F0).
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
