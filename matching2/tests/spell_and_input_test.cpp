// Assert-based behavioral tests for recovery batch 11.

#include "th10/game/enemy_motion_steps.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/score_tasks.hpp"
#include "th10/game/spell_card_dispatch.hpp"
#include "th10/platform/font_surface_blend.hpp"
#include "th10/platform/joystick_poll.hpp"
#include "th10/render/anm_script_table_sweep.hpp"
#include "th10/util/scalars.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace {

long long FloatToLong(float value) {
	return (long long)value;
}

ClockEnv MakeClockEnv() {
	ClockEnv env;
	env.span_low = 0.99f;
	env.span_high = 1.01f;
	env.frame_step = 1.0f;
	env.float_to_long = FloatToLong;
	return env;
}

// --- AnmScriptTable_Sweep ----------------------------------------------------

static_assert(sizeof(AnmSpriteSlot) == 8, "slot stride must be 8 bytes");

int g_live_by_vm[8];
int g_run_calls;

int RunScript(void* vm_pool, int vm_index) {
	(void)vm_pool;
	g_run_calls += 1;
	return g_live_by_vm[vm_index];
}

void TestAnmScriptTableSweep() {
	AnmSpriteSlot slots_live[3] = {
	    {0, 8, 0, 1},
	    {1, 8, 0, 2},
	    {-1, 0, 0, 0},
	};
	AnmSpriteSlot slots_dead[2] = {
	    {0, 8, 0, 3},
	    {-1, 0, 0, 0},
	};
	AnmSpriteSlot slots_empty[1] = {{-1, 0, 0, 0}};

	AnmSweepRecord live_record = {1, slots_live};   // stays active
	AnmSweepRecord dead_record = {1, slots_dead};   // cleared
	AnmSweepRecord idle_record = {0, slots_dead};   // skipped
	AnmSweepRecord empty_record = {1, slots_empty}; // cleared

	AnmSweepRecord* records[4] = {&live_record, &dead_record, &idle_record,
	                                  &empty_record};
	short count = 4;

	std::memset(g_live_by_vm, 0, sizeof(g_live_by_vm));
	g_live_by_vm[1] = 1; // VM 1 keeps an instruction cursor
	g_run_calls = 0;

	AnmSweepEnv env;
	std::memset(&env, 0, sizeof(env));
	env.count = &count;
	env.records = records;
	env.run_script = RunScript;

	assert(AnmScriptTable_Sweep(&env) == 0);
	assert((live_record.flags & 1u) == 1u);  // one live slot keeps it active
	assert((dead_record.flags & 1u) == 0u);  // all slots dead -> cleared
	assert((idle_record.flags & 1u) == 0u);  // inactive record untouched
	assert((empty_record.flags & 1u) == 0u); // empty list clears immediately
	assert(g_run_calls == 3); // 2 runs for the live record + 1 for the dead one
}

// --- Enemy_HomingRelaunchStep ------------------------------------------------

int g_sound_calls;

void PlaySound(void* sound_state, int id) {
	(void)sound_state;
	(void)id;
	g_sound_calls += 1;
}

float NormalizeSum(float angle, float delta) {
	return angle + delta;
}

void SetVelocity(float* velocity, float angle, float speed) {
	velocity[0] = angle;
	velocity[1] = speed;
}

void TestEnemyHomingRelaunchStep() {
	float frame_scale = 1.0f;
	float player_pos[2] = {0.0f, 0.0f};

	RelaunchEnv env;
	std::memset(&env, 0, sizeof(env));
	env.clock_env = MakeClockEnv();
	env.player_pos = player_pos;
	env.frame_scale = &frame_scale;
	env.play_sound = PlaySound;
	env.normalize_sum = NormalizeSum;
	env.set_velocity = SetVelocity;

	// Deceleration phase: heading kept, speed decays linearly, clock ticks.
	RelaunchEnemy enemy;
	std::memset(&enemy, 0, sizeof(enemy));
	enemy.speed = 10.0f;
	enemy.duration = 10;
	enemy.angle = 2.0f;
	enemy.clock.flags = 1;
	enemy.clock.clock.frame = 5;
	enemy.clock.clock.timer = 5.0f;
	enemy.clock.clock.control = &frame_scale;
	g_sound_calls = 0;

	Enemy_HomingRelaunchStep(&enemy, &env);
	assert(enemy.velocity[0] == 2.0f); // heading unchanged
	assert(enemy.velocity[1] == 5.0f); // 10 - 10*5/10
	assert(enemy.clock.clock.frame == 6 && enemy.clock.clock.previous == 5);
	assert(g_sound_calls == 0);

	// Relaunch phase: sound, counter, re-aim at the player, clock restart.
	std::memset(&enemy, 0, sizeof(enemy));
	enemy.pos_x = player_pos[0];
	enemy.pos_y = player_pos[1]; // dx == dy == 0 -> kRelaunchHalfPi fallback
	enemy.duration = 10;
	enemy.mode_flags = kEnemyModeRelaunchArmed | 1u;
	enemy.relaunch_limit = 1;
	enemy.relaunch_speed = 4.0f;
	enemy.angle_offset = 0.25f;
	enemy.clock.flags = 1;
	enemy.clock.clock.frame = 10; // duration reached
	enemy.clock.clock.control = &frame_scale;

	Enemy_HomingRelaunchStep(&enemy, &env);
	assert(g_sound_calls == 1);
	assert(enemy.relaunch_count == 1);
	assert(enemy.mode_flags == 1u); // relaunch-armed bit cleared at the limit
	assert(enemy.angle == kRelaunchHalfPi + 0.25f);
	assert(enemy.speed == 4.0f);
	assert(enemy.velocity[1] == 4.0f);
	assert(enemy.clock.clock.frame == 1 && enemy.clock.clock.timer == 1.0f);
}

// --- ScoreTaskList_Tick ------------------------------------------------------

int g_updates;
int g_destroys;
int g_frees;

int UpdateKeep(ScoreTaskNode* node) {
	(void)node;
	g_updates += 1;
	return 0;
}

void DestroyNode(ScoreTaskNode* node) {
	(void)node;
	g_destroys += 1;
}

void FreeNode(ScoreTaskNode* node) {
	(void)node;
	g_frees += 1;
}

void TestScoreTaskListTick() {
	float frame_scale = 1.0f;
	ClockEnv clock_env = MakeClockEnv();

	ScoreTaskList list;
	std::memset(&list, 0, sizeof(list));
	ScoreTaskNode ticked, killed, retired;
	std::memset(&ticked, 0, sizeof(ticked));
	std::memset(&killed, 0, sizeof(killed));
	std::memset(&retired, 0, sizeof(retired));

	list.head_sentinel.next = &ticked;
	ticked.prev = &list.head_sentinel;
	ticked.next = &killed;
	killed.prev = &ticked;
	killed.next = &retired;
	retired.prev = &killed;
	retired.next = 0;
	list.cursor = &retired;
	list.live_count = 3;
	list.free_node = FreeNode;

	ticked.update = UpdateKeep;
	ticked.destroy = DestroyNode;
	ticked.clock.control = &frame_scale;
	killed.update = UpdateKeep;
	killed.destroy = DestroyNode;
	killed.kill_flag = 1; // forced retirement
	retired.update = UpdateKeep;
	retired.destroy = DestroyNode;
	retired.retire_count = 1; // increments to 2 and retires

	g_updates = g_destroys = g_frees = 0;
	assert(ScoreTaskList_Tick(&list, &clock_env) == 1);
	assert(g_updates == 1); // only the surviving node ran its update
	assert(g_destroys == 2 && g_frees == 2);
	assert(list.live_count == 1);
	assert(list.head_sentinel.next == &ticked && ticked.next == 0);
	assert(list.cursor == &ticked); // repaired when its node retired
	assert(ticked.clock.frame == 1 && ticked.clock.previous == 0);
}

// --- SpellCard_Dispatch ------------------------------------------------------

SpellRecord g_allocated;

SpellRecord* AllocateRecord() {
	std::memset(&g_allocated, 0, sizeof(g_allocated));
	return &g_allocated;
}

void StoreGauge(void* gauge, int value) {
	*(int*)gauge = value;
}

void TestSpellCardDispatchDeclare() {
	short active_spell_id = 42;
	int active_spell_aux = 9;
	Word capture_flag = 1;
	int difficulty = 1;

	SpellRecord* history[4] = {0, 0, 0, 0};
	SpellSlot slots[4];
	std::memset(slots, 0, sizeof(slots));

	SpellManager manager;
	manager.state = kSpellStateDeclare;
	manager.history = history;
	manager.slots = slots;

	SpellDispatchEnv env;
	std::memset(&env, 0, sizeof(env));
	env.difficulty = &difficulty;
	env.allocate_record = AllocateRecord;
	env.ui.active_spell_id = &active_spell_id;
	env.ui.active_spell_aux = &active_spell_aux;
	env.ui.capture_flag = &capture_flag;

	SpellCard_Dispatch(&manager, &env);
	assert(history[1] == &g_allocated);
	assert(g_allocated.spell_id == 42);
	assert(g_allocated.difficulty == 1);
	assert((g_allocated.flags & 1u) == 1u); // mirrors the capture flag
	assert(active_spell_aux == 0);
}

void TestSpellCardDispatchActivate() {
	short active_spell_id = 0;
	int active_spell_aux = 9;
	int bonus_value = 0;
	short bonus_active = 0;
	int gauge_marker = 0;
	RegisteredClock spell_clock;
	std::memset(&spell_clock, 0, sizeof(spell_clock));
	float frame_scale = 1.0f;
	int activation_param_a = 0, activation_param_b = 0;
	int history_captures = 0, history_attempts = 0;
	Word capture_flag = 1;
	int difficulty = 1;

	SpellRecord record;
	std::memset(&record, 0, sizeof(record));
	record.spell_id = 77;
	record.bonus_initial = 500000;
	record.bonus_active = 3;
	record.bonus_gauge = 120;
	record.duration = 3600;
	record.activation_param_a = 11;
	record.activation_param_b = 22;
	record.history_captures = 33;
	record.history_attempts = 44;

	SpellSlot slots[4];
	std::memset(slots, 0, sizeof(slots));
	slots[1].current_a = 100;
	slots[1].current_b = 200;
	slots[1].record = &record;
	slots[1].counter = 5;

	SpellManager manager;
	manager.state = kSpellStateActivate;
	manager.history = 0;
	manager.slots = slots;

	SpellDispatchEnv env;
	std::memset(&env, 0, sizeof(env));
	env.difficulty = &difficulty;
	env.ui.active_spell_id = &active_spell_id;
	env.ui.active_spell_aux = &active_spell_aux;
	env.ui.bonus_value = &bonus_value;
	env.ui.bonus_active = &bonus_active;
	env.ui.gauge = &gauge_marker;
	env.ui.store_gauge = StoreGauge;
	env.ui.spell_clock = &spell_clock;
	env.ui.frame_scale = &frame_scale;
	env.ui.activation_param_a = &activation_param_a;
	env.ui.activation_param_b = &activation_param_b;
	env.ui.history_captures = &history_captures;
	env.ui.history_attempts = &history_attempts;
	env.ui.capture_flag = &capture_flag;

	SpellCard_Dispatch(&manager, &env);
	assert(slots[1].previous_a == 100 && slots[1].previous_b == 200);
	assert(slots[1].counter == 0);
	assert(active_spell_id == 77);
	assert(active_spell_aux == 0);
	assert(bonus_value == 500000);
	assert(bonus_active == 3);
	assert(gauge_marker == 1200); // bonus_gauge published times ten
	assert(spell_clock.clock.frame == 3600);
	assert(spell_clock.clock.timer == 3600.0f);
	assert(spell_clock.clock.previous == 3599);
	assert((spell_clock.flags & 1u) == 1u);
	assert(spell_clock.clock.control == &frame_scale);
	assert(activation_param_a == 11 && activation_param_b == 22);
	assert(history_captures == 33 && history_attempts == 44);
}

// --- FontCache_BlendToSurface ------------------------------------------------

Byte g_dst_pixels[16];
int g_lock_format;
int g_lock_calls;
int g_unlock_calls;

int LockSurface(void* texture, int width, int height,
                LockedSurface* out) {
	(void)texture;
	(void)width;
	(void)height;
	g_lock_calls += 1;
	out->bits = g_dst_pixels;
	out->pitch = 4;
	out->format = g_lock_format;
	return 0;
}

int UnlockSurface(void* texture) {
	(void)texture;
	g_unlock_calls += 1;
	return 0;
}

void TestFontCacheBlendToSurface() {
	FontSurfaceEnv env = {LockSurface, UnlockSurface};
	Byte src[4] = {100, 50, 200, 255};

	FontCacheSurface cache;
	std::memset(&cache, 0, sizeof(cache));
	cache.format = kFontFormatA8R8G8B8;
	cache.width = 1;
	cache.height = 1;
	cache.src_pitch = 4;
	cache.valid = (void*)1;
	cache.src_bits = src;

	// A8R8G8B8 blend over a black destination.
	std::memset(g_dst_pixels, 0, sizeof(g_dst_pixels));
	g_lock_format = kFontFormatA8R8G8B8;
	g_lock_calls = g_unlock_calls = 0;
	assert(FontCache_BlendToSurface(&cache, 0, 0, 0, 1, &env) == 1);
	assert(g_unlock_calls == 1);
	assert(g_dst_pixels[0] == 99);  // (100 * 255) >> 8
	assert(g_dst_pixels[1] == 49);  // (50 * 255) >> 8
	assert(g_dst_pixels[2] == 199); // (200 * 255) >> 8
	assert(g_dst_pixels[3] == 0);   // destination alpha byte untouched

	// Format mismatch: no copy, still unlocks and reports success.
	std::memset(g_dst_pixels, 0, sizeof(g_dst_pixels));
	g_lock_format = kFontFormatA1R5G5B5;
	assert(FontCache_BlendToSurface(&cache, 0, 0, 0, 1, &env) == 1);
	assert(g_dst_pixels[0] == 0);

	// Invalid cache: rejected before locking.
	int locks_before = g_lock_calls;
	cache.valid = 0;
	assert(FontCache_BlendToSurface(&cache, 0, 0, 0, 1, &env) == 0);
	assert(g_lock_calls == locks_before);

	// Unsupported matching format: unlocks and fails.
	cache.valid = (void*)1;
	cache.format = 0x99;
	g_lock_format = 0x99;
	int unlocks_before = g_unlock_calls;
	assert(FontCache_BlendToSurface(&cache, 0, 0, 0, 1, &env) == 0);
	assert(g_unlock_calls == unlocks_before + 1);
}

// --- Joystick_Poll -----------------------------------------------------------

WinmmState g_winmm_state;
int g_winmm_result;

int GetPosition(int pad, WinmmState* out) {
	(void)pad;
	*out = g_winmm_state;
	return g_winmm_result;
}

DirectInputState g_di_state;
int g_poll_result;
int g_acquire_result;
int g_acquire_calls;

int PollDevice(void* device) {
	(void)device;
	return g_poll_result;
}

int AcquireDevice(void* device) {
	(void)device;
	g_acquire_calls += 1;
	return g_acquire_result;
}

int GetState(void* device, DirectInputState* out) {
	(void)device;
	*out = g_di_state;
	return 0;
}

void TestJoystickPoll() {
	PadButtons configs[2];
	std::memset(configs, 0, sizeof(configs));
	configs[0].shoot = 0;  // button 0 -> kPadShoot
	configs[0].bomb = 1;   // button 1 -> kPadBomb
	configs[0].focus = 2;  // button 2 -> kPadFocus
	configs[0].pause = -1; // unbound
	configs[0].skip = 4;   // button 4 -> kPadSkip

	JoyCalibration calibrations[1] = {{0, 100, 0, 100}};

	void* devices[1] = {0};
	JoyPollEnv env;
	std::memset(&env, 0, sizeof(env));
	env.configs = configs;
	env.get_position = GetPosition;
	env.calibrations = calibrations;
	env.devices = devices;
	env.poll = PollDevice;
	env.acquire = AcquireDevice;
	env.get_state = GetState;
	env.threshold_x = 100;
	env.threshold_y = 100;

	// winmm path: shoot + focus buttons, stick up-right past the dead zone.
	env.use_direct_input = 0;
	g_winmm_state.buttons = (1u << 0) | (1u << 2);
	g_winmm_state.x = 90; // > center 50 + quarter 25 -> right
	g_winmm_state.y = 10; // < center 50 - quarter 25 -> up
	g_winmm_result = 0;
	Half state = Joystick_Poll(0, 0, 0, &env);
	assert(state == (kPadShoot | kPadFocus |
	                 kPadUp | kPadRight));

	// winmm failure leaves the state untouched.
	g_winmm_result = 1;
	assert(Joystick_Poll(0x123, 0, 0, &env) == 0x123);

	// DirectInput path: same buttons via rgbButtons bit 7, axes past the
	// global thresholds.
	env.use_direct_input = 1;
	g_poll_result = 0;
	std::memset(&g_di_state, 0, sizeof(g_di_state));
	g_di_state.buttons[0] = 0x80; // shoot
	g_di_state.buttons[2] = 0x80; // focus
	g_di_state.x = 101;           // > threshold -> right
	g_di_state.y = -101;          // < -threshold -> up
	state = Joystick_Poll(0, 0, 0, &env);
	assert(state == (kPadShoot | kPadFocus |
	                 kPadUp | kPadRight));

	// 0x0044A4E0's WinMM branch emits one 0x80 marker per pressed bit and
	// clears every other byte in the 32-byte output.
	JoystickButtonPollEnv button_env;
	std::memset(&button_env, 0, sizeof(button_env));
	button_env.get_position = GetPosition;
	unsigned char button_bytes[32];
	std::memset(button_bytes, 0xCC, sizeof(button_bytes));
	g_winmm_result = 0;
	g_winmm_state.buttons = (1u << 0) | (1u << 31);
	assert(Joystick_PollButtonBytes(button_bytes, 0, &button_env));
	assert(button_bytes[0] == 0x80 && button_bytes[31] == 0x80);
	assert(button_bytes[1] == 0 && button_bytes[30] == 0);

	// DirectInput copies rgbButtons byte-for-byte, rather than normalizing
	// nonzero values to the WinMM marker.
	button_env.use_direct_input = 1;
	button_env.devices = devices;
	button_env.poll = PollDevice;
	button_env.acquire = AcquireDevice;
	button_env.get_state = GetState;
	g_poll_result = 0;
	std::memset(&g_di_state, 0, sizeof(g_di_state));
	g_di_state.buttons[0] = 0x81;
	g_di_state.buttons[31] = 0x7E;
	assert(Joystick_PollButtonBytes(button_bytes, 0, &button_env));
	assert(button_bytes[0] == 0x81 && button_bytes[31] == 0x7E);
	assert(button_bytes[1] == 0 && button_bytes[30] == 0);

	// Every failed source read leaves the output cleared, including a WinMM
	// failure before any button state is available.
	g_winmm_result = 1;
	button_env.use_direct_input = 0;
	std::memset(button_bytes, 0xCC, sizeof(button_bytes));
	assert(!Joystick_PollButtonBytes(button_bytes, 0, &button_env));
	for (unsigned char byte : button_bytes)
		assert(byte == 0);

	// DIERR_INPUTLOST: the poll re-acquires up to 400 times, then gives up.
	g_poll_result = -1;
	g_acquire_result = kDInputInputLost;
	g_acquire_calls = 0;
	assert(Joystick_Poll(0x42, 0, 0, &env) == 0x42);
	assert(g_acquire_calls == 401); // initial attempt + 400 retries
}

} // namespace

int main() {
	TestAnmScriptTableSweep();
	TestEnemyHomingRelaunchStep();
	TestScoreTaskListTick();
	TestSpellCardDispatchDeclare();
	TestSpellCardDispatchActivate();
	TestFontCacheBlendToSurface();
	TestJoystickPoll();
	std::printf("BATCH11_TESTS_PASS\n");
	return 0;
}
