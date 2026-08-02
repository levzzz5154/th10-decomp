// Tests for the batch 10 readable reconstructions.

#include "th10/game/bullet_manager.hpp"
#include "th10/game/effect_accel.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/enemy_motion_steps.hpp"
#include "th10/game/name_entry.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/replay_progress.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/game/score_tasks.hpp"
#include "th10/game/spell_card_end.hpp"
#include "th10/game/spell_timer.hpp"
#include "th10/game/stage_background.hpp"
#include "th10/platform/gdi_surface.hpp"
#include "th10/platform/joystick_property.hpp"
#include "th10/render/anm_blend_state.hpp"
#include "th10/render/anm_clip_quad.hpp"
#include "th10/render/texture_stage_reset.hpp"
#include "th10/script/ecl_name_table.hpp"
#include "th10/util/scalars.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Retail globals consumed by the linked manager/scheduler/entity sources.
uint32_t DAT_00491be4 = 0;
uint32_t DAT_00492274 = 0;
uint32_t DAT_004776f4 = 0;
uint32_t DAT_0047770c = 0;
uint32_t DAT_00477810 = 0;
uint32_t DAT_00474e36 = 0;
uint32_t DAT_00491ff4 = 0;
uint32_t DAT_00474ca0 = 0;
uint32_t DAT_00476f78 = 0;
unsigned char DAT_0049231c = 0;
void* g_pGameStateManager = 0;
float DAT_00470b04 = 0.0f;
float DAT_00470b0c = 1.0f;
float _DAT_00470b64 = 1.01f;
float _DAT_00470b68 = 0.99f;
float DAT_00470b38 = 448.0f;
float DAT_00470b3c = 192.0f;
float DAT_00470b40 = -192.0f;
float DAT_00470b5c = 384.0f;

extern "C" void* operator_new(uint32_t size) {
    return std::malloc(size);
}
extern "C" void _free(void* memory) {
    std::free(memory);
}
extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

int* ResourceManager_FindResource(int, void*, const char*) {
    return 0;
}

namespace {

long long FloatToLong(float value) { return (long long)value; }

ClockEnv MakeClockEnv() {
	ClockEnv env;
	env.span_low = 0.99f;
	env.span_high = 1.01f;
	env.frame_step = 1.0f;
	env.float_to_long = &FloatToLong;
	return env;
}

// --- Input_SetJoystickProperty (0x0044C7E0) ---------------------------------

int g_joy_prepare_result = 0;
int g_joy_set_result = 0;
JoyPropertyBlock g_joy_block;

int JoyPrepare(void*) { return g_joy_prepare_result; }
int JoySetProperty(void*, const JoyPropertyBlock* block) {
	g_joy_block = *block;
	return g_joy_set_result;
}

void TestJoystickProperty() {
	void* device = 0;
	JoyPropertyEnv env = {};
	env.device_slot = &device;
	env.prepare_device = &JoyPrepare;
	env.set_property = &JoySetProperty;

	// Missing device fails with the retail HRESULT.
	assert(Input_SetJoystickProperty(0x400, 2, &env) == (int)0x800401F0u);

	int cookie = 0;
	device = &cookie;
	g_joy_prepare_result = -5;
	assert(Input_SetJoystickProperty(0x400, 2, &env) == -5);

	g_joy_prepare_result = 0;
	assert(Input_SetJoystickProperty(0x400, 2, &env) == 0);
	assert(g_joy_block.size == 0x24 && g_joy_block.header_size == 1);
	// value = (range << 16) | (Half)((range >> 3) * scale)
	assert(g_joy_block.value == ((0x400u << 16) | (Half)(0x80 * 2)));
}

// --- Enemy_Destroy (0x0040DAE0) ---------------------------------------------

int g_free_calls = 0;
void* g_freed[8];
void FreeBlock(void* block) { g_freed[g_free_calls++] = block; }

void TestEnemyDestroy() {
	int live_vt = 0;
	int dead_vt = 0;

	DtorEnemy enemy = {};
	DtorEnemy other = {};
	DtorManager manager = {};
	void* slots[4] = {};
	slots[2] = &enemy;
	manager.slots = slots;

	// Ring: other <-> enemy, head = other, tail = enemy.
	manager.head = &other.node;
	manager.tail = &enemy.node;
	manager.count = 2;
	other.node.next = &enemy.node;
	enemy.node.prev = &other.node;

	enemy.slot_flags = 0x8000;
	enemy.slot_index = 2;

	// Handle 7 lives in list B; its group has a parentless leader with one
	// child, so both get the cancel flag.
	EnemyRef leader = {};
	EnemyRef child = {};
	leader.id = 7;
	RefNode child_node = {&child, 0};
	leader.children = &child_node;
	RefNode list_b = {&leader, 0};

	EnemyRef decoy = {};
	decoy.id = 99;
	RefNode list_a = {&decoy, 0};

	enemy.handles[0] = 7;
	enemy.handles[9] = 12345; // not found anywhere: ignored

	// Effect registry focuses this enemy and references it in two slots.
	void* focus = &enemy;
	Byte focus_flag = 1;
	EffectSlotOwner effect_slots[3] = {};
	effect_slots[0].owner = &enemy;
	effect_slots[2].owner = &enemy;
	EffectRegistry effects = {&focus, &focus_flag, effect_slots, 3};

	// Allocation chain with two blocks.
	int payload_a = 0;
	int payload_b = 0;
	ChainAlloc chain_b = {&payload_b, 0};
	ChainAlloc chain_a = {&payload_a, &chain_b};
	enemy.chain = &chain_a;

	DtorEnv env = {};
	env.manager = &manager;
	env.search_list_a = &list_a;
	env.search_list_b = &list_b;
	env.effects = &effects;
	env.free_block = &FreeBlock;
	env.live_vtable = &live_vt;
	env.dead_vtable = &dead_vt;

	Enemy_Destroy(&enemy, &env);

	assert(manager.tail == &other.node);
	assert(other.node.next == 0);
	assert(manager.count == 1);
	assert(slots[2] == 0);
	assert((leader.flags & 0x4000000u) != 0);
	assert((child.flags & 0x4000000u) != 0);
	assert((decoy.flags & 0x4000000u) == 0);
	assert(enemy.handles[0] == 0 && enemy.handles[9] == 0);
	assert(focus == 0 && focus_flag == 0);
	assert(effect_slots[0].owner == 0 && effect_slots[2].owner == 0);
	assert(effect_slots[1].owner == 0);
	assert(enemy.vtable == &dead_vt);
	assert(g_free_calls == 4);
	assert(g_freed[0] == &payload_a && g_freed[1] == &chain_a);
	assert(g_freed[2] == &payload_b && g_freed[3] == &chain_b);
}

// --- EclNameTable_Register / EclArchive_LoadFile ----------------------------

Byte g_arena[0x2000];
unsigned int g_arena_used = 0;
int g_release_count = 0;
void* g_released = 0;

void* ArenaAllocate(unsigned int size) {
	void* result = g_arena + g_arena_used;
	g_arena_used = (g_arena_used + size + 15u) & ~15u;
	return result;
}
void ArenaRelease(void* block) {
	++g_release_count;
	g_released = block;
}

void BuildScript(Byte* script, const char* const* names, int count) {
	std::memset(script, 0, 0x100);
	*(Word*)script = 0x54504353u; // "SCPT"
	*(short*)(script + 4) = 1;
	*(Half*)(script + 6) = 0x10; // offsets start at 0x34
	*(Half*)(script + 0x10) = (Half)count;
	Word* offsets = (Word*)(script + 0x34);
	char* names_out = (char*)(offsets + count);
	for (int i = 0; i < count; ++i) {
		offsets[i] = 0xC0 + (Word)i * 4; // arbitrary body offsets
		std::strcpy(names_out, names[i]);
		names_out += std::strlen(names[i]) + 1;
	}
}

void TestEclNameTable() {
	static Byte script_a[0x100];
	static Byte script_b[0x100];
	const char* names_a[2] = {"boss", "main"};
	const char* names_b[2] = {"alpha", "zeta"};
	BuildScript(script_a, names_a, 2);
	BuildScript(script_b, names_b, 2);

	EclTable table = {};
	EclNameEnv env = {&ArenaAllocate, &ArenaRelease};

	// Bad magic is rejected and the slot cleared.
	static Byte bogus[0x100];
	std::memset(bogus, 0, sizeof(bogus));
	assert(EclNameTable_Register(&table, bogus, &env) == -1);
	assert(table.files[0] == 0);

	// First registration bulk-fills.
	assert(EclNameTable_Register(&table, script_a, &env) == 0);
	assert(table.total_count == 2);
	assert(std::strcmp(table.entries[0].name, "boss") == 0);
	assert(std::strcmp(table.entries[1].name, "main") == 0);
	assert(table.entries[0].body == script_a + 0xC0);
	assert(table.entries[1].body == script_a + 0xC4);

	// Second registration merges sorted: alpha, boss, main, zeta.
	table.file_index = 1;
	void* old_entries = table.entries;
	assert(EclNameTable_Register(&table, script_b, &env) == 0);
	assert(table.total_count == 4);
	assert(g_release_count == 1 && g_released == old_entries);
	assert(std::strcmp(table.entries[0].name, "alpha") == 0);
	assert(std::strcmp(table.entries[1].name, "boss") == 0);
	assert(std::strcmp(table.entries[2].name, "main") == 0);
	assert(std::strcmp(table.entries[3].name, "zeta") == 0);
	assert(table.entries[0].body == script_b + 0xC0);
	assert(table.entries[3].body == script_b + 0xC4);
}

Byte* g_read_file_result = 0;
char g_path_buffer[64];
Byte* ReadFileStub(unsigned int*, int) { return g_read_file_result; }

void TestEclLoadFile() {
	static Byte script[0x100];
	const char* names[1] = {"entry"};
	BuildScript(script, names, 1);

	EclTable table = {};
	EclLoadEnv env = {};
	env.path_buffer = g_path_buffer;
	env.read_file = &ReadFileStub;
	env.table_env.allocate = &ArenaAllocate;
	env.table_env.release = &ArenaRelease;

	g_read_file_result = script;
	assert(EclArchive_LoadFile(&table, "stage1.ecl", &env) == 0);
	assert(std::strcmp(g_path_buffer, "stage1.ecl") == 0);
	assert(table.total_count == 1);

	// A missing file propagates as -1.
	EclTable table2 = {};
	g_read_file_result = 0;
	assert(EclArchive_LoadFile(&table2, "missing.ecl", &env) == -1);
}

// --- SpellTimer_Update (0x004127A0) ------------------------------------------

void TestSpellTimer() {
	float scale = 1.0f;
	int hud_seconds = -1;
	int bonus_pool = 20000;
	Word option_a = 0xFFFFFFFFu;
	Word option_b = 0xFFFFFFFFu;

	SpellPlayer player = {};
	player.flags = 0xFFFFFFFFu & ~8u;
	player.invuln_timer = 100;
	player.charge = 55;
	Word dummy = 0;
	for (int i = 0; i < 7; ++i) player.option_flags[i] = &dummy;
	player.option_flags[0] = &option_a;
	player.option_flags[6] = &option_b;

	SpellHost host = {};
	host.flags = 0x10000u;
	for (int i = 0; i < 8; ++i) host.entries[i].start_frame = -1;

	SpellTimerEnv env = {};
	env.hud_seconds_display = &hud_seconds;
	env.bonus_pool = &bonus_pool;
	env.player = &player;
	env.frame_scale = &scale;
	env.clock_env = MakeClockEnv();

	// All consumed: nothing to do.
	assert(SpellTimer_Update(&host, &env) == 0);

	// Phase 1: capture when the main frame reaches the start frame.
	host.entries[2].start_frame = 100;
	host.entries[2].end_frame = 0;
	host.entries[2].capture_bonus = 777;
	host.main_frame = 100;
	assert(SpellTimer_Update(&host, &env) == 777);
	assert(host.entries[2].start_frame == -1);
	assert(host.main_frame == 100);
	assert((host.flags & 0x10000u) == 0);
	assert(host.clock.clock.frame == 0 && host.clock.clock.previous == -1);
	assert((host.clock.flags & 1u) != 0);

	// Phase 2: countdown display without timeout.
	host.entries[4].start_frame = 200;
	host.entries[4].end_frame = 600;
	host.entries[4].timeout_reward = 55;
	host.main_frame = 300;
	host.clock.clock.frame = 240;
	assert(SpellTimer_Update(&host, &env) == 0);
	assert(hud_seconds == 6); // (600-240+59)/60 = 6
	assert(host.entries[4].start_frame == 200);

	// Phase 2: timeout consumes the entry and decays the pool.
	host.clock.clock.frame = 600;
	assert(SpellTimer_Update(&host, &env) == 55);
	assert(host.entries[4].start_frame == -1);
	assert(host.main_frame == 200);
	assert((host.flags & 0x10000u) != 0);
	assert(bonus_pool == 17000);
	assert(player.charge == 0);
	assert((player.flags & 2u) == 0);
	assert((option_a & 2u) == 0 && (option_b & 2u) == 0);

	// Pool floors at 5000.
	bonus_pool = 6000;
	host.entries[1].start_frame = 10;
	host.entries[1].end_frame = 20;
	host.clock.clock.frame = 20;
	host.entries[1].timeout_reward = 1;
	assert(SpellTimer_Update(&host, &env) == 1);
	assert(bonus_pool == 5000);
}

// --- BulletRing_Reset (0x0040C730) -------------------------------------------

void TestBulletRingReset() {
	BulletRing ring;
	std::memset(&ring, 0xAB, sizeof(ring));
	ring.flags = 0xFFFFFFFFu;
	BulletRing_Reset(&ring);
	assert((ring.flags & 1u) == 0);
	assert(ring.node.next == 0 && ring.node.prev == 0);
	assert(ring.self == &ring);
	assert(ring.sentinel == -1);
	assert(ring.control_flags == 0);
	assert(ring.head == &ring.node && ring.cursor == &ring.node);
	assert(ring.count_a == 0 && ring.count_b == 0);
}

// --- AnmManager_UploadClipQuad (0x004462F0) ----------------------------------

float g_mirror[20];
float g_locked_storage[20];
void* g_locked_target = g_locked_storage;
int g_lock_calls = 0;
int g_unlock_calls = 0;
int g_stream_stride = -1;
void* g_stream_vb = 0;
Word g_device_state[3];

void SetDeviceState(void*, Word a, Word b, Word c) {
	g_device_state[0] = a;
	g_device_state[1] = b;
	g_device_state[2] = c;
}
int LockBuffer(void*, void** pointer_out) {
	++g_lock_calls;
	*pointer_out = g_locked_target;
	return 0;
}
void UnlockBuffer(void*) { ++g_unlock_calls; }
void SetStreamSource(void*, void* vb, int stride) {
	g_stream_vb = vb;
	g_stream_stride = stride;
}

void TestClipQuadUpload() {
	int vb_cookie = 0;
	int device_cookie = 0;
	ClipQuadHost host = {};
	host.vertex_buffer = &vb_cookie;
	ClipQuadEnv env = {};
	env.mirror = g_mirror;
	env.device = &device_cookie;
	env.set_device_state = &SetDeviceState;
	env.lock_buffer = &LockBuffer;
	env.unlock_buffer = &UnlockBuffer;
	env.set_stream_source = &SetStreamSource;

	AnmManager_UploadClipQuad(&host, &env);
	assert(host.quad[0] == -128.0f && host.quad[1] == -128.0f);
	assert(host.quad[5] == 128.0f && host.quad[6] == -128.0f);
	assert(host.quad[8] == 1.0f && host.quad[9] == 0.0f);
	assert(host.quad[10] == -128.0f && host.quad[11] == 128.0f);
	assert(host.quad[15] == 128.0f && host.quad[16] == 128.0f);
	assert(host.quad[18] == 1.0f && host.quad[19] == 1.0f);
	assert(std::memcmp(g_mirror, host.quad, sizeof(g_mirror)) == 0);
	assert(std::memcmp(g_locked_storage, host.quad, sizeof(g_locked_storage)) ==
	       0);
	assert(g_lock_calls == 1 && g_unlock_calls == 1);
	assert(g_device_state[0] == 0x50 && g_device_state[2] == 0x102);
	assert(g_stream_vb == &vb_cookie && g_stream_stride == 0x14);
}

// --- ScoreData_CreateGlobal / ReplayTimer_ClampToEnd -------------------------

unsigned int g_create_size = 0;
int g_init_calls = 0;
Byte g_score_block[16];
void* g_allocate_result = g_score_block;

void* CreateAllocate(unsigned int size) {
	g_create_size = size;
	return g_allocate_result;
}
void* CreateInitialize(void* block) {
	++g_init_calls;
	return block;
}

RegisteredClock* g_advance_target = 0;
void AdvanceStub(float amount) {
	g_advance_target->clock.frame += (int)amount;
}

void TestScoreCreateAndReplayClamp() {
	void* global_slot = (void*)1;
	ScoreCreateEnv env = {&CreateAllocate, &CreateInitialize, &global_slot};
	ScoreData_CreateGlobal(&env);
	assert(g_create_size == 0x1DCB4u);
	assert(global_slot == g_score_block && g_init_calls == 1);

	g_allocate_result = 0;
	ScoreData_CreateGlobal(&env);
	assert(global_slot == 0 && g_init_calls == 1);

	// Replay clamp: overshooting the advance pins the clock at frame 0x82.
	float scale = 1.0f;
	RegisteredClock clock = {};
	clock.clock.frame = 0x80;
	g_advance_target = &clock;
	ReplayTimer_ClampToEnd(&clock, 10.0f, &AdvanceStub, &scale);
	assert(clock.clock.frame == 0x82);
	assert(clock.clock.timer == 130.0f);
	assert(clock.clock.previous == 0x81);
	assert((clock.flags & 1u) != 0);

	// Already at the end: no advance at all.
	int before = clock.clock.frame;
	ReplayTimer_ClampToEnd(&clock, 10.0f, &AdvanceStub, &scale);
	assert(clock.clock.frame == before);
}

// --- ScoreTask_Init (0x00413A20) ----------------------------------------------

void* g_task_result = 0;
int g_fatal_calls = 0;
Byte g_score_file[4];
Byte* g_load_result = 0;

void* CreateTask(int size, void*, const char*) {
	return size == 0x1C ? g_task_result : 0;
}
void FatalError(void*, const char*) { ++g_fatal_calls; }
Byte* LoadScoreFile(unsigned int*, int) { return g_load_result; }

void TestScoreTaskInit() {
	float scale = 1.0f;
	char path_buffer[32] = {};
	Byte* preloaded = 0;

	ScoreHost host = {};
	ScoreInitEnv env = {};
	env.create_task = &CreateTask;
	env.task_name = "score";
	env.preloaded_data = &preloaded;
	env.score_path = "score.dat";
	env.path_buffer = path_buffer;
	env.load_file = &LoadScoreFile;
	env.fatal_error = &FatalError;
	env.error_text = "boom";
	env.current_score = 4242;
	env.frame_scale = &scale;

	// Task creation failure is fatal.
	g_task_result = 0;
	assert(ScoreTask_Init(&host, &env) == -1);
	assert(g_fatal_calls == 1);

	// Load path: copies the path and loads the file.
	int task_cookie = 0;
	g_task_result = &task_cookie;
	g_load_result = g_score_file;
	assert(ScoreTask_Init(&host, &env) == 0);
	assert(std::strcmp(path_buffer, "score.dat") == 0);
	assert(host.data == g_score_file);
	assert(host.task == &task_cookie);
	assert(host.hud_a == -1 && host.hud_b == -1);
	assert(host.saved_score == 4242);
	assert(host.clock.clock.frame == 0 && host.clock.clock.previous == -1);

	// Preloaded path: adopts the block and clears the slot.
	Byte preloaded_block[4];
	preloaded = preloaded_block;
	ScoreHost host2 = {};
	assert(ScoreTask_Init(&host2, &env) == 0);
	assert(host2.data == preloaded_block);
	assert(preloaded == 0);

	// Missing score file is fatal.
	preloaded = 0;
	g_load_result = 0;
	ScoreHost host3 = {};
	assert(ScoreTask_Init(&host3, &env) == -1);
	assert(g_fatal_calls == 2);
}

} // namespace

namespace {

// --- NameEntry_DrawCharGrid (0x004224C0) --------------------------------------

char g_glyphs[64];
int g_glyph_count = 0;
Word g_glyph_colors[64];
Word g_grid_color = 0;
int g_name_row_calls = 0;
int g_cursor_calls = 0;
Word g_cursor_color = 0;

void DrawNameRow(void*) { ++g_name_row_calls; }
void DrawCursor(void*) {
	++g_cursor_calls;
	g_cursor_color = g_grid_color;
}
void DrawGlyph(void*, char glyph) {
	g_glyph_colors[g_glyph_count] = g_grid_color;
	g_glyphs[g_glyph_count++] = glyph;
}

void TestNameEntryDrawCharGrid() {
	const char* charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // 26 = 2 full rows
	float row_y = 0.0f;

	NameGridEntry entry = {};
	entry.cursor_index = 3;
	NameGridEnv env = {};
	env.charset = charset;
	env.color_slot = &g_grid_color;
	env.draw_name_row = &DrawNameRow;
	env.draw_cursor = &DrawCursor;
	env.draw_glyph = &DrawGlyph;
	env.line_height = 24.0f;
	env.row_y = &row_y;

	NameEntry_DrawCharGrid(&entry, &env);
	assert(g_name_row_calls == 1 && g_cursor_calls == 1);
	assert(g_cursor_color == 0xFFFFFF00u);
	assert(g_glyph_count == 26);
	assert(g_glyphs[0] == 'A' && g_glyphs[25] == 'Z');
	assert(g_glyph_colors[3] == 0xFFFFFF00u); // highlighted cursor glyph
	assert(g_glyph_colors[2] == 0xFF808080u);
	assert(g_glyph_colors[4] == 0xFF808080u);
	// 26 glyphs wrap after indices 12 and 25 -> two row advances.
	assert(row_y == 320.0f + 2.0f * 24.0f);
	assert(g_grid_color == 0xFFFFFFFFu);
}

// --- ResultScreen_LazyCreateEffects (0x0041FDD0) ------------------------------

ResultEffectVm g_lazy_vm;
int g_lazy_assign_calls = 0;
int g_lazy_register_calls = 0;
Word g_sprite_value = 0;
Word g_sprite_slot = 0;

ResultEffectVm* LazyAcquire() {
	g_lazy_vm.layer = 0;
	g_lazy_vm.flags = 0;
	return &g_lazy_vm;
}
void LazyAssign(ResultEffectVm*, int) { ++g_lazy_assign_calls; }
void LazyRegister(void*) { ++g_lazy_register_calls; }
Word* CloneSprite(void*) { return &g_sprite_value; }

void TestResultScreenLazyCreate() {
	g_sprite_value = 777;

	ResultLazyHost host = {};
	host.stage_a = 1;
	host.stage_b = 1;
	ResultLazyEnv env = {};
	env.acquire_effect = &LazyAcquire;
	env.assign_script = &LazyAssign;
	env.register_front = &LazyRegister;
	env.cached_sprite_slot = &g_sprite_slot;
	env.clone_sprite = &CloneSprite;

	assert(ResultScreen_LazyCreateEffects(&host, &env) == 1);
	assert(host.stage_a == 2 && host.stage_b == 2);
	assert(host.owner_slot == &host);
	assert(g_lazy_vm.layer == 0xF);
	assert((g_lazy_vm.flags & 0x40000000u) != 0);
	assert(g_lazy_assign_calls == 1 && g_lazy_register_calls == 1);
	assert(g_sprite_slot == 777u);
	assert(host.frame == 1);

	// Second call: stages already past 1, only the frame advances.
	assert(ResultScreen_LazyCreateEffects(&host, &env) == 1);
	assert(host.stage_a == 2 && host.stage_b == 2);
	assert(g_lazy_assign_calls == 1);
	assert(host.frame == 2);
}

// --- GdiSurface_Create (0x00436AF0) -------------------------------------------

BitmapRequest g_bitmap_request;
Byte g_dib_bits[64 * 64 * 4];
void* g_dib_result = 0;
int g_release_surface_calls = 0;
int g_dc_cookie = 0;
int g_prev_cookie = 0;

void ReleaseExisting(GdiSurface*) { ++g_release_surface_calls; }
void* CreateDibSection(BitmapRequest* request, void** bits_out) {
	g_bitmap_request = *request;
	*bits_out = g_dib_bits;
	return g_dib_result;
}
void* CreateDc() { return &g_dc_cookie; }
void* SelectObject(void*, void*) { return &g_prev_cookie; }

void TestGdiSurfaceCreate() {
	static const GdiFormat formats[] = {
	    {0x18, 24, {0, 0, 0, 0}},
	    {0x20, 32, {0xFF000000u, 0x00FF0000u, 0x0000FF00u, 0x000000FFu}},
	    {-1, 0, {0, 0, 0, 0}},
	};

	GdiEnv env = {};
	env.release_existing = &ReleaseExisting;
	env.formats = formats;
	env.create_dib_section = &CreateDibSection;
	env.create_dc = &CreateDc;
	env.select_object = &SelectObject;

	GdiSurface surface = {};

	// Unknown format fails after releasing the old surface.
	assert(GdiSurface_Create(&surface, 64, 32, 0x99, &env) == 0);
	assert(g_release_surface_calls == 1);

	// DIB creation failure fails.
	g_dib_result = 0;
	assert(GdiSurface_Create(&surface, 64, 32, 0x20, &env) == 0);

	// 32-bit path: bitfields masks rotated, top-down height quirk.
	int bitmap_cookie = 0;
	g_dib_result = &bitmap_cookie;
	std::memset(g_dib_bits, 0xCD, sizeof(g_dib_bits));
	assert(GdiSurface_Create(&surface, 64, 32, 0x20, &env) == 1);
	assert(g_bitmap_request.width == 64);
	assert(g_bitmap_request.height == -1 - 32);
	assert(g_bitmap_request.planes == 1);
	assert(g_bitmap_request.bit_count == 32);
	assert(g_bitmap_request.compression == 3);
	assert(g_bitmap_request.masks[0] == 0x00FF0000u);
	assert(g_bitmap_request.masks[3] == 0xFF000000u);
	assert(surface.pitch == 64 * 4);
	assert(surface.size_image == (Word)(64 * 4 * 32));
	assert(surface.bits == g_dib_bits);
	assert(g_dib_bits[0] == 0); // zeroed after creation
	assert(surface.dc == &g_dc_cookie);
	assert(surface.bitmap == &bitmap_cookie);
	assert(surface.previous_object == &g_prev_cookie);
	assert(surface.width == 64 && surface.height == 32);
	assert(surface.format == 0x20);

	// 24-bit path: no bitfields, pitch rounds to 4 bytes.
	assert(GdiSurface_Create(&surface, 3, 2, 0x18, &env) == 1);
	assert(g_bitmap_request.compression == 0);
	assert(surface.pitch == (((24 * 3 + 7) / 8 + 3) & ~3));
}

// --- Enemy_BounceStep (0x00407BE0) --------------------------------------------

int g_bounce_sound_calls = 0;
float g_set_velocity_angle = 0.0f;
float g_set_velocity_speed = 0.0f;

void BouncePlaySound(void*, int) { ++g_bounce_sound_calls; }
float NormalizeAngle(float angle, float) {
	const float pi = 3.14159265f;
	while (angle > pi) angle -= 2.0f * pi;
	while (angle < -pi) angle += 2.0f * pi;
	return angle;
}
void SetVelocity(float*, float angle, float speed) {
	g_set_velocity_angle = angle;
	g_set_velocity_speed = speed;
}

void TestEnemyBounceStep() {
	BounceEnv env = {};
	env.min_x = -192.0f;
	env.max_x = 192.0f;
	env.min_y = 0.0f;
	env.max_y = 448.0f;
	env.reflect_low = -384.0f;
	env.reflect_high = 384.0f;
	env.speed_floor = 0.0f;
	env.pi = 3.14159265f;
	env.play_sound = &BouncePlaySound;
	env.normalize_angle = &NormalizeAngle;
	env.set_velocity = &SetVelocity;

	// Inside the field: untouched.
	BounceEnemy enemy = {};
	enemy.x = 0.0f;
	enemy.y = 100.0f;
	enemy.sound_id = -1;
	Enemy_BounceStep(&enemy, &env);
	assert(enemy.bounce_count == 0 && g_bounce_sound_calls == 0);

	// Left wall: x reflects around reflect_low, angle mirrored, count++.
	enemy.x = -200.0f;
	enemy.y = 100.0f;
	enemy.angle = 0.5f;
	enemy.speed = 2.0f;
	enemy.floor_speed = 3.0f;
	enemy.bounce_limit = 10;
	enemy.sound_id = 1;
	enemy.flags = 0x400u;
	Enemy_BounceStep(&enemy, &env);
	assert(g_bounce_sound_calls == 1);
	assert(enemy.x == -384.0f - -200.0f);
	assert(enemy.bounce_count == 1);
	assert(enemy.speed == 3.0f); // floored
	assert(g_set_velocity_speed == 3.0f);

	// Top wall: y mirrors to -y, angle negated.
	BounceEnemy enemy2 = {};
	enemy2.x = 0.0f;
	enemy2.y = -10.0f;
	enemy2.angle = 1.0f;
	enemy2.speed = 5.0f;
	enemy2.floor_speed = 1.0f;
	enemy2.bounce_limit = 1;
	enemy2.sound_id = -1;
	enemy2.flags = 0x8000400u | 0x400u;
	// 0x8000000 set: vertical bounce suppressed -> position unchanged but
	// still outside, so velocity is refreshed and no bounce is counted.
	Enemy_BounceStep(&enemy2, &env);
	assert(enemy2.y == -10.0f);
	assert(enemy2.bounce_count == 0);

	enemy2.flags = 0x400u;
	Enemy_BounceStep(&enemy2, &env);
	assert(enemy2.y == 10.0f);
	assert(enemy2.angle == -1.0f);
	assert(enemy2.bounce_count == 1);
	// bounce_limit (1) reached: bounce bits cleared.
	assert((enemy2.flags & 0x400u) == 0);

	// Bottom wall requires the 0x400 flag.
	BounceEnemy enemy3 = {};
	enemy3.x = 0.0f;
	enemy3.y = 500.0f;
	enemy3.angle = 0.25f;
	enemy3.speed = 4.0f;
	enemy3.bounce_limit = 10;
	enemy3.sound_id = -1;
	enemy3.flags = 0x400u;
	Enemy_BounceStep(&enemy3, &env);
	assert(enemy3.y == (448.0f - 500.0f) + 448.0f);
	assert(enemy3.bounce_count == 1);
}

// --- AnmManager_ApplyBlendColorWrap (0x004423E0) ------------------------------

int g_flush_calls = 0;
int g_blend_mode = -1;
Word g_texture_factor = 0;
int g_texture_filter = -1;

void StateFlush() { ++g_flush_calls; }
void SetBlendMode(Word mode) { g_blend_mode = (int)mode; }
void SetTextureFactor(Word color) { g_texture_factor = color; }
void SetTextureFilter(Word mode) { g_texture_filter = (int)mode; }

void TestApplyBlendColorWrap() {
	AnmStateCache cache = {};
	cache.cached_blend = 3;
	cache.cached_filter = 0;
	cache.cached_color = 0;

	AnmStateEnv env = {};
	env.flush = &StateFlush;
	env.set_blend_mode = &SetBlendMode;
	env.set_texture_factor = &SetTextureFactor;
	env.set_texture_filter = &SetTextureFilter;

	// blend 0, primary color, bit 31 set.
	AnmBlendVmState vm = {};
	vm.flags = 0x80000000u; // blend bits 0, bit 31 set
	vm.color_primary = 0x11223344u;
	vm.color_secondary = 0x99887766u;

	AnmManager_ApplyBlendColorWrap(&cache, &vm, &env);
	assert(cache.cached_blend == 0 && g_blend_mode == 6);
	assert(cache.cached_color == 0x11223344u);
	assert(g_texture_factor == 0x11223344u);
	assert(cache.cached_filter == 1 && g_texture_filter == 1);
	assert(g_flush_calls == 3);
	assert(cache.state_changes == 1);

	// Same state again: no flushes, only the counter moves.
	AnmManager_ApplyBlendColorWrap(&cache, &vm, &env);
	assert(g_flush_calls == 3);
	assert(cache.state_changes == 2);

	// Secondary color select + blend 1 -> mode 2; bit 31 cleared -> 2.
	vm.flags = 0x8010u; // secondary color, blend bits = 1
	AnmManager_ApplyBlendColorWrap(&cache, &vm, &env);
	assert(g_blend_mode == 2);
	assert(g_texture_factor == 0x99887766u);
	assert(g_texture_filter == 2);

	// Fade modulation: 0x80 = identity on one channel, 0xFF saturates.
	cache.fade_enabled = 1;
	cache.fade[0] = 0x80; // blue identity
	cache.fade[1] = 0x40; // green halved
	cache.fade[2] = 0xFF; // red nearly x2 (clamped at 0xFF)
	cache.fade[3] = 0x80; // alpha identity
	vm.flags = 0;
	vm.color_primary = 0xFF80FF40u; // a=FF r=80 g=FF b=40
	AnmManager_ApplyBlendColorWrap(&cache, &vm, &env);
	// r = 0xFF*0x80>>7 = 0xFF; g = 0x40*0xFF>>7 = 0x7F; b = 0x80*0x40>>7 = 0x40
	assert(g_texture_factor == 0xFFFF7F40u);
}

// --- Renderer_InitTextureStages (0x0043BFA0) ----------------------------------

int g_stage_calls = 0;
int g_stage_log[16][3];
int g_render_state_id = -1;
int g_render_state_value = -1;
int g_fvf = -1;
int g_draw_stride = -1;
int g_stage_flush_calls = 0;

void StageFlush() { ++g_stage_flush_calls; }
void SetStageState(Word stage, Word id, Word value) {
	g_stage_log[g_stage_calls][0] = (int)stage;
	g_stage_log[g_stage_calls][1] = (int)id;
	g_stage_log[g_stage_calls][2] = (int)value;
	++g_stage_calls;
}
void SetRenderState(Word id, Word value) {
	g_render_state_id = (int)id;
	g_render_state_value = (int)value;
}
void SetFvf(Word fvf) { g_fvf = (int)fvf; }
void DrawQuad(const void*, Word stride) { g_draw_stride = (int)stride; }

void TestInitTextureStages() {
	StageResetCache cache = {};
	StageResetEnv env = {};
	env.flush = &StageFlush;
	env.set_stage_state = &SetStageState;
	env.set_render_state = &SetRenderState;
	env.set_fvf = &SetFvf;
	env.draw_quad = &DrawQuad;

	Renderer_InitTextureStages(&cache, &env);
	assert(g_stage_flush_calls == 1);
	assert(g_stage_calls == 8);
	// First four collapse the stages...
	assert(g_stage_log[0][1] == 4 && g_stage_log[0][2] == 2);
	assert(g_stage_log[3][1] == 2 && g_stage_log[3][2] == 0);
	// ...last four restore modulate.
	assert(g_stage_log[4][1] == 4 && g_stage_log[4][2] == 4);
	assert(g_stage_log[7][1] == 2 && g_stage_log[7][2] == 2);
	assert(g_render_state_id == 0x14 && g_render_state_value == 6);
	assert(g_fvf == 0x44);
	assert(g_draw_stride == 0x14);
	assert(cache.cached_blend == 3);
	assert(cache.cached_a == 0xFF && cache.cached_b == 0xFF);
	assert(cache.cached_c == 0xFF && cache.cached_d == 0);
	assert(cache.cached_color == 0);
}

// --- Effect_AccelStep (0x0041D2C0) --------------------------------------------

void TestEffectAccelStep() {
	ClockEnv clock_env = MakeClockEnv();

	AccelEffect fx = {};
	fx.duration = 10;
	fx.flags = 0x10u;
	fx.velocity[0] = 1.0f;
	fx.velocity[1] = 0.0f;
	fx.accel[0] = 0.5f;
	fx.accel[1] = 0.25f;
	fx.accel[2] = 0.125f;
	fx.aux = 2.0f;
	fx.aux_accel = 1.0f;

	float control = 1.0f;
	fx.clock.control = &control;

	Effect_AccelStep(&fx, 2.0f, 0.1f, &clock_env);
	assert(fx.aux == 4.0f);
	assert(fx.velocity[0] == 2.0f);
	assert(fx.velocity[1] == 0.5f);
	assert(fx.velocity[2] == 0.25f);
	float expected = atan2f(0.5f, 2.0f);
	assert(std::fabs(fx.angle - expected) < 1e-6f);
	assert((fx.flags & 0x10u) != 0);
	assert(fx.clock.frame == 1); // clock advanced

	// Below the component threshold: angle untouched.
	AccelEffect fx2 = {};
	fx2.duration = 10;
	fx2.angle = 9.0f;
	fx2.clock.control = &control;
	Effect_AccelStep(&fx2, 1.0f, 0.5f, &clock_env);
	assert(fx2.angle == 9.0f);

	// Expired: only the flag clears and the clock still ticks.
	AccelEffect fx3 = {};
	fx3.duration = 0;
	fx3.flags = 0xFFu;
	fx3.clock.control = &control;
	Effect_AccelStep(&fx3, 1.0f, 0.1f, &clock_env);
	assert((fx3.flags & 0x10u) == 0);
	assert(fx3.clock.frame == 1);
}

// --- PauseMenu_Open / ResultMenu_Open ----------------------------------------

ResultEffectVm g_menu_vms[8];
int g_menu_vm_count = 0;
int g_menu_assign_calls = 0;
int g_menu_register_calls = 0;
int g_menu_assign_scripts[8];
int g_position_x = -1, g_position_y = -1, g_position_w = -1, g_position_h = -1;
int g_capture_calls = 0;
int g_menu_sound_calls = 0;
const char* g_named_sound = 0;
int g_named_sound_arg = -1;
int g_named_sound_count = 0;
int g_released_script = 0;
int g_release_script_calls = 0;
const char* g_music_path = 0;

ResultEffectVm* MenuAcquire() {
	ResultEffectVm* vm = &g_menu_vms[g_menu_vm_count++];
	vm->layer = 0;
	vm->flags = 0;
	return vm;
}
void MenuAssign(ResultEffectVm*, int script) {
	g_menu_assign_scripts[g_menu_assign_calls++] = script;
}
void MenuRegister(void*) { ++g_menu_register_calls; }
void PositionWindow(OverlayMenu*, int x, int y, int w, int h) {
	g_position_x = x;
	g_position_y = y;
	g_position_w = w;
	g_position_h = h;
}
void CaptureBackground() { ++g_capture_calls; }
void MenuPlaySound(void*, int) { ++g_menu_sound_calls; }
void PlayNamedSound(const char* name, int arg, int) {
	g_named_sound = name;
	g_named_sound_arg = arg;
	++g_named_sound_count;
}
void MenuReleaseScript(void*, Word script) {
	g_released_script = (int)script;
	++g_release_script_calls;
}
void PlayMusic(int, const char* path) { g_music_path = path; }

void FillMenuCommon(OverlayMenuEnv* common, Word* supervisor,
                    Word* hud_handle, float* speed, float* scale) {
	common->supervisor_flags = supervisor;
	common->acquire_effect = &MenuAcquire;
	common->assign_script = &MenuAssign;
	common->register_front = &MenuRegister;
	common->position_window = &PositionWindow;
	common->hud_score_handle = hud_handle;
	common->global_speed = speed;
	common->frame_scale = scale;
}

void TestPauseMenuOpen() {
	Word supervisor = 0;
	Word hud_handle = 77;
	float speed = 0.5f;
	float scale = 1.0f;
	Word active_script = 42;

	OverlayMenu menu = {};
	PauseOpenEnv env = {};
	FillMenuCommon(&env.common, &supervisor, &hud_handle, &speed, &scale);
	env.play_sound = &MenuPlaySound;
	env.play_named_sound = &PlayNamedSound;
	env.capture_background = &CaptureBackground;
	env.active_script_slot = &active_script;
	env.release_script = &MenuReleaseScript;

	PauseMenu_Open(&menu, &env);
	assert(menu.state == 1);
	assert((supervisor & 0x10u) != 0);
	assert(g_menu_vm_count == 2);
	assert(g_menu_vms[0].layer == 0xF && g_menu_vms[1].layer == 0xF);
	assert((g_menu_vms[0].flags & 0x40000000u) != 0);
	assert(g_menu_register_calls == 2);
	assert(menu.owner_primary == &menu && menu.owner_secondary == &menu);
	assert(menu.hud_handle == 77);
	assert(g_position_x == 0x20 && g_position_y == 0x10);
	assert(g_position_w == 0x180 && g_position_h == 0x1C0);
	assert(g_capture_calls == 1);
	assert(g_menu_sound_calls == 1);
	assert(std::strcmp(g_named_sound, "Pause") == 0 && g_named_sound_arg == 6);
	assert(g_release_script_calls == 1 && g_released_script == 42);
	assert(active_script == 0);
	assert(menu.saved_speed == 0.5f);
	assert(speed == 1.0f);
	assert(menu.clock.clock.frame == 0 && menu.clock.clock.previous == -1);
}

void TestResultMenuOpen() {
	Word supervisor = 0;
	Word hud_handle = 5;
	float speed = 2.0f;
	float scale = 1.0f;
	Word pending = 1;
	Word retry_mode = 0;
	Byte score_dirty = 0;

	OverlayMenu menu = {};
	ResultOpenEnv env = {};
	FillMenuCommon(&env.common, &supervisor, &hud_handle, &speed, &scale);
	env.pending_slot = &pending;
	env.config_flags = 0x1000u;
	env.retry_mode_slot = &retry_mode;
	env.play_music = &PlayMusic;
	env.play_named_sound = &PlayNamedSound;
	env.sound_config = 0x10u;
	env.score_dirty_flag = &score_dirty;

	// Pending retry: records the mode and does nothing else.
	int vm_count_before = g_menu_vm_count;
	ResultMenu_Open(&menu, &env);
	assert(retry_mode == 2);
	assert(g_menu_vm_count == vm_count_before);
	assert(score_dirty == 0);

	pending = 0;
	env.config_flags = 0;
	ResultMenu_Open(&menu, &env);
	assert(menu.state == 6);
	assert(std::strcmp(g_music_path, "bgm/th10_17.wav") == 0);
	assert(g_named_sound_count >= 2); // both dummy sounds (0x10 set)
	assert(score_dirty == 1);
	assert(menu.practice_flag == 0);
	assert(menu.saved_speed == 2.0f);
	assert(speed == 1.0f);
}

// --- NameEntry_Init (0x00423570) ----------------------------------------------

int g_find_rank_result = 0;
int g_find_rank_difficulty = -1;
const void* g_find_rank_table = 0;
int* g_rank_difficulty_ptr = 0;
const void** g_rank_table_ptr = 0;
int g_existing_name_calls = 0;

int FindRank() {
	g_find_rank_difficulty = *g_rank_difficulty_ptr;
	g_find_rank_table = *g_rank_table_ptr;
	return g_find_rank_result;
}
void OnExistingName(int) { ++g_existing_name_calls; }

void TestNameEntryInit() {
	int difficulty = 7;
	int difficulty_shadow = 7;
	int extra_table_cookie = 0;
	int normal_table_cookie = 0;
	const void* score_table = &normal_table_cookie;
	g_rank_difficulty_ptr = &difficulty;
	g_rank_table_ptr = &score_table;

	NameEntry entry = {};
	entry.extra_mode = 1;
	NameInitEnv env = {};
	env.difficulty = &difficulty;
	env.difficulty_shadow = &difficulty_shadow;
	env.score_table_slot = &score_table;
	env.extra_table = &extra_table_cookie;
	env.normal_table = &normal_table_cookie;
	env.find_rank = &FindRank;
	env.charset = "ABC";
	env.default_name = "YUKI    ";
	env.on_existing_name = &OnExistingName;

	// Extra-mode swap: find_rank sees difficulty 8 and the extra table,
	// then both are restored.
	g_find_rank_result = 3;
	NameEntry_Init(&entry, &env);
	assert(g_find_rank_difficulty == 8);
	assert(g_find_rank_table == &extra_table_cookie);
	assert(difficulty == 7 && difficulty_shadow == 7);
	assert(score_table == &normal_table_cookie);
	assert(entry.failed == 0);
	assert(entry.rank == 3);
	assert(entry.rank_cap == 0x19);
	assert(entry.active == 1);
	assert(entry.cursor == 0);
	assert(entry.charset_len == 3);
	assert(entry.done_flag == 1);
	assert(std::strcmp(entry.name, "YUKI    ") == 0);
	assert(g_existing_name_calls == 1); // non-blank default name
	assert(entry.name_len == 4);        // trailing spaces trimmed

	// No rank: failed.
	NameEntry entry2 = {};
	g_find_rank_result = -1;
	NameEntry_Init(&entry2, &env);
	assert(entry2.failed == 1);

	// Rank beyond the cap clamps to cap-1; blank name skips the callback.
	NameEntry entry3 = {};
	g_find_rank_result = 0x30;
	env.default_name = "        ";
	int existing_before = g_existing_name_calls;
	NameEntry_Init(&entry3, &env);
	assert(entry3.rank == 0x18);
	assert(g_existing_name_calls == existing_before);
	assert(entry3.name_len == 0);
}

// --- StageBackground_SyncScroll (0x00427960) ----------------------------------

int g_random_value = 100;
int RandomInt() { return g_random_value++; }

void TestStageBackgroundSyncScroll() {
	ScrollAnchor anchors[4] = {};
	int random_pairs[40][2] = {};
	ScrollStage stage = {};
	stage.anchors = anchors;
	stage.random_pairs = random_pairs;
	stage.camera_x = 10.0f;
	stage.camera_y = 20.0f;

	ScrollItem item = {};
	item.index = 2;
	anchors[2].x = 110.0f;
	anchors[2].y = 220.0f;

	ScrollEnv env = {&stage, &RandomInt};

	// Unlocked: relative offset captured from the anchor.
	stage.scroll_locked = 0;
	StageBackground_SyncScroll(&item, &env);
	assert(item.rel_x == 100.0f && item.rel_y == 200.0f);
	assert(item.x == 110.0f && item.y == 220.0f);
	assert(item.last_mode == 0);
	assert(random_pairs[17][0] == 0); // untouched

	// Locked: anchor rewritten from the offset, randoms rerolled for
	// indices 17..23 (= 2*8+1 .. 2*8+7).
	stage.scroll_locked = 1;
	stage.camera_x = 50.0f;
	stage.camera_y = 60.0f;
	StageBackground_SyncScroll(&item, &env);
	assert(anchors[2].x == 150.0f && anchors[2].y == 260.0f);
	assert(item.x == 150.0f && item.y == 260.0f);
	assert(item.last_mode == 1);
	assert(random_pairs[16][0] == 0);
	assert(random_pairs[17][0] == 100 && random_pairs[17][1] == 101);
	assert(random_pairs[23][0] == 112 && random_pairs[23][1] == 113);
	assert(random_pairs[24][0] == 0);
}

// --- SpellCard_OnEnd (0x00409C00) ---------------------------------------------

int g_release_effect_calls = 0;
int g_spell_release_script_calls = 0;
int g_spell_released_scripts[8];
int g_show_bonus_divided = -1;
int g_show_bonus_raw = -1;
int g_per_shot_count = 0;
int g_overall_count = 0;
int g_spell_sound_calls = 0;
Word g_spawned_effect = 4242;

void ReleaseEffect(SpellCard*) { ++g_release_effect_calls; }
void SpellReleaseScript(void*, Word script) {
	g_spell_released_scripts[g_spell_release_script_calls++] = (int)script;
}
void ShowBonus(void*, int divided, int raw) {
	g_show_bonus_divided = divided;
	g_show_bonus_raw = raw;
}
int* PerShotCaptureCount(int) { return &g_per_shot_count; }
int* OverallCaptureCount(int) { return &g_overall_count; }
void SpellPlaySound(void*, int) { ++g_spell_sound_calls; }
Word SpawnHudEffect(Word, int, int) { return g_spawned_effect; }

void TestSpellCardOnEnd() {
	Word side_flags = 0;
	int total_score = 100;
	int game_mode = 0;
	Word hud_effect = 7;

	SpellEndEnv env = {};
	env.side_flags = &side_flags;
	env.release_effect = &ReleaseEffect;
	env.release_script = &SpellReleaseScript;
	env.total_score = &total_score;
	env.show_bonus = &ShowBonus;
	env.game_mode = &game_mode;
	env.per_shot_capture_count = &PerShotCaptureCount;
	env.overall_capture_count = &OverallCaptureCount;
	env.play_sound = &SpellPlaySound;
	env.hud_effect_slot = &hud_effect;
	env.spawn_hud_effect = &SpawnHudEffect;

	// Inactive card: nothing happens.
	SpellCard card = {};
	SpellCard_OnEnd(&card, &env);
	assert(side_flags == 0 && g_release_effect_calls == 0);

	// Captured card: bonus awarded, counters bumped, sound played.
	card.flags = 3;
	card.script = 55;
	card.bonus = 1230;
	card.spell_index = 4;
	SpellCard_OnEnd(&card, &env);
	assert((side_flags & 1u) != 0);
	assert(g_release_effect_calls == 3);
	assert((card.flags & 1u) == 0);
	assert(g_spell_release_script_calls == 1);
	assert(g_spell_released_scripts[0] == 55);
	assert(card.script == 0);
	assert(total_score == 100 + 123);
	assert(g_show_bonus_divided == 123 && g_show_bonus_raw == 1230);
	assert(g_per_shot_count == 1 && g_overall_count == 1);
	assert(g_spell_sound_calls == 1);

	// Score cap at 999999999.
	SpellCard card2 = {};
	card2.flags = 3;
	card2.bonus = 500;
	total_score = 999999990;
	SpellCard_OnEnd(&card2, &env);
	assert(total_score == 999999999);

	// Missed card: HUD effect recycled instead of the bonus.
	SpellCard card3 = {};
	card3.flags = 1;
	card3.script = 9;
	int releases_before = g_spell_release_script_calls;
	SpellCard_OnEnd(&card3, &env);
	// Releases: the card script and the previous HUD effect.
	assert(g_spell_release_script_calls == releases_before + 2);
	assert(hud_effect == 4242);

	// Practice mode (game_mode == 1) skips the counters. The score-cap
	// card above already bumped both to 2 (game_mode was still 0 there).
	SpellCard card4 = {};
	card4.flags = 3;
	card4.bonus = 10;
	game_mode = 1;
	SpellCard_OnEnd(&card4, &env);
	assert(g_per_shot_count == 2 && g_overall_count == 2);
}

} // namespace

int main() {
	TestJoystickProperty();
	TestEnemyDestroy();
	TestEclNameTable();
	TestEclLoadFile();
	TestSpellTimer();
	TestBulletRingReset();
	TestClipQuadUpload();
	TestScoreCreateAndReplayClamp();
	TestScoreTaskInit();
	TestNameEntryDrawCharGrid();
	TestResultScreenLazyCreate();
	TestGdiSurfaceCreate();
	TestEnemyBounceStep();
	TestApplyBlendColorWrap();
	TestInitTextureStages();
	TestEffectAccelStep();
	TestPauseMenuOpen();
	TestResultMenuOpen();
	TestNameEntryInit();
	TestStageBackgroundSyncScroll();
	TestSpellCardOnEnd();

	std::printf("BATCH10_TESTS_PASS\n");
	return 0;
}
