#include "th10/app/version_marker.hpp"
#include "th10/game/game_mode_switch.hpp"
#include "th10/game/stage_controller_tick.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

namespace {

bool g_probe_result;
bool Probe(const char* name) {
	assert(std::strcmp(name, "th10.ver") == 0);
	return g_probe_result;
}
unsigned char g_marker[3] = {1, 2, 3};
bool g_load_result;
std::string g_loaded_name;
unsigned char* Load(const char* name, std::size_t* size) {
	g_loaded_name = name;
	*size = g_load_result ? sizeof(g_marker) : 0;
	return g_load_result ? g_marker : 0;
}
std::string g_log;
void Log(const char* text) { g_log = text; }

void TestVersionMarkerLoad() {
	unsigned char* data = reinterpret_cast<unsigned char*>(1);
	std::size_t size = 99;
	VersionMarkerEnv env = {0x100, 'a', "probe missing", "load failed",
	                               Probe, Load, Log, &data, &size};
	g_probe_result = false;
	g_log.clear();
	assert(VersionMarker_Load(&env) == -1);
	assert(g_log == "probe missing");
	assert(data == reinterpret_cast<unsigned char*>(1));

	g_probe_result = true;
	g_load_result = false;
	g_log.clear();
	assert(VersionMarker_Load(&env) == -1);
	assert(g_loaded_name == "th10_0100a.ver");
	assert(data == 0 && size == 0 && g_log == "load failed");

	g_load_result = true;
	assert(VersionMarker_Load(&env) == 0);
	assert(data == g_marker && size == sizeof(g_marker));
}

int g_enter, g_leave, g_create, g_fail, g_finalize, g_left_game;
int g_entered_game, g_release, g_restart, g_cleanup, g_commit;
void Enter() { ++g_enter; }
void Leave() { ++g_leave; }
void* CreateOk() { ++g_create; return reinterpret_cast<void*>(0x1234); }
void* CreateFail() { ++g_create; return 0; }
void Fail() { ++g_fail; }
void Finalize() { ++g_finalize; }
void LeftGame() { ++g_left_game; }
void EnteredGame() { ++g_entered_game; }
void Release() { ++g_release; }
void Restart() { ++g_restart; }
void Cleanup() { ++g_cleanup; }
void Commit() { ++g_commit; }

GameModeEnv MakeModeEnv() {
	GameModeEnv env;
	std::memset(&env, 0, sizeof(env));
	env.enter_critical = Enter;
	env.leave_critical = Leave;
	env.create_loading_owner = CreateOk;
	env.show_failure = Fail;
	env.finalize_failure = Finalize;
	env.leave_gameplay = LeftGame;
	env.enter_gameplay = EnteredGame;
	env.release_bullets = Release;
	env.prepare_restart = Restart;
	env.prepare_cleanup = Cleanup;
	env.commit_menu = Commit;
	return env;
}
void ResetModeCalls() {
	g_enter = g_leave = g_create = g_fail = g_finalize = g_left_game = 0;
	g_entered_game = g_release = g_restart = g_cleanup = g_commit = 0;
}

void TestGameModeApplyRequested() {
	GameModeEnv env = MakeModeEnv();
	GameModeState state;
	std::memset(&state, 0, sizeof(state));

	state.requested = state.current = kGameModeMenu;
	assert(GameMode_ApplyRequested(&state, &env) == 1);
	assert(g_enter == 0);

	ResetModeCalls();
	state.requested = kGameModeGameplay;
	state.current = kGameModeBoot;
	assert(GameMode_ApplyRequested(&state, &env) == 1);
	assert(state.current == kGameModeLoading);
	assert(state.requested == kGameModeLoading);
	assert(state.loading_owner == reinterpret_cast<void*>(0x1234));
	assert(state.fade_color == 0xFF000000u);
	assert(g_enter == 1 && g_leave == 1 && state.critical_depth == 0);

	ResetModeCalls();
	env.create_loading_owner = CreateFail;
	state.requested = kGameModeGameplay;
	state.current = kGameModeBoot;
	assert(GameMode_ApplyRequested(&state, &env) == 4);
	assert(state.current == kGameModeFailure);
	assert(g_fail == 1 && g_finalize == 1);
	// The retail failure path returns before the common critical-section tail.
	assert(g_enter == 1 && g_leave == 0 && state.critical_depth == 1);

	ResetModeCalls();
	env = MakeModeEnv();
	int active_difficulty = -1;
	const void* active_record = 0;
	char table[4 * 48] = {};
	env.selected_difficulty = 2;
	env.active_difficulty = &active_difficulty;
	env.difficulty_table = table;
	env.difficulty_stride = 48;
	env.active_difficulty_record = &active_record;
	std::memset(&state, 0, sizeof(state));
	state.current = kGameModeResults;
	state.requested = kGameModeGameplay;
	assert(GameMode_ApplyRequested(&state, &env) == 1);
	assert(state.current == kGameModeGameplay && state.gameplay_variant == 1);
	assert(active_difficulty == 2 && active_record == table + 96);
	assert(g_left_game == 1 && g_entered_game == 1);

	ResetModeCalls();
	int exit_reason = 0;
	env.exit_reason = &exit_reason;
	state.current = kGameModeExit;
	state.requested = kGameModeCleanup;
	assert(GameMode_ApplyRequested(&state, &env) == 1);
	assert(state.current == kGameModeMenu && exit_reason == 3);
	assert(g_cleanup == 1 && g_commit == 1);
}

int g_camera, g_callbacks, g_spawns, g_flushes;
float g_effects[2];
void Camera(StageController*) { ++g_camera; }
void Callback(void* context) { g_callbacks += *static_cast<int*>(context); }
void Spawn(float value) { g_effects[g_spawns++] = value; }
void Flush() { ++g_flushes; }

void TestStageControllerTick() {
	StageController controller;
	std::memset(&controller, 0, sizeof(controller));
	controller.position = {10.0f, 20.0f, 30.0f};
	int one = 1, two = 2;
	controller.callbacks[0] = Callback;
	controller.callback_contexts[0] = &one;
	controller.callbacks[2] = Callback;
	controller.callback_contexts[2] = &two;

	StageControllerEnv env = {1.5f, -2.0f, true, 4.0f, -5.0f,
	                       Camera, Spawn, Flush};
	g_camera = g_callbacks = g_spawns = g_flushes = 0;
	assert(StageController_Tick(&controller, &env) == 1);
	assert(controller.projected.x == 11.5f);
	assert(controller.projected.y == 18.0f);
	assert(controller.projected.z == 30.0f);
	assert(g_camera == 1 && g_callbacks == 3);
	assert(g_spawns == 2 && g_effects[0] == 14.0f && g_effects[1] == 15.0f);
	assert(g_flushes == 2);

	controller.mode = 2;
	g_camera = g_callbacks = g_spawns = g_flushes = 0;
	assert(StageController_Tick(&controller, &env) == 1);
	assert(g_camera == 0 && g_callbacks == 0 && g_spawns == 0);
}

} // namespace

int main() {
	TestVersionMarkerLoad();
	TestGameModeApplyRequested();
	TestStageControllerTick();
	std::puts("BATCH12_TESTS_PASS");
	return 0;
}
