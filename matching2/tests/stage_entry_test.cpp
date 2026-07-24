// Tests for recovery batch 25 (0x00417870 stage entry, 0x004187C0 update
// thunk, 0x004187D0 camera-clear callback).
#include "th10/game/stage_entry.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>

static int g_failures = 0;
#define CHECK(condition)                                                     \
	do {                                                                     \
		if (!(condition)) {                                                  \
			std::printf("CHECK failed at line %d: %s\n", __LINE__,           \
			            #condition);                                         \
			++g_failures;                                                    \
		}                                                                    \
	} while (0)

// ---------------------------------------------------------------------------
// Recording hooks
// ---------------------------------------------------------------------------

static char g_log[1024];
static void Log(const char* text) {
	std::strncat(g_log, text, sizeof(g_log) - std::strlen(g_log) - 1);
}

static StageGlobals g_globals;
static unsigned char g_score_file[96 * 1024];
static unsigned char g_descriptor[52];
static StageRecord g_record;
static int g_scheduler_tag;
static int g_anm_tag;
static int g_game_tag;
static int g_spell_tag;
static int g_key_tag;
static int g_enemy_script_tag;

static int g_sleep_count_1ms;
static int g_sleep_count_16ms;
static int g_sync_decrement; // when set, 1 ms sleeps decrement sync[0]
static int g_loader_countdown; // when set, 16 ms sleeps decrement loader
static void HookSleep(unsigned int milliseconds) {
	if (milliseconds == 1) {
		++g_sleep_count_1ms;
		if (g_sync_decrement)
			g_globals.sync[0] -= 2;
	} else if (milliseconds == 16) {
		++g_sleep_count_16ms;
		if (g_loader_countdown && --g_globals.loader_busy < 0)
			g_globals.loader_busy = 0;
	}
}

static int* g_extend_target;
static int g_extend_amount;
static void HookSeedExtend(int* score_seed, int amount) {
	Log("extend;");
	g_extend_target = score_seed;
	g_extend_amount = amount;
}

static StageTaskNode g_nodes[4];
static int g_node_count;
static int g_created_callbacks[4];
static StageTaskNode* HookCreateTask(int callback_index) {
	Log("create;");
	StageTaskNode* node = &g_nodes[g_node_count];
	g_created_callbacks[g_node_count] = callback_index;
	++g_node_count;
	std::memset(node, 0, sizeof(*node));
	node->flags = 0xFFu;
	return node;
}

static int g_update_priority;
static StageTaskNode* g_update_node;
static void* g_update_scheduler;
static void HookRegisterUpdate(int priority, StageTaskNode* node,
                               void* scheduler) {
	Log("regU;");
	g_update_priority = priority;
	g_update_node = node;
	g_update_scheduler = scheduler;
}

static int g_draw_priority;
static StageTaskNode* g_draw_node;
static void* g_draw_scheduler;
static void HookRegisterDraw(int priority, StageTaskNode* node,
                             void* scheduler) {
	Log("regD;");
	g_draw_priority = priority;
	g_draw_node = node;
	g_draw_scheduler = scheduler;
}

static void HookReplayReset() { Log("rreset;"); }
static void* g_replay_seed_game;
static void HookReplaySeed(void* game) {
	Log("rseed;");
	g_replay_seed_game = game;
}

static int g_script_result;
static const char* g_script_name;
static int g_script_flag;
static int HookLoadScript(const char* name, int flag) {
	Log("script;");
	g_script_name = name;
	g_script_flag = flag;
	return g_script_result;
}

static int g_side_result;
static void* g_side_replay;
static void* g_side_keys;
static int HookInitSidePanel(void* replay_handle, void* key_buffer) {
	Log("side;");
	g_side_replay = replay_handle;
	g_side_keys = key_buffer;
	return g_side_result;
}

static int g_init_results[8]; // 414830,425020,406060,41AED0,score,422360,419090,stage
static int HookInit414830() { Log("i414830;"); return g_init_results[0]; }
static int HookInit425020() { Log("i425020;"); return g_init_results[1]; }
static int HookInit406060() { Log("i406060;"); return g_init_results[2]; }
static int HookInit41AED0() { Log("i41aed0;"); return g_init_results[3]; }
static int HookCreateScore() { Log("score;"); return g_init_results[4]; }
static int HookInit422360() { Log("i422360;"); return g_init_results[5]; }
static int HookInit419090() { Log("i419090;"); return g_init_results[6]; }
static int HookCreateStage() { Log("stage;"); return g_init_results[7]; }

static void* g_spell_reset_state;
static void HookSpellReset(void* state) {
	Log("spell;");
	g_spell_reset_state = state;
}

static int g_enemy_result;
static void* g_enemy_script_seen;
static int HookCreateEnemy(void* enemy_script) {
	Log("enemy;");
	g_enemy_script_seen = enemy_script;
	return g_enemy_result;
}

static int g_bullet_result;
static int HookCreateBullet() { Log("bullet;"); return g_bullet_result; }
static int g_4056b0_result;
static int HookInit4056B0() { Log("i4056b0;"); return g_4056b0_result; }
static int g_408c90_result;
static int HookInit408C90() { Log("i408c90;"); return g_408c90_result; }

static void HookMusicReset() { Log("mreset;"); }
static int g_music_slots[4];
static const char* g_music_names[4];
static int g_music_count;
static void HookMusicLoad(int slot, const char* name) {
	Log("music;");
	if (g_music_count < 4) {
		g_music_slots[g_music_count] = slot;
		g_music_names[g_music_count] = name;
	}
	++g_music_count;
}

static float* g_spawn_target;
static int g_spawn_value;
static void HookResetSpawn(float* spawn, int value) {
	Log("spawn;");
	g_spawn_target = spawn;
	g_spawn_value = value;
}

static void* g_overlay_slots;
static int g_overlay_count;
static void HookReleaseOverlay(void* slots) {
	Log("overlay;");
	g_overlay_slots = slots;
	++g_overlay_count;
}

static void* g_pending_slots;
static void HookReleasePending(void* slots) {
	Log("pending;");
	g_pending_slots = slots;
}

static void* g_removal_context;
static void HookRequestRemoval(void* context) {
	Log("removal;");
	g_removal_context = context;
}

static void MakeEnv(StageEntryEnv* env) {
	std::memset(env, 0, sizeof(*env));
	std::memset(&g_globals, 0, sizeof(g_globals));
	g_globals.sync[0] = -1;
	g_globals.sync[1] = -1;
	g_globals.camera_a = 5.0;
	g_globals.camera_b = 7.0;
	std::memset(g_score_file, 0, sizeof(g_score_file));
	for (int i = 0; i < 52; ++i)
		g_descriptor[i] = (unsigned char)(i + 3);
	g_record.number = 4;
	g_record.script_name = "stage04.std";
	g_record.reserved_8 = 0;
	g_record.enemy_script = &g_enemy_script_tag;
	g_record.music_name = "th10_09.wav";
	g_record.music_loop = "th10_09loop.wav";
	env->globals = &g_globals;
	env->score_file = g_score_file;
	env->stage_record = &g_record;
	env->stage_descriptor = g_descriptor;
	env->scheduler = &g_scheduler_tag;
	env->anm_slots = &g_anm_tag;
	env->game = &g_game_tag;
	env->spell_practice_state = &g_spell_tag;
	env->key_buffer = &g_key_tag;
	env->sleep = HookSleep;
	env->seed_extend_threshold = HookSeedExtend;
	env->create_task = HookCreateTask;
	env->register_update = HookRegisterUpdate;
	env->register_draw = HookRegisterDraw;
	env->replay_reset = HookReplayReset;
	env->replay_seed = HookReplaySeed;
	env->load_stage_script = HookLoadScript;
	env->init_side_panel = HookInitSidePanel;
	env->init_414830 = HookInit414830;
	env->init_425020 = HookInit425020;
	env->init_406060 = HookInit406060;
	env->init_41aed0 = HookInit41AED0;
	env->create_score_manager = HookCreateScore;
	env->init_422360 = HookInit422360;
	env->init_419090 = HookInit419090;
	env->create_stage_state = HookCreateStage;
	env->spell_practice_reset = HookSpellReset;
	env->create_enemy_manager = HookCreateEnemy;
	env->create_bullet_manager = HookCreateBullet;
	env->init_4056b0 = HookInit4056B0;
	env->init_408c90 = HookInit408C90;
	env->music_reset = HookMusicReset;
	env->music_load = HookMusicLoad;
	env->reset_player_spawn = HookResetSpawn;
	env->release_overlay_anm = HookReleaseOverlay;
	env->release_pending_anm = HookReleasePending;
	env->request_callback_removal = HookRequestRemoval;
	g_log[0] = 0;
	g_sleep_count_1ms = 0;
	g_sleep_count_16ms = 0;
	g_sync_decrement = 0;
	g_loader_countdown = 0;
	g_extend_target = 0;
	g_extend_amount = 0;
	g_node_count = 0;
	g_script_result = 1;
	g_script_name = 0;
	g_script_flag = -1;
	g_side_result = 1;
	for (int i = 0; i < 8; ++i)
		g_init_results[i] = 1;
	g_enemy_result = 1;
	g_bullet_result = 1;
	g_4056b0_result = 1;
	g_408c90_result = 1;
	g_music_count = 0;
	g_overlay_count = 0;
	g_overlay_slots = 0;
	g_pending_slots = 0;
	g_removal_context = 0;
}

static void MakeContext(StageContext* context) {
	std::memset(context, 0, sizeof(*context));
}

static void WriteDword(unsigned char* at, int value) {
	std::memcpy(at, &value, 4);
}
static int ReadDword(const unsigned char* at) {
	int value = 0;
	std::memcpy(&value, at, 4);
	return value;
}

// ---------------------------------------------------------------------------
// StageContext_Enter tests
// ---------------------------------------------------------------------------

static void TestSyncWaitThenSuccess() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.sync[0] = 5; // needs 3 decrements of 2 to reach -1
	g_sync_decrement = 1;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_sleep_count_1ms == 3);
	CHECK(g_globals.frame_scale == 1.0f);
}

static void TestSyncAbort() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.sync[0] = 5;
	g_globals.ui_flags = 0x80;
	CHECK(StageContext_Enter(&context, &env) == -1);
	// Entry bit stays set, fail bit set, overlay release with the slot
	// block, result words published, no task nodes were created.
	CHECK((context.flags & 4u) != 0);
	CHECK((context.flags & 8u) != 0);
	CHECK(g_overlay_count == 1);
	CHECK(g_overlay_slots == &g_anm_tag);
	CHECK(g_globals.result_492264 == 0);
	CHECK(g_globals.result_492260 == 1);
	CHECK(g_node_count == 0);
	CHECK(std::strcmp(g_log, "overlay;") == 0);
}

static void TestFreshRunSeeding() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.fresh_run = 1;
	g_globals.character = 1;
	g_globals.stage = 2;
	g_globals.difficulty = 1;
	g_globals.game_flags = 0x14; // continue bit + stale bit 2
	g_globals.continues = 3;
	g_globals.power_474c90 = 55;
	g_globals.score_current = 999;
	// Record base 17276 * (3*1 + 2) = 86380; difficulty offset 240.
	WriteDword(g_score_file + 86380 + 240 + 24, 12345);
	g_score_file[86380 + 240 + 29] = 77;
	WriteDword(g_score_file + 86380 + 1224, 5);
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.score_seed == 12345);
	CHECK(g_globals.power_seed == 77);
	CHECK(g_globals.power_474c90 == 0); // bit 3 clear -> zeroed
	CHECK(g_globals.score_current == 0);
	CHECK(g_extend_target == &g_globals.score_seed);
	CHECK(g_extend_amount == 50000);
	CHECK(g_globals.lives == 2); // continues 3 - 1
	CHECK(g_globals.bomb_fragments == 0x50);
	CHECK(g_globals.counter_474c98 == 0);
	CHECK(g_globals.counter_474c9c == 0);
	CHECK(g_globals.extend_index == 9);
	// Play count incremented (no replay handle).
	CHECK(ReadDword(g_score_file + 86380 + 1224) == 6);
}

static void TestPracticeDifficultyOverride() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.fresh_run = 1;
	g_globals.mode = 7;
	g_globals.difficulty = 1;
	// Practice forces difficulty 4: score at 240*4 + 24 = 984.
	WriteDword(g_score_file + 984, 4444);
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.difficulty == 4);
	CHECK(g_globals.score_seed == 4444);
	// Mode != 1 keeps the 0x50 bomb word.
	CHECK(g_globals.bomb_fragments == 0x50);
}

static void TestLivesAndBombVariants() {
	StageEntryEnv env;
	StageContext context;
	// Continue flag with zero continues -> 9 lives.
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.fresh_run = 1;
	g_globals.game_flags = 0x10;
	g_globals.continues = 0;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.lives == 9);
	// No continue flag -> 2 lives; mode 1 -> zero bomb word.
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.fresh_run = 1;
	g_globals.mode = 1;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.lives == 2);
	CHECK(g_globals.bomb_fragments == 0);
}

static void TestPlayCountCapAndReplaySkip() {
	StageEntryEnv env;
	StageContext context;
	// Cap at 99999.
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.fresh_run = 1;
	WriteDword(g_score_file + 1224, 99999);
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(ReadDword(g_score_file + 1224) == 99999);
	// Replay handle skips the increment.
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.fresh_run = 1;
	context.replay_handle = &g_game_tag;
	WriteDword(g_score_file + 1224, 10);
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(ReadDword(g_score_file + 1224) == 10);
}

static void TestCarryHighScore() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.score_seed = 100;
	g_globals.score_current = 500;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.score_seed == 500);
	CHECK(g_globals.extend_index == 9);
	// Lower current score leaves the seed alone.
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.score_seed = 100;
	g_globals.score_current = 50;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.score_seed == 100);
}

static void TestTaskRegistrationAndDescriptor() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_node_count == 2);
	CHECK(g_created_callbacks[0] == 0);
	CHECK(g_created_callbacks[1] == 1);
	// Arm bit cleared (0xFF -> 0xFD), context attached, priorities 10/4.
	CHECK(g_nodes[0].flags == 0xFDu);
	CHECK(g_nodes[1].flags == 0xFDu);
	CHECK(g_nodes[0].context == &context);
	CHECK(g_nodes[1].context == &context);
	CHECK(g_update_priority == 10);
	CHECK(g_update_node == &g_nodes[0]);
	CHECK(g_update_scheduler == &g_scheduler_tag);
	CHECK(g_draw_priority == 4);
	CHECK(g_draw_node == &g_nodes[1]);
	CHECK(g_draw_scheduler == &g_scheduler_tag);
	CHECK(context.update_task == &g_nodes[0]);
	CHECK(context.draw_task == &g_nodes[1]);
	CHECK(std::memcmp(context.descriptor, g_descriptor, 52) == 0);
	CHECK(context.stage_number == 4);
}

static void TestNormalChainOrderAndTail() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	context.replay_handle = 0;
	g_globals.pending_474c84 = 1;
	g_globals.counter_474c8c = 42;
	g_globals.game_flags = 0x0B & ~0x0Bu; // start clean
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(std::strcmp(g_log,
	                  "create;regU;create;regD;side;script;i414830;i425020;"
	                  "i406060;i41aed0;score;i422360;i419090;stage;enemy;"
	                  "bullet;i4056b0;i408c90;mreset;music;music;spawn;"
	                  "pending;removal;") == 0);
	CHECK(g_side_replay == 0);
	CHECK(g_side_keys == &g_key_tag);
	CHECK(std::strcmp(g_script_name, "stage04.std") == 0);
	CHECK(g_script_flag == 0);
	CHECK(g_enemy_script_seen == &g_enemy_script_tag);
	CHECK(g_music_count == 2);
	CHECK(g_music_slots[0] == 0);
	CHECK(std::strcmp(g_music_names[0], "th10_09.wav") == 0);
	CHECK(g_music_slots[1] == 1);
	CHECK(std::strcmp(g_music_names[1], "th10_09loop.wav") == 0);
	CHECK(g_globals.camera_a == 0.0);
	CHECK(g_globals.camera_b == 0.0);
	CHECK(g_spawn_target == context.spawn);
	CHECK(g_spawn_value == 0);
	// Pending word consumed and the counter zeroed.
	CHECK(g_globals.pending_474c84 == 0);
	CHECK(g_globals.counter_474c8c == 0);
	CHECK(g_pending_slots == &g_anm_tag);
	// Entry bit cleared only on success; result words and counters set.
	CHECK((context.flags & 4u) == 0);
	CHECK((context.flags & 8u) == 0);
	CHECK(g_globals.result_492264 == 0);
	CHECK(g_globals.result_492260 == 1);
	CHECK(g_globals.counter_4918a4 == 0);
	CHECK(g_removal_context == &context);
}

static void TestGameFlagMaskOnSuccess() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.game_flags = 0x3B; // bits 0,1,3 clear; 4,5 survive
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_globals.game_flags == 0x30u);
}

static void TestInitFailureKillsTasks() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_init_results[1] = 0; // 0x00425020 fails
	CHECK(StageContext_Enter(&context, &env) == -1);
	CHECK((context.flags & 8u) != 0);
	CHECK((context.flags & 4u) != 0); // entry bit not cleared on failure
	CHECK((g_nodes[0].flags & 2u) != 0);
	CHECK((g_nodes[1].flags & 2u) != 0);
	CHECK(g_overlay_count == 1);
	// Chain stopped at the failing step; nothing later ran.
	CHECK(std::strstr(g_log, "i406060;") == 0);
	CHECK(std::strstr(g_log, "removal;") == 0);
}

static void TestStageStateFailure() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_init_results[7] = 0; // 0x0042B660 returns null
	CHECK(StageContext_Enter(&context, &env) == -1);
	CHECK(std::strstr(g_log, "enemy;") == 0);
}

static void TestReplayBranch() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.game_flags = 2;
	CHECK(StageContext_Enter(&context, &env) == 0);
	// Short path: no side panel or nine-step chain, but the shared
	// post-construction steps still run (2 & 9 == 0 -> enemy manager).
	CHECK(std::strstr(g_log, "rreset;rseed;script;") != 0);
	CHECK(std::strstr(g_log, "side;") == 0);
	CHECK(std::strstr(g_log, "i414830;") == 0);
	CHECK(std::strstr(g_log, "stage;") == 0);
	CHECK(std::strstr(g_log, "enemy;") != 0);
	CHECK(g_replay_seed_game == &g_game_tag);
	// Replay script failure fails the entry.
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.game_flags = 2;
	g_script_result = 0;
	CHECK(StageContext_Enter(&context, &env) == -1);
}

static void TestSpellPracticeBranch() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.game_flags = 9; // bits 0 and 3
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(std::strstr(g_log, "spell;") != 0);
	CHECK(std::strstr(g_log, "enemy;") == 0);
	CHECK(g_spell_reset_state == &g_spell_tag);
	// Bits 0 and 3 are cleared by the success mask.
	CHECK(g_globals.game_flags == 0u);
}

static void TestMusicSuppression() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.game_flags = 0x20;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(std::strstr(g_log, "mreset;") == 0);
	CHECK(g_music_count == 0);
}

static void TestPostChainFailures() {
	StageEntryEnv env;
	StageContext context;
	// Enemy manager failure.
	MakeEnv(&env);
	MakeContext(&context);
	g_enemy_result = 0;
	CHECK(StageContext_Enter(&context, &env) == -1);
	CHECK(std::strstr(g_log, "bullet;") == 0);
	// Bullet manager failure.
	MakeEnv(&env);
	MakeContext(&context);
	g_bullet_result = 0;
	CHECK(StageContext_Enter(&context, &env) == -1);
	CHECK(std::strstr(g_log, "i4056b0;") == 0);
	// 0x00408C90 failure.
	MakeEnv(&env);
	MakeContext(&context);
	g_408c90_result = 0;
	CHECK(StageContext_Enter(&context, &env) == -1);
	CHECK(std::strstr(g_log, "mreset;") == 0);
}

static void TestLoaderWait() {
	StageEntryEnv env;
	StageContext context;
	MakeEnv(&env);
	MakeContext(&context);
	g_globals.loader_busy = 3;
	g_loader_countdown = 1;
	CHECK(StageContext_Enter(&context, &env) == 0);
	CHECK(g_sleep_count_16ms == 3);
}

// ---------------------------------------------------------------------------
// Task callback tests
// ---------------------------------------------------------------------------

static void* g_tick_context;
static int FakeStageTick(void* context) {
	g_tick_context = context;
	return 7;
}

static void TestUpdateThunk() {
	int tag = 0;
	CHECK(StageTask_UpdateThunk(&tag, FakeStageTick) == 7);
	CHECK(g_tick_context == &tag);
}

static void TestClearCameraOnIdle() {
	StageContext context;
	MakeContext(&context);
	int words[24];
	for (int i = 0; i < 24; ++i)
		words[i] = 100 + i;
	// Entry in progress: untouched.
	context.flags = 4;
	CHECK(StageTask_ClearCameraOnIdle(&context, words) == 1);
	CHECK(words[19] == 119 && words[20] == 120 && words[21] == 121 &&
	      words[22] == 122);
	// Idle: words 19..22 zeroed, neighbors intact.
	context.flags = 0;
	CHECK(StageTask_ClearCameraOnIdle(&context, words) == 1);
	CHECK(words[19] == 0 && words[20] == 0 && words[21] == 0 &&
	      words[22] == 0);
	CHECK(words[18] == 118);
	CHECK(words[23] == 123);
}

int main() {
	TestSyncWaitThenSuccess();
	TestSyncAbort();
	TestFreshRunSeeding();
	TestPracticeDifficultyOverride();
	TestLivesAndBombVariants();
	TestPlayCountCapAndReplaySkip();
	TestCarryHighScore();
	TestTaskRegistrationAndDescriptor();
	TestNormalChainOrderAndTail();
	TestGameFlagMaskOnSuccess();
	TestInitFailureKillsTasks();
	TestStageStateFailure();
	TestReplayBranch();
	TestSpellPracticeBranch();
	TestMusicSuppression();
	TestPostChainFailures();
	TestLoaderWait();
	TestUpdateThunk();
	TestClearCameraOnIdle();

	if (g_failures != 0) {
		std::printf("%d check(s) failed\n", g_failures);
		return 1;
	}
	std::printf("recovery_batch25_test passed\n");
	return 0;
}
