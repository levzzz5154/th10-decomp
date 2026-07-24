#pragma once

#include <cstddef>

// Requested/current game-mode transition serializer (retail 0x004218D0).
// --- 0x004218D0: apply a requested high-level game mode ---------------------
enum GameMode {
	kGameModeBoot = 0,
	kGameModeLoading = 1,
	kGameModeFailure = 3,
	kGameModeMenu = 4,
	kGameModeGameplay = 7,
	kGameModeResults = 10,
	kGameModeReplay = 11,
	kGameModeRestart = 12,
	kGameModeReturn = 13,
	kGameModeCleanup = 14,
	kGameModeExit = 15,
};

struct GameModeState {
	int requested;       // retail +0x38C
	int current;         // retail +0x390
	int previous_request;// retail +0x394
	int gameplay_variant;// retail +0x39C
	unsigned int fade_color; // retail +0x780
	void* loading_owner; // retail +0x768
	unsigned char critical_depth; // retail +0x6F9
};

struct GameModeEnv {
	void (*enter_critical)();
	void (*leave_critical)();
	void* (*create_loading_owner)();
	void (*show_failure)();
	void (*finalize_failure)();
	void (*leave_gameplay)();
	void (*enter_gameplay)();
	void (*release_bullets)();
	void (*prepare_restart)();
	void (*prepare_cleanup)();
	void (*commit_menu)();
	int selected_difficulty;
	int* active_difficulty;
	const void* difficulty_table;
	std::size_t difficulty_stride;
	const void** active_difficulty_record;
	int* exit_reason;
};

int GameMode_ApplyRequested(GameModeState* state, GameModeEnv* env);
