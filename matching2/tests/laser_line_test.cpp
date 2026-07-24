// Tests for recovery batch 23 (0x0041D3D0 line-laser update).
#include "th10/game/effect_pool_update.hpp"
#include "th10/game/laser_line.hpp"
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

static bool NearlyEqual(float a, float b, float tolerance) {
	return std::fabs(a - b) <= tolerance;
}

// ---------------------------------------------------------------------------
// Recording hooks
// ---------------------------------------------------------------------------

static char g_calls[32];
static int g_call_count;
static void PushCall(char tag) {
	if (g_call_count < 31) {
		g_calls[g_call_count++] = tag;
		g_calls[g_call_count] = 0;
	}
}

static void HookRunCommands(LineLaser*) { PushCall('c'); }
static void HookFlag0001(LineLaser*) { PushCall('1'); }
static void HookFlag0010(LineLaser*) { PushCall('a'); }
static void HookFlag0020(LineLaser*) { PushCall('2'); }
static void HookFlag0040(LineLaser*) { PushCall('t'); }
static void HookFlag0100(LineLaser*) { PushCall('h'); }
static void HookFlag0080(LineLaser*) { PushCall('8'); }
static void HookFlagBounce(LineLaser*) { PushCall('b'); }
static void HookFlag100000(LineLaser*) { PushCall('k'); }
static void HookFlag200000(LineLaser*) { PushCall('l'); }
static void HookFlag4000000(LineLaser*) { PushCall('m'); }

// A bounce hook that clears its own trigger bits, like retail 0x0041CFD0.
static void HookBounceClearsBits(LineLaser* laser) {
	PushCall('b');
	laser->flags &= 0xF7FFF3FFu;
}

static LaserTimer* g_advanced_timer;
static float g_advanced_delta;
static int g_advance_count;
static void HookAdvanceTimer(LaserTimer* timer, float delta) {
	g_advanced_timer = timer;
	g_advanced_delta = delta;
	++g_advance_count;
	timer->previous = timer->current;
	timer->elapsed += delta;
	timer->current = (int)timer->elapsed;
}

static void HookSetPolar(float* destination, float angle, float length) {
	destination[0] = std::cos(angle) * length;
	destination[1] = std::sin(angle) * length;
}

static float g_viewport_points[4][3];
static float g_viewport_radii[4][2];
static int g_viewport_calls;
static int g_viewport_results[4];
static int HookOutsideViewport(const float* point, float radius_x,
                               float radius_y) {
	int index = g_viewport_calls < 4 ? g_viewport_calls : 3;
	g_viewport_points[index][0] = point[0];
	g_viewport_points[index][1] = point[1];
	g_viewport_points[index][2] = point[2];
	g_viewport_radii[index][0] = radius_x;
	g_viewport_radii[index][1] = radius_y;
	return g_viewport_results[g_viewport_calls++];
}

static int g_classify_result;
static int g_classify_calls;
static float g_classify_probe[3];
static void* g_classify_player;
static float g_classify_angle;
static float g_classify_half_width;
static float g_classify_reach;
static int HookClassifyPlayer(const float* probe, void* player, float angle,
                              float half_width, float reach) {
	++g_classify_calls;
	g_classify_probe[0] = probe[0];
	g_classify_probe[1] = probe[1];
	g_classify_probe[2] = probe[2];
	g_classify_player = player;
	g_classify_angle = angle;
	g_classify_half_width = half_width;
	g_classify_reach = reach;
	return g_classify_result;
}

static int g_hit_calls;
static LineLaser* g_hit_laser;
static void* g_hit_player_state;
static float g_hit_box[3];
static int g_hit_flag;
static void HookHitPlayer(LineLaser* laser, void* player_state,
                          const float* box, int flag) {
	++g_hit_calls;
	g_hit_laser = laser;
	g_hit_player_state = player_state;
	g_hit_box[0] = box[0];
	g_hit_box[1] = box[1];
	g_hit_box[2] = box[2];
	g_hit_flag = flag;
}

static int g_graze_calls;
static void* g_graze_player_state;
static float g_graze_half_width;
static void HookRegisterGraze(void* player_state, float* half_width) {
	++g_graze_calls;
	g_graze_player_state = player_state;
	g_graze_half_width = *half_width;
}

static int g_sound_calls;
static int g_sound_id;
static float g_sound_x;
static void HookPlayGrazeSound(int id, float x) {
	++g_sound_calls;
	g_sound_id = id;
	g_sound_x = x;
}

static LineLaserVm* g_ticked[4];
static int g_tick_count;
static void HookTickVm(LineLaserVm* vm) {
	if (g_tick_count < 4)
		g_ticked[g_tick_count] = vm;
	++g_tick_count;
}

static int g_player_dummy;
static int g_player_state_dummy;
static LineLaserSprite g_sprite;
static LineLaserVm g_body_vm;
static LineLaserVm g_head_vm;

static void ResetRecorders() {
	g_call_count = 0;
	g_calls[0] = 0;
	g_advanced_timer = 0;
	g_advanced_delta = 0.0f;
	g_advance_count = 0;
	g_viewport_calls = 0;
	g_viewport_results[0] = 0;
	g_viewport_results[1] = 0;
	g_viewport_results[2] = 0;
	g_viewport_results[3] = 0;
	g_classify_result = 0;
	g_classify_calls = 0;
	g_hit_calls = 0;
	g_graze_calls = 0;
	g_sound_calls = 0;
	g_tick_count = 0;
	std::memset(g_ticked, 0, sizeof(g_ticked));
}

static void MakeEnv(LineLaserEnv* env) {
	std::memset(env, 0, sizeof(*env));
	env->run_commands = HookRunCommands;
	env->on_flag_0001 = HookFlag0001;
	env->on_flag_0010 = HookFlag0010;
	env->on_flag_0020 = HookFlag0020;
	env->on_flag_0040 = HookFlag0040;
	env->on_flag_0100 = HookFlag0100;
	env->on_flag_0080 = HookFlag0080;
	env->on_flag_bounce = HookFlagBounce;
	env->on_flag_100000 = HookFlag100000;
	env->on_flag_200000 = HookFlag200000;
	env->on_flag_4000000 = HookFlag4000000;
	env->hit_player = HookHitPlayer;
	env->advance_timer = HookAdvanceTimer;
	env->set_polar = HookSetPolar;
	env->outside_viewport = HookOutsideViewport;
	env->classify_player = HookClassifyPlayer;
	env->register_graze = HookRegisterGraze;
	env->play_graze_sound = HookPlayGrazeSound;
	env->tick_vm = HookTickVm;
	env->player = &g_player_dummy;
	env->player_state = &g_player_state_dummy;
	env->body_vm = &g_body_vm;
	env->head_vm = &g_head_vm;
	env->frame_speed = 1.0f;
}

static void MakeLaser(LineLaser* laser) {
	std::memset(laser, 0, sizeof(*laser));
	laser->position.x = 0.0f;
	laser->position.y = 100.0f;
	laser->angle = 0.0f;
	laser->length = 10.0f;
	laser->width = 8.0f;
	laser->grow_speed = 4.0f;
	laser->length_limit = 100.0f;
	laser->total_length = 0.0f;
	g_sprite.width = 16.0f;
	g_sprite.height = 8.0f;
	std::memset(&g_body_vm, 0, sizeof(g_body_vm));
	std::memset(&g_head_vm, 0, sizeof(g_head_vm));
	g_body_vm.sprite = &g_sprite;
	g_head_vm.sprite = &g_sprite;
}

// ---------------------------------------------------------------------------
// Flag dispatch
// ---------------------------------------------------------------------------

static void TestFlagDispatchOrder() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.flags = 0x1u | 0x10u | 0x20u | 0x40u | 0x100u | 0x80u | 0x400u |
	              0x100000u | 0x200000u | 0x4000000u;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	// Retail order: commands, then 1, 0x10, 0x20, 0x40, 0x100, 0x80,
	// bounce mask, 0x100000, 0x200000, 0x4000000.
	CHECK(std::strcmp(g_calls, "c1a2th8bklm") == 0);

	// Any single bit of the 0x08000C00 mask reaches the bounce slot.
	ResetRecorders();
	laser.flags = 0x800u;
	LaserLine_Update(&laser, &env);
	CHECK(std::strcmp(g_calls, "cb") == 0);
	ResetRecorders();
	laser.flags = 0x8000000u;
	LaserLine_Update(&laser, &env);
	CHECK(std::strcmp(g_calls, "cb") == 0);

	// No flags: only the command stream runs.
	ResetRecorders();
	laser.flags = 0;
	LaserLine_Update(&laser, &env);
	CHECK(std::strcmp(g_calls, "c") == 0);
}

static void TestFlagsReReadAfterSlots() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	env.on_flag_bounce = HookBounceClearsBits;
	MakeLaser(&laser);
	ResetRecorders();
	// The bounce clears 0x400/0x800/0x8000000; later bits still dispatch
	// from the live word.
	laser.flags = 0x400u | 0x200000u;
	LaserLine_Update(&laser, &env);
	CHECK(std::strcmp(g_calls, "cbl") == 0);
	CHECK(laser.flags == 0x200000u);
}

static void TestFlashTimerCountdown() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);

	// Positive flash timer: advanced by -1, flag kept.
	ResetRecorders();
	laser.flags = 0x8000u;
	laser.flash_timer.current = 3;
	laser.flash_timer.elapsed = 3.0f;
	LaserLine_Update(&laser, &env);
	CHECK(g_advance_count == 1);
	CHECK(g_advanced_timer == &laser.flash_timer);
	CHECK(NearlyEqual(g_advanced_delta, -1.0f, 0.0f));
	CHECK((laser.flags & 0x8000u) != 0);

	// Expired flash timer: the flag toggles off without an advance.
	ResetRecorders();
	laser.flags = 0x8000u;
	laser.flash_timer.current = 0;
	LaserLine_Update(&laser, &env);
	CHECK(g_advance_count == 0);
	CHECK((laser.flags & 0x8000u) == 0);
}

// ---------------------------------------------------------------------------
// Growth and tail motion
// ---------------------------------------------------------------------------

static void TestGrowthPhase() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 10.0f;
	laser.length_limit = 100.0f;
	laser.grow_speed = 4.0f;
	laser.velocity.x = 2.0f;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	// Growing: length advances, the origin does not move yet.
	CHECK(NearlyEqual(laser.length, 14.0f, 1e-4f));
	CHECK(NearlyEqual(laser.position.x, 0.0f, 0.0f));
	CHECK(NearlyEqual(laser.traveled, 0.0f, 0.0f));

	// The growth clamps at the limit.
	laser.length = 99.0f;
	LaserLine_Update(&laser, &env);
	CHECK(NearlyEqual(laser.length, 100.0f, 1e-4f));

	// Frame speed scales the growth step.
	laser.length = 10.0f;
	env.frame_speed = 0.5f;
	LaserLine_Update(&laser, &env);
	CHECK(NearlyEqual(laser.length, 12.0f, 1e-4f));
}

static void TestExtendedPhaseMovesAndConsumes() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 100.0f;
	laser.length_limit = 100.0f;
	laser.grow_speed = 4.0f;
	laser.velocity.x = 2.0f;
	laser.velocity.y = -1.0f;
	laser.velocity.z = 0.5f;
	laser.total_length = 0.0f; // endless: no consumption clamp
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(NearlyEqual(laser.traveled, 4.0f, 1e-4f));
	CHECK(NearlyEqual(laser.position.x, 2.0f, 1e-4f));
	CHECK(NearlyEqual(laser.position.y, 99.0f, 1e-4f));
	CHECK(NearlyEqual(laser.position.z, 0.5f, 1e-4f));
	CHECK(NearlyEqual(laser.length, 100.0f, 0.0f));

	// A finite total length shortens the beam once consumed past it.
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 100.0f;
	laser.length_limit = 100.0f;
	laser.grow_speed = 4.0f;
	laser.traveled = 30.0f;
	laser.total_length = 120.0f;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(NearlyEqual(laser.traveled, 34.0f, 1e-4f));
	CHECK(NearlyEqual(laser.length, 86.0f, 1e-4f));
	CHECK(NearlyEqual(laser.length_limit, 86.0f, 1e-4f));

	// Fully consumed: retire with 1 before any cull/collision work.
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 2.0f;
	laser.length_limit = 2.0f;
	laser.grow_speed = 4.0f;
	laser.traveled = 118.0f;
	laser.total_length = 120.0f;
	CHECK(LaserLine_Update(&laser, &env) == 1);
	CHECK(g_viewport_calls == 0);
	CHECK(g_tick_count == 0);
}

// ---------------------------------------------------------------------------
// Hold timer and off-screen cull
// ---------------------------------------------------------------------------

static void TestHoldTimerSkipsCull() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.hold_timer.current = 2;
	laser.hold_timer.elapsed = 2.0f;
	g_viewport_results[0] = 1;
	g_viewport_results[1] = 1;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(g_advance_count == 1);
	CHECK(g_advanced_timer == &laser.hold_timer);
	CHECK(NearlyEqual(g_advanced_delta, -1.0f, 0.0f));
	CHECK(g_viewport_calls == 0);
}

static void TestOffscreenCull() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);

	// Both endpooints off-screen: retire.
	ResetRecorders();
	laser.angle = 0.0f;
	laser.length = 10.0f;
	laser.length_limit = 100.0f;
	laser.grow_speed = 0.0f;
	laser.width = 8.0f;
	g_viewport_results[0] = 1;
	g_viewport_results[1] = 1;
	CHECK(LaserLine_Update(&laser, &env) == 1);
	CHECK(g_viewport_calls == 2);
	// First test: the tail with (width, width) radii.
	CHECK(NearlyEqual(g_viewport_points[0][0], 0.0f, 1e-4f));
	CHECK(NearlyEqual(g_viewport_points[0][1], 100.0f, 1e-4f));
	CHECK(NearlyEqual(g_viewport_radii[0][0], 8.0f, 0.0f));
	CHECK(NearlyEqual(g_viewport_radii[0][1], 8.0f, 0.0f));
	// Second test: the head = tail + polar(angle, length).
	CHECK(NearlyEqual(g_viewport_points[1][0], 10.0f, 1e-4f));
	CHECK(NearlyEqual(g_viewport_points[1][1], 100.0f, 1e-4f));

	// Tail on-screen short-circuits the head test.
	ResetRecorders();
	g_viewport_results[0] = 0;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(g_viewport_calls == 1);

	// Head on-screen keeps the laser alive.
	ResetRecorders();
	g_viewport_results[0] = 1;
	g_viewport_results[1] = 0;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(g_viewport_calls == 2);
}

// ---------------------------------------------------------------------------
// Player interaction
// ---------------------------------------------------------------------------

static void TestCollisionGates() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);

	// Too short: no classification.
	ResetRecorders();
	laser.length = 16.0f;
	laser.length_limit = 200.0f;
	laser.grow_speed = 0.0f;
	laser.width = 8.0f;
	LaserLine_Update(&laser, &env);
	CHECK(g_classify_calls == 0);

	// Too narrow: no classification.
	ResetRecorders();
	laser.length = 50.0f;
	laser.width = 3.0f;
	LaserLine_Update(&laser, &env);
	CHECK(g_classify_calls == 0);

	// Narrow beam: half width is width * 0.5.
	ResetRecorders();
	laser.length = 50.0f;
	laser.width = 8.0f;
	laser.angle = 0.0f;
	LaserLine_Update(&laser, &env);
	CHECK(g_classify_calls == 1);
	CHECK(g_classify_player == &g_player_dummy);
	CHECK(NearlyEqual(g_classify_half_width, 4.0f, 1e-4f));
	CHECK(NearlyEqual(g_classify_reach, 40.0f, 1e-4f));
	// Probe sits 10% along the beam from the tail.
	CHECK(NearlyEqual(g_classify_probe[0], 5.0f, 1e-4f));
	CHECK(NearlyEqual(g_classify_probe[1], 100.0f, 1e-4f));

	// Wide beam (>= 32): half width becomes (width - 16) * 0.5.
	ResetRecorders();
	laser.width = 40.0f;
	LaserLine_Update(&laser, &env);
	CHECK(g_classify_calls == 1);
	CHECK(NearlyEqual(g_classify_half_width, 12.0f, 1e-4f));
}

static void TestDirectHit() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 50.0f;
	laser.length_limit = 200.0f;
	laser.grow_speed = 0.0f;
	laser.width = 8.0f;
	g_classify_result = 1;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(g_hit_calls == 1);
	CHECK(g_hit_laser == &laser);
	CHECK(g_hit_player_state == &g_player_state_dummy);
	CHECK(NearlyEqual(g_hit_box[0], 32.0f, 0.0f));
	CHECK(NearlyEqual(g_hit_box[1], 32.0f, 0.0f));
	CHECK(NearlyEqual(g_hit_box[2], 0.0f, 0.0f));
	CHECK(g_hit_flag == 0);
	CHECK(g_graze_calls == 0);
	CHECK(g_sound_calls == 0);
}

static void TestGrazeEveryFifthFrame() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 50.0f;
	laser.length_limit = 200.0f;
	laser.grow_speed = 0.0f;
	laser.width = 8.0f;
	laser.position.x = -12.0f;
	g_classify_result = 2;

	// Frame 10: graze fires with the collision half width and sound 28.
	laser.age.current = 10;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(g_hit_calls == 0);
	CHECK(g_graze_calls == 1);
	CHECK(g_graze_player_state == &g_player_state_dummy);
	CHECK(NearlyEqual(g_graze_half_width, 4.0f, 1e-4f));
	CHECK(g_sound_calls == 1);
	CHECK(g_sound_id == 28);
	CHECK(NearlyEqual(g_sound_x, -12.0f, 0.0f));

	// Frame 11: the modulo gate suppresses the graze.
	ResetRecorders();
	g_classify_result = 2;
	laser.age.current = 11;
	LaserLine_Update(&laser, &env);
	CHECK(g_graze_calls == 0);
	CHECK(g_sound_calls == 0);
}

// ---------------------------------------------------------------------------
// Animation VMs
// ---------------------------------------------------------------------------

static void TestVmScalingAndTicks() {
	LineLaserEnv env;
	LineLaser laser;
	MakeEnv(&env);
	MakeLaser(&laser);
	ResetRecorders();
	laser.length = 50.0f;
	laser.length_limit = 200.0f;
	laser.grow_speed = 0.0f;
	laser.width = 12.0f;
	g_sprite.width = 16.0f;
	g_sprite.height = 8.0f;
	laser.traveled = 0.0f;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	// growth_x = width / sprite height, growth_y = length / sprite width.
	CHECK(NearlyEqual(g_body_vm.growth_x, 12.0f / 8.0f, 1e-5f));
	CHECK(NearlyEqual(g_body_vm.growth_y, 50.0f / 16.0f, 1e-5f));
	CHECK((g_body_vm.flags & 0x8u) != 0);
	// Head VM ticks while the tail has not moved.
	CHECK(g_tick_count == 2);
	CHECK(g_ticked[0] == &g_body_vm);
	CHECK(g_ticked[1] == &g_head_vm);

	// Once the tail travels, only the body VM ticks.
	ResetRecorders();
	laser.length = 200.0f; // extended phase accumulates traveled
	laser.grow_speed = 4.0f;
	CHECK(LaserLine_Update(&laser, &env) == 0);
	CHECK(NearlyEqual(laser.traveled, 4.0f, 1e-4f));
	CHECK(g_tick_count == 1);
	CHECK(g_ticked[0] == &g_body_vm);
}


// ---------------------------------------------------------------------------
// 0x0041F400 cancel sweep
// ---------------------------------------------------------------------------

static LaserSweepVm g_sweep_vms[16];
static int g_sweep_alloc_count;
static void* g_sweep_alloc_manager;
static LaserSweepVm* HookAllocateVm(void* manager) {
	g_sweep_alloc_manager = manager;
	int index = g_sweep_alloc_count < 15 ? g_sweep_alloc_count : 15;
	++g_sweep_alloc_count;
	g_sweep_vms[index].flags = 0x1u; // pre-set bits must survive the |=
	g_sweep_vms[index].pending_word = 77;
	return &g_sweep_vms[index];
}

static int g_load_script_count;
static LaserSweepVm* g_load_script_vm;
static void* g_load_script_file;
static int g_load_script_id;
static void HookLoadScript(LaserSweepVm* vm, void* file, int script_id) {
	++g_load_script_count;
	g_load_script_vm = vm;
	g_load_script_file = file;
	g_load_script_id = script_id;
}

static int g_register_count;
static LaserSweepVm* g_register_vm;
static void* g_register_manager;
static void HookRegisterVm(LaserSweepVm* vm, void* manager) {
	++g_register_count;
	g_register_vm = vm;
	g_register_manager = manager;
}

static int g_item_count;
static void* g_item_manager;
static float g_item_points[8][2];
static int g_item_kind;
static int g_item_id;
static float g_item_angle;
static float g_item_speed;
static void HookSpawnItem(void* manager, const float* point, int kind, int id,
                          float angle, float speed) {
	int index = g_item_count < 7 ? g_item_count : 7;
	++g_item_count;
	g_item_manager = manager;
	g_item_points[index][0] = point[0];
	g_item_points[index][1] = point[1];
	g_item_kind = kind;
	g_item_id = id;
	g_item_angle = angle;
	g_item_speed = speed;
}

static int g_anm_manager_dummy;
static int g_anm_file_dummy;
static int g_item_manager_dummy;

static void MakeSweepEnv(LaserSweepEnv* env) {
	std::memset(env, 0, sizeof(*env));
	env->set_polar = HookSetPolar;
	env->allocate_vm = HookAllocateVm;
	env->load_script = HookLoadScript;
	env->register_vm = HookRegisterVm;
	env->spawn_item = HookSpawnItem;
	env->anm_manager = &g_anm_manager_dummy;
	env->anm_file = &g_anm_file_dummy;
	env->item_manager = &g_item_manager_dummy;
	g_sweep_alloc_count = 0;
	g_load_script_count = 0;
	g_register_count = 0;
	g_item_count = 0;
}

static void TestSweepShortBeamRetires() {
	LaserSweepEnv env;
	LineLaser laser;
	MakeSweepEnv(&env);
	MakeLaser(&laser);
	laser.length = 12.0f;
	CHECK(LaserLine_SweepIntoItems(&laser, 1, &env) == 0);
	CHECK(laser.retired == 1);
	CHECK(g_sweep_alloc_count == 0);
	CHECK(g_item_count == 0);
}

static void TestSweepSpawnsAlongBeam() {
	LaserSweepEnv env;
	LineLaser laser;
	MakeSweepEnv(&env);
	MakeLaser(&laser);
	laser.position.x = 0.0f;
	laser.position.y = 100.0f;
	laser.position.z = 7.0f;
	laser.angle = 0.0f;
	laser.length = 60.0f;
	laser.colour = 2;
	// Steps at x = 6, 18, 30, 42 (distance 6 + 12k while distance+6 < 60).
	CHECK(LaserLine_SweepIntoItems(&laser, 1, &env) == 4);
	CHECK(laser.retired == 1);
	CHECK(g_sweep_alloc_count == 4);
	CHECK(g_sweep_alloc_manager == &g_anm_manager_dummy);
	CHECK(g_load_script_count == 4);
	CHECK(g_load_script_file == &g_anm_file_dummy);
	CHECK(g_load_script_id == 2 * 2 + 17);
	CHECK(g_register_count == 4);
	CHECK(g_register_vm == &g_sweep_vms[3]);
	CHECK(g_register_manager == &g_anm_manager_dummy);
	// The sparkle keeps pre-set flag bits, clears +0x20, and is placed in
	// screen space.
	CHECK((g_sweep_vms[0].flags & 0x40000000u) != 0);
	CHECK((g_sweep_vms[0].flags & 0x1u) != 0);
	CHECK(g_sweep_vms[0].pending_word == 0);
	CHECK(NearlyEqual(g_sweep_vms[0].position[0], 230.0f, 1e-4f));
	CHECK(NearlyEqual(g_sweep_vms[0].position[1], 116.0f, 1e-4f));
	CHECK(NearlyEqual(g_sweep_vms[0].position[2], 7.0f, 1e-4f));
	CHECK(NearlyEqual(g_sweep_vms[3].position[0], 266.0f, 1e-4f));
	// Items drop at the world points with kind 8, id -1, straight down.
	CHECK(g_item_count == 4);
	CHECK(g_item_manager == &g_item_manager_dummy);
	CHECK(NearlyEqual(g_item_points[0][0], 6.0f, 1e-4f));
	CHECK(NearlyEqual(g_item_points[0][1], 100.0f, 1e-4f));
	CHECK(NearlyEqual(g_item_points[3][0], 42.0f, 1e-4f));
	CHECK(g_item_kind == 8);
	CHECK(g_item_id == -1);
	CHECK(NearlyEqual(g_item_angle, -1.5707964f, 1e-6f));
	CHECK(NearlyEqual(g_item_speed, 0.6f, 1e-6f));
}

static void TestSweepSkipsOffscreenAndItems() {
	LaserSweepEnv env;
	LineLaser laser;
	MakeSweepEnv(&env);
	MakeLaser(&laser);
	// Beam runs off the right edge: x = 196 passes the 16-unit sparkle
	// bound (196 - 16 < 192) but x = 208 does not.
	laser.position.x = 190.0f;
	laser.position.y = 100.0f;
	laser.angle = 0.0f;
	laser.length = 30.0f;
	CHECK(LaserLine_SweepIntoItems(&laser, 1, &env) == 2);
	CHECK(g_sweep_alloc_count == 1);
	CHECK(g_item_count == 1);
	// spawn_items == 0 suppresses the drops but not the sparkles.
	MakeSweepEnv(&env);
	CHECK(LaserLine_SweepIntoItems(&laser, 0, &env) == 2);
	CHECK(g_sweep_alloc_count == 1);
	CHECK(g_item_count == 0);
}

int main() {
	TestFlagDispatchOrder();
	TestFlagsReReadAfterSlots();
	TestFlashTimerCountdown();
	TestGrowthPhase();
	TestExtendedPhaseMovesAndConsumes();
	TestHoldTimerSkipsCull();
	TestOffscreenCull();
	TestCollisionGates();
	TestDirectHit();
	TestGrazeEveryFifthFrame();
	TestVmScalingAndTicks();
	TestSweepShortBeamRetires();
	TestSweepSpawnsAlongBeam();
	TestSweepSkipsOffscreenAndItems();

	if (g_failures != 0) {
		std::printf("%d check(s) failed\n", g_failures);
		return 1;
	}
	std::printf("recovery_batch23_test passed\n");
	return 0;
}
