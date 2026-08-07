// Game-thread arena pointer (pool_constructors).
void* g_pGameThread = 0;
unsigned int DAT_00477834 = 0;  // player position (the 0x0041AFD0 sweep)


// Render/effect chain globals (pool_constructors + render leaves).
extern "C" {
unsigned long dword_491C10 = 0;   // animation manager
unsigned long dword_491C30 = 0;   // D3D device
unsigned long dword_491D78 = 0;   // view flags
unsigned long dword_492378 = 0;   // alpha-blend latch
unsigned long dword_477834 = 0;   // player position
}

// Tests for the batch 9 readable reconstructions.

#include "th10/app/fps_counter.hpp"
#include "th10/game/ascii_overlay_callbacks.hpp"
#include "th10/game/bullet_manager.hpp"

// Published game-UI manager (retail 0x00477810); zero = absent.
extern "C" {
unsigned long dword_477810 = 0;
}

// Angle recovery constants (math/angle.cpp).
float DAT_00470b10 = -3.1415927f;  // -pi
float DAT_00470b14 = 6.2831855f;   // 2*pi
float DAT_00470b18 = 3.1415927f;   // pi

#include "th10/game/ending_screen.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/enemy_motion_steps.hpp"
#include "th10/game/item_field_contact.hpp"
#include "th10/game/pause_menu_reset.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/title_assets.hpp"
#include "th10/platform/midi_worker.hpp"
#include "th10/platform/sound_effect_buffers.hpp"
#include "th10/render/anm_surface_restore.hpp"
#include "th10/render/anm_vm_draw_dispatch.hpp"
#include "th10/render/default_viewport.hpp"
#include "th10/script/stage_ecl_load.hpp"
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
float _DAT_00470b0c = 0.5f;   // the 0x0042B9A0 sweep (frame-delta half-rate)
float _DAT_00470afc = 1.0f;   // the 0x0042B9A0 sweep (ramp step)
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

// --- FrameRateCounter_Update (0x004134B0) ---------------------------------

double g_seconds = 0.0;
double ReadSeconds() { return g_seconds; }

void TestFrameRateCounter() {
	FrameRateCounter counter = {};
	double stamps[4] = {-1.0, -1.0, -1.0, -1.0};
	double skip_accumulator = 42.0;
	Word input_flags = 0x80;
	FrameRateEnv env = {};
	env.read_seconds = &ReadSeconds;
	env.min_interval = 0.5;
	env.negative_wrap = 4294967296.0;
	env.stall_threshold = 1000.0;
	env.fps_cap = 60.0;
	env.second_unit = 1.0;
	env.input_flags = &input_flags;
	for (int i = 0; i < 4; ++i) env.sync_stamps[i] = &stamps[i];
	env.skip_accumulator = &skip_accumulator;

	// Short window: nothing is measured.
	g_seconds = 0.25;
	counter.frame_count = 15;
	assert(FrameRateCounter_Update(&counter, &env) == 1);
	assert(counter.frame_count == 15);

	// Full window: the short call did not advance the stamp, so the window
	// is 1.25s; 60 frames => 48 fps, counted as active.
	g_seconds = 1.25;
	counter.frame_count = 60;
	assert(FrameRateCounter_Update(&counter, &env) == 1);
	assert(counter.fps > 47.0f && counter.fps < 49.0f);
	assert(counter.frame_count == 0);
	assert(counter.total_seconds == 1.0);
	assert(counter.active_seconds > 47.0 && counter.active_seconds < 49.0);
	assert((input_flags & 0x80) == 0);
	assert(counter.stall_count == 0);

	// Two stalls in a row rewrite the sync stamps.
	g_seconds = 2.25;
	counter.frame_count = 2000000;
	assert(FrameRateCounter_Update(&counter, &env) == 1);
	assert(counter.stall_count == 1);
	assert(stamps[0] == -1.0);
	g_seconds = 3.25;
	counter.frame_count = 2000000;
	assert(FrameRateCounter_Update(&counter, &env) == 1);
	assert(counter.stall_count == 2);
	assert(stamps[0] == 3.25 && stamps[3] == 3.25);

	// Two more stalls clear the skip accumulator and reset the counter.
	g_seconds = 4.25;
	counter.frame_count = 2000000;
	assert(FrameRateCounter_Update(&counter, &env) == 1);
	assert(counter.stall_count == 3);
	g_seconds = 5.25;
	counter.frame_count = 2000000;
	assert(FrameRateCounter_Update(&counter, &env) == 1);
	assert(counter.stall_count == 0);
	assert(skip_accumulator == 0.0);
	assert(stamps[2] == 5.25);
}

// --- EndingState_Dispatch (0x0042D300) -------------------------------------

EndingScreen* g_ending_screen = 0;
int g_ending_load_result = 0;
int g_ending_advance_calls = 0;
Word g_ending_color = 0xAABBCCDD;
int g_ending_set_state_log[8];
int g_ending_set_state_count = 0;
int g_ending_sound = -1;
int g_ending_stop_music_calls = 0;
int g_ending_fade_calls = 0;
int g_ending_pop_count = -1;

int EndingLoadBackground(void*, int) { return g_ending_load_result; }
void EndingAdvance(EndingScreen*) { ++g_ending_advance_calls; }
const Word* EndingSampleColor(void*, int, int) { return &g_ending_color; }
void EndingSetState(int state) {
	g_ending_set_state_log[g_ending_set_state_count++] = state;
	if (g_ending_screen != 0) g_ending_screen->state = state;
}
void EndingPlaySound(int id) { g_ending_sound = id; }
void EndingStopMusic(void*, int) { ++g_ending_stop_music_calls; }
void EndingBeginFade() { ++g_ending_fade_calls; }
void EndingPopState(int count) { g_ending_pop_count = count; }

void TestEndingDispatch() {
	EndingScreen screen = {};
	g_ending_screen = &screen;
	EndingEnv env = {};
	env.load_background = &EndingLoadBackground;
	env.advance_script = &EndingAdvance;
	env.sample_color = &EndingSampleColor;
	env.set_state = &EndingSetState;
	env.play_sound = &EndingPlaySound;
	env.stop_music = &EndingStopMusic;
	env.begin_fade_out = &EndingBeginFade;
	env.pop_state = &EndingPopState;

	// State 0 loads the background, samples the color, clamps the delay, and
	// falls through to the frame check (frame 20 > 10 => state 2).
	screen.state = 0;
	screen.pending_delay = -3;
	screen.frame = 20;
	assert(EndingState_Dispatch(&screen, &env) == 1);
	assert(g_ending_advance_calls == 2);
	assert(screen.color == 0xAABBCCDD);
	assert(screen.state_timer == -4);
	assert(g_ending_set_state_count == 2);
	assert(g_ending_set_state_log[0] == 1 && g_ending_set_state_log[1] == 2);

	// State 2 waits for accept input.
	env.input_flags = 0;
	assert(EndingState_Dispatch(&screen, &env) == 1);
	assert(g_ending_sound == -1);
	env.input_flags = 0x0001;
	assert(EndingState_Dispatch(&screen, &env) == 1);
	assert(g_ending_sound == 0x5A);
	assert(g_ending_stop_music_calls == 1);
	assert(g_ending_fade_calls == 1);
	assert(screen.state == 4);

	// State 4 pops after 0x1D frames.
	screen.frame = 0x1D;
	assert(EndingState_Dispatch(&screen, &env) == 1);
	assert(g_ending_pop_count == -1);
	screen.frame = 0x1E;
	assert(EndingState_Dispatch(&screen, &env) == 1);
	assert(g_ending_pop_count == 2);
}

// --- Renderer_ApplyDefaultViewport / Ascii_OnResetDevice --------------------

int g_flush_calls = 0;
int g_reset_text_calls = 0;
const int* g_seen_viewport = 0;
void* g_seen_device = 0;

void FlushDrawQueue() { ++g_flush_calls; }
void ResetTextState() { ++g_reset_text_calls; }
void SetViewport(void* device, const int* viewport) {
	g_seen_device = device;
	g_seen_viewport = viewport;
}

void TestViewportCallbacks() {
	int viewport[4] = {9, 9, 9, 9};
	int device_cookie = 0;
	ViewportEnv env = {};
	env.flush_draw_queue = &FlushDrawQueue;
	env.viewport_slot = viewport;
	env.device = &device_cookie;
	env.set_viewport = &SetViewport;
	env.reset_text_state = &ResetTextState;
	assert(Renderer_ApplyDefaultViewport(&env) == 1);
	assert(g_flush_calls == 1);
	assert(viewport[0] == 0 && viewport[1] == 0);
	assert(viewport[2] == 0x280 && viewport[3] == 0x1E0);
	assert(g_seen_viewport == viewport);
	assert(g_seen_device == &device_cookie);
	assert(g_reset_text_calls == 1);

	assert(Ascii_OnResetDevice(&ResetTextState) == 1);
	assert(g_reset_text_calls == 2);
}

// --- BulletManager_RelinkActive (0x004065C0) --------------------------------

int g_update_calls = 0;
int g_update_fail_index = -1;
LinkBullet* g_update_base = 0;

int UpdateBullet(LinkBullet* bullet) {
	++g_update_calls;
	return (int)(bullet - g_update_base) == g_update_fail_index ? 1 : 0;
}

void TestRelinkActive() {
	float scale = 1.0f;
	LinkBullet bullets[4] = {};
	for (int i = 0; i < 4; ++i) {
		bullets[i].state = 1;
		bullets[i].clock.control = &scale;
		bullets[i].age = 5.0f;
	}
	bullets[1].state = 0;             // free slot
	bullets[0].layer = 2.0f;
	bullets[2].layer = 2.0f;
	bullets[3].layer = 0.0f;
	g_update_base = bullets;
	g_update_fail_index = 3;          // bullet 3 retires during update

	BulletLinkManager manager = {};
	manager.active_count = 99;
	BulletLinkEnv env = {};
	env.player_flags = 0;
	env.update_bullet = &UpdateBullet;
	env.clock_env = MakeClockEnv();

	assert(BulletManager_RelinkActive(&manager, bullets, 4, &env) == 1);
	assert(g_update_calls == 3);      // bullet 1 skipped entirely
	assert(manager.active_count == 2);
	assert(manager.heads[2] == &bullets[0]);
	assert(manager.tails[2] == &bullets[2]);
	assert(bullets[0].next == &bullets[2]);
	assert(manager.heads[0] == 0);    // bullet 3 dropped
	assert(bullets[0].age == 0.0f);
	assert(bullets[0].clock.frame == 1 && bullets[0].clock.previous == 0);

	// Player capture state freezes updates but still relinks.
	Word player_flags = 2 | 0x400;
	env.player_flags = &player_flags;
	g_update_calls = 0;
	assert(BulletManager_RelinkActive(&manager, bullets, 4, &env) == 1);
	assert(g_update_calls == 0);
	assert(manager.active_count == 3);
}

// --- BulletManager_OnDraw (0x00402720) --------------------------------------

int g_normalize_calls = 0;
int g_prepare_calls = 0;
int g_layout_calls = 0;
void* g_batch_log[16];
int g_batch_count = 0;
float g_batch_scales[16];
float g_scale_slot = 2.5f;

void NormalizeVec(float* out3, const float* in3) {
	++g_normalize_calls;
	float len = sqrtf(in3[0] * in3[0] + in3[1] * in3[1] + in3[2] * in3[2]);
	for (int i = 0; i < 3; ++i) out3[i] = in3[i] / len;
}
void PrepareCommonState() { ++g_prepare_calls; }
void RefreshLayout(BulletDrawHost*) { ++g_layout_calls; }
void DrawBatch(void* batch) {
	g_batch_scales[g_batch_count] = g_scale_slot;
	g_batch_log[g_batch_count++] = batch;
}

void TestBulletOnDraw() {
	BulletDrawHost host = {};
	Word snapshot[0x46] = {};
	BulletDrawEnv env = {};
	env.normalize = &NormalizeVec;
	env.prepare_common_state = &PrepareCommonState;
	env.refresh_layout = &RefreshLayout;
	env.draw_batch = &DrawBatch;
	env.global_scale = &g_scale_slot;
	env.camera_snapshot = snapshot;

	// Hidden host draws nothing.
	host.flags = 8;
	assert(BulletManager_OnDraw(&host, &env) == 1);
	assert(g_batch_count == 0);

	// Long freeze also skips.
	host.flags = 4;
	host.freeze_timer = 0x3C;
	assert(BulletManager_OnDraw(&host, &env) == 1);
	assert(g_batch_count == 0);

	// Active host draws 8 layers + 3 overlays at unit scale.
	host.flags = 0;
	host.aim_source[0] = 3.0f;
	host.aim_source[1] = 4.0f;
	host.overlay_pending = 1;
	for (int i = 0; i < 5; ++i) host.recoil[i] = 9.0f;
	int layer_cookies[8];
	int overlay_cookies[3];
	for (int i = 0; i < 8; ++i) host.layer_batches[i] = &layer_cookies[i];
	for (int i = 0; i < 3; ++i) host.overlay_batches[i] = &overlay_cookies[i];
	for (int i = 0; i < 0x46; ++i) host.camera_block[i] = 0x1000u + (Word)i;
	assert(BulletManager_OnDraw(&host, &env) == 1);
	assert(g_normalize_calls == 1 && g_prepare_calls == 1 && g_layout_calls == 1);
	assert(host.recoil[0] == 0.0f && host.recoil[4] == 0.0f);
	assert(host.ambient_color == 0x808080);
	assert(g_batch_count == 11);
	assert(g_batch_log[0] == &layer_cookies[0]);
	assert(g_batch_log[8] == &overlay_cookies[0]);
	assert(g_batch_scales[0] == 2.5f);   // layers draw at the ambient scale
	assert(g_batch_scales[8] == 1.0f);   // overlays draw at unit scale
	assert(g_scale_slot == 2.5f);        // scale restored
	assert(host.overlay_pending == 0);
	assert(snapshot[0] == 0x1000u && snapshot[0x45] == 0x1045u);
	assert(host.draw_counter == 1);
	assert(fabsf(host.aim_normalized[0] - 0.6f) < 1e-5f);
	assert(fabsf(host.aim_normalized[1] - 0.8f) < 1e-5f);
}

// --- TitleScreen_LoadCoreAssets (0x0041F990) --------------------------------

int g_open_anm_calls = 0;
const char* g_open_anm_names[4];
int g_open_anm_slots[4];
void* g_open_anm_results[4];
void* g_title_task_result = 0;
int g_report_calls = 0;
const char* g_reported_text = 0;
Byte g_score_bytes[4];
Byte* g_score_result = 0;
int g_sound_init_calls = 0;
int g_has_file_result = 0;
int g_stream_calls = 0;
int g_midi_calls = 0;
int g_score_table_calls = 0;
int g_enter_title_calls = 0;

void* OpenAnm(int slot, void*, const char* name) {
	g_open_anm_slots[g_open_anm_calls] = slot;
	g_open_anm_names[g_open_anm_calls] = name;
	return g_open_anm_results[g_open_anm_calls++];
}
void* CreateTitleTask() { return g_title_task_result; }
void ReportError(void*, const char* text) {
	++g_report_calls;
	g_reported_text = text;
}
Byte* LoadScoreFile(Word*, int) { return g_score_result; }
int InitSoundBuffers() { ++g_sound_init_calls; return 0; }
int ArchiveHasFile(const char*) { return g_has_file_result; }
int StartMusicStream(const char*) { ++g_stream_calls; return 0; }
void SelectMidiPlayback() { ++g_midi_calls; }
void LoadScoreTable() { ++g_score_table_calls; }
void EnterTitleMenu() { ++g_enter_title_calls; }

void TestTitleLoadCoreAssets() {
	Word update_flags = 0;
	Word draw_flags = 0;
	void* interface_slot = 0;
	Byte* score_slot = 0;
	int failure_state = 0;
	int sig_cookie = 0;
	int text_cookie = 0;
	int task_cookie = 0;

	TitleScreen title = {};
	title.update_flags = &update_flags;
	title.draw_flags = &draw_flags;
	TitleEnv env = {};
	env.open_anm = &OpenAnm;
	env.create_title_task = &CreateTitleTask;
	env.report_error = &ReportError;
	env.task_error_text = "task";
	env.score_error_text = "score";
	env.interface_anm_slot = &interface_slot;
	env.load_score_file = &LoadScoreFile;
	env.score_data_slot = &score_slot;
	env.init_sound_buffers = &InitSoundBuffers;
	env.archive_has_file = &ArchiveHasFile;
	env.start_music_stream = &StartMusicStream;
	env.select_midi_playback = &SelectMidiPlayback;
	env.load_score_table = &LoadScoreTable;
	env.enter_title_menu = &EnterTitleMenu;
	env.failure_state = &failure_state;

	// Missing sig.anm fails immediately.
	g_open_anm_results[0] = 0;
	assert(TitleScreen_LoadCoreAssets(&title, &env) == 0);
	assert(failure_state == 3);
	assert((draw_flags & 2) != 0);
	assert(g_open_anm_slots[0] == 1);
	assert(std::strcmp(g_open_anm_names[0], "sig.anm") == 0);

	// Full success path with streamed BGM.
	g_open_anm_calls = 0;
	failure_state = 0;
	draw_flags = 0;
	g_open_anm_results[0] = &sig_cookie;
	g_open_anm_results[1] = &text_cookie;
	g_title_task_result = &task_cookie;
	g_score_result = g_score_bytes;
	g_has_file_result = 1;
	assert(TitleScreen_LoadCoreAssets(&title, &env) == 0);
	assert(failure_state == 0);
	assert(title.signature_ready == 1 && title.interface_ready == 1);
	assert((update_flags & 2) != 0 && (draw_flags & 2) != 0);
	assert(interface_slot == &text_cookie);
	assert(score_slot == g_score_bytes);
	assert(g_report_calls == 0);   // missing sig.anm is silent, no report
	assert(g_sound_init_calls == 1);
	assert(g_stream_calls == 1 && g_midi_calls == 0);
	assert(g_score_table_calls == 1 && g_enter_title_calls == 1);
	assert(std::strcmp(g_open_anm_names[1], "text.anm") == 0);

	// Midi config selects midi playback instead of the stream.
	g_open_anm_calls = 0;
	env.config_flags = 0x10;
	assert(TitleScreen_LoadCoreAssets(&title, &env) == 0);
	assert(g_midi_calls == 1 && g_stream_calls == 1);
}

// --- MidiOutput_ApplyChannelVolumes (0x0043B7A0) -----------------------------

int g_midi_bases[16];
Word g_midi_messages[16];
int g_midi_message_count = 0;

int ReadBaseVolume(int channel) { return g_midi_bases[channel]; }
void SendShortMessage(void*, Word message) {
	g_midi_messages[g_midi_message_count++] = message;
}

void TestMidiVolumes() {
	MidiOutput midi = {};
	int handle_cookie = 0;
	midi.handle = &handle_cookie;
	MidiEnv env = {};
	env.read_base_volume = &ReadBaseVolume;
	env.send_short_message = &SendShortMessage;
	for (int i = 0; i < 16; ++i) g_midi_bases[i] = 64;
	g_midi_bases[0] = 120;  // clamps high with +20
	g_midi_bases[1] = -10;  // clamps low with +20 - 40

	// Stream mode skips everything.
	midi.stream_mode = 1;
	MidiOutput_ApplyChannelVolumes(&midi, 20, &env);
	assert(g_midi_message_count == 0);

	midi.stream_mode = 0;
	MidiOutput_ApplyChannelVolumes(&midi, 20, &env);
	assert(g_midi_message_count == 16);
	// Channel 0: clamped to 0x7F, controller 7, status 0xB0.
	assert(g_midi_messages[0] == ((0x7Fu << 16) | 0x0700u | 0xB0u));
	// Channel 1: -10 + 20 = 10.
	assert(g_midi_messages[1] == ((10u << 16) | 0x0700u | 0xB1u));
	// Channel 2: 64 + 20 = 84.
	assert(g_midi_messages[2] == ((84u << 16) | 0x0700u | 0xB2u));
}

// --- SoundManager_InitCommonBuffers (0x0043DB60) -----------------------------

int g_bank_load_calls = 0;
int g_bank_load_sets = 1;
void* g_dup_sources[8];
int g_dup_count = 0;
int g_volume_log[8];
int g_pan_log[8];

int LoadWaveBank(SoundManager* manager) {
	++g_bank_load_calls;
	manager->loaded = g_bank_load_sets;
	return 0;
}
void DuplicateBuffer(void*, void* source, void** out) {
	g_dup_sources[g_dup_count] = source;
	*out = source;
	++g_dup_count;
}
void SetBufferVolume(void*, int volume) { g_volume_log[g_dup_count - 1] = volume; }
void SetBufferPan(void*, int pan) { g_pan_log[g_dup_count - 1] = pan; }
long long ReadClock() { return 1234; }

void TestSoundInitCommonBuffers() {
	int device_cookie = 0;
	int wave_a = 0;
	int wave_b = 0;
	void* waves[4] = {&wave_a, &wave_b, 0, 0};
	void* duplicated[8] = {};
	SoundEffectSpec specs[2] = {{0, -50}, {1, 70}};

	SoundManager manager = {};
	manager.device = &device_cookie;
	manager.wave_buffers = waves;
	manager.duplicated = duplicated;
	SoundBufferEnv env = {};
	env.load_wave_bank = &LoadWaveBank;
	env.duplicate_buffer = &DuplicateBuffer;
	env.set_volume = &SetBufferVolume;
	env.set_pan = &SetBufferPan;
	env.specs = specs;
	env.spec_count = 2;
	env.bgm_enabled_flag = 1;
	env.bgm_stream_flag = 1;
	env.read_clock = &ReadClock;

	// Failed bank load.
	g_bank_load_sets = 0;
	assert(SoundManager_InitCommonBuffers(&manager, &env) == -1);
	assert(manager.queue_ids[0] == -1 && manager.queue_ids[11] == -1);
	assert(g_bank_load_calls == 1);

	// Success with streamed BGM start offset.
	g_bank_load_sets = 1;
	assert(SoundManager_InitCommonBuffers(&manager, &env) == 0);
	assert(g_dup_count == 2);
	assert(g_dup_sources[0] == &wave_a && g_dup_sources[1] == &wave_b);
	assert(g_volume_log[0] == 0 && g_pan_log[0] == -50 && g_pan_log[1] == 70);
	assert(manager.bgm_enabled == 1 && manager.bgm_use_stream == 1);
	assert(manager.bgm_start_offset == -5000 - 1234);

	// Non-stream BGM uses the fixed offset.
	env.bgm_stream_flag = 0;
	assert(SoundManager_InitCommonBuffers(&manager, &env) == 0);
	assert(manager.bgm_start_offset == -10000);
}

// --- AnmVm_DrawDispatch (0x004451C0) -----------------------------------------

int g_draw_which = -1;
int g_corner_layer = -1;

int DrawStandard(void*) { g_draw_which = 0; return 10; }
int DrawUnrotated(void*) { g_draw_which = 2; return 12; }
int DrawCornerQuad(void*, int layer) {
	g_draw_which = 1;
	g_corner_layer = layer;
	return 11;
}
int DrawMode4(void*) { g_draw_which = 4; return 14; }
int DrawMode5(void*) { g_draw_which = 5; return 15; }
int DrawMode6(void*) { g_draw_which = 6; return 16; }
int DrawMode7(void*, AnmDrawVm*) { g_draw_which = 7; return 17; }
int DrawMode8(void*) { g_draw_which = 8; return 18; }
int DrawMode9(void*) { g_draw_which = 9; return 19; }

void TestAnmDrawDispatch() {
	AnmQuad quad = {};
	AnmDrawEnv env = {};
	env.draw_standard = &DrawStandard;
	env.draw_unrotated = &DrawUnrotated;
	env.draw_corner_quad = &DrawCornerQuad;
	env.draw_mode4 = &DrawMode4;
	env.draw_mode5 = &DrawMode5;
	env.draw_mode6 = &DrawMode6;
	env.draw_mode7 = &DrawMode7;
	env.draw_mode8 = &DrawMode8;
	env.draw_mode9 = &DrawMode9;
	env.quad = &quad;
	env.anchor_low = -0.5f;
	env.anchor_high = 0.5f;

	AnmDrawVm vm = {};
	int context = 0;

	// Invisible or disabled VMs bail out.
	vm.flags = 3;
	vm.visible = 0;
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == -1);
	vm.visible = 1;
	vm.flags = 1;
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == -1);

	// Mode 0 routes to the standard handler.
	vm.flags = 3;
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == 10);
	assert(g_draw_which == 0);

	// Mode 1 with zero rotation routes to the unrotated handler.
	vm.flags = 3 | (1u << 0x16);
	vm.rotation = 0.0f;
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == 12);
	assert(g_draw_which == 2);

	// Mode 1 with rotation pi/2 fills the corner quad: a centered 4x2 quad
	// rotates so x extents become y extents.
	vm.rotation = 1.5707964f;
	vm.size_x = 4.0f;
	vm.size_y = 2.0f;
	vm.scale_x = 1.0f;
	vm.scale_y = 1.0f;
	vm.origin_x = 10.0f;
	vm.origin_y = 20.0f;
	vm.origin_z = 5.0f;
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == 11);
	assert(g_draw_which == 1 && g_corner_layer == 0);
	assert(fabsf(quad.corners[0][0] - (10.0f + 1.0f)) < 1e-4f);  // -(-1) rotated
	assert(fabsf(quad.corners[0][1] - (20.0f - 2.0f)) < 1e-4f);
	assert(fabsf(quad.corners[3][0] - (10.0f - 1.0f)) < 1e-4f);
	assert(fabsf(quad.corners[3][1] - (20.0f + 2.0f)) < 1e-4f);
	assert(quad.corners[0][2] == 5.0f && quad.corners[3][2] == 5.0f);

	// Left-anchored horizontal mode keeps x extents in 0..w before rotation.
	vm.flags = 3 | (3u << 0x16) | (1u << 0x12);
	vm.rotation = 0.0001f;  // effectively unrotated but nonzero
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == 11);
	assert(fabsf(quad.corners[0][0] - 10.0f) < 1e-2f);
	assert(fabsf(quad.corners[1][0] - 14.0f) < 1e-2f);

	// Modes 4..9 route to their handlers.
	for (Word mode = 4; mode <= 9; ++mode) {
		vm.flags = 3 | (mode << 0x16);
		assert(AnmVm_DrawDispatch(&vm, &context, &env) == (int)(10 + mode));
		assert(g_draw_which == (int)mode);
	}

	// Unknown modes return 0.
	vm.flags = 3 | (11u << 0x16);
	assert(AnmVm_DrawDispatch(&vm, &context, &env) == 0);
}

// --- StageScript_Load (0x00403850) -------------------------------------------

Byte g_script_file[0x200];
char g_name_sink[64];
Byte g_alloc_arena[0x4000];
unsigned int g_alloc_used = 0;
int g_open_entry_mode = -1;
const char* g_open_entry_name = 0;
int g_stage_report_calls = 0;

Byte* ReadScriptFile(Word* size_slot, int) {
	*size_slot = sizeof(g_script_file);
	return g_script_file;
}
void* OpenEntry(int mode, void*, const char* name) {
	g_open_entry_mode = mode;
	g_open_entry_name = name;
	return (void*)name;
}
void StageReportError(void*, const char*) { ++g_stage_report_calls; }
void* AllocateArena(unsigned int size) {
	void* result = g_alloc_arena + g_alloc_used;
	g_alloc_used = (g_alloc_used + size + 15u) & ~15u;
	return result;
}

void TestStageScriptLoad() {
	// Build a tiny ECL header: 2 subs, 3 enemies, anm/std paths, offsets.
	std::memset(g_script_file, 0, sizeof(g_script_file));
	short sub_count = 2;
	short enemy_count = 3;
	Word anm_offset = 0x100;
	Word std_offset = 0x110;
	std::memcpy(g_script_file + 0, &sub_count, 2);
	std::memcpy(g_script_file + 2, &enemy_count, 2);
	std::memcpy(g_script_file + 4, &anm_offset, 4);
	std::memcpy(g_script_file + 8, &std_offset, 4);
	std::strcpy((char*)g_script_file + 0x10, "stage1.anm");
	Word sub0 = 0x120;
	Word sub1 = 0x140;
	std::memcpy(g_script_file + 0x90, &sub0, 4);
	std::memcpy(g_script_file + 0x94, &sub1, 4);

	StageScript script = {};
	script.mode_flags = 1;
	StageScriptEnv env = {};
	env.name_sink = g_name_sink;
	env.read_script_file = &ReadScriptFile;
	env.open_entry = &OpenEntry;
	env.report_error = &StageReportError;
	env.error_text = "missing";
	env.allocate = &AllocateArena;

	assert(StageScript_Load(&script, "ecldata1.ecl", &env) == 0);
	assert(std::strcmp(g_name_sink, "ecldata1.ecl") == 0);
	assert(script.cached_file == g_script_file);
	assert(script.cached_size == sizeof(g_script_file));
	assert(script.buffer != 0 && script.buffer != (char*)g_script_file);
	assert(std::memcmp(script.buffer, g_script_file, sizeof(g_script_file)) == 0);
	assert(g_open_entry_mode == 5);  // (mode_flags & 1) + 4
	assert(std::strcmp(g_open_entry_name, "stage1.anm") == 0);
	assert(script.anm_path == script.buffer + 0x100);
	assert(script.std_path == script.buffer + 0x110);
	assert(script.sub_table[0] == script.buffer + 0x120);
	assert(script.sub_table[1] == script.buffer + 0x140);
	assert(script.enemy_pool != 0);
	assert(g_stage_report_calls == 0);
}

// --- Enemy step functions ----------------------------------------------------

float g_set_velocity_out[3];
float g_set_velocity_angle;
float g_set_velocity_speed;
int g_set_velocity_calls = 0;
int g_ambient_stop_calls = 0;

void SetVelocity(float* velocity, float angle, float speed) {
	g_set_velocity_angle = angle;
	g_set_velocity_speed = speed;
	velocity[0] = cosf(angle) * speed;
	velocity[1] = sinf(angle) * speed;
	g_set_velocity_out[0] = velocity[0];
	g_set_velocity_out[1] = velocity[1];
	++g_set_velocity_calls;
}
void StopAmbient(void*, int) { ++g_ambient_stop_calls; }
float WrapTurn(float reference, float amount) { return reference + amount; }
float LimitTurn(float turn, float angle) { return turn - angle; }

void TestEnemyAccelStep() {
	float scale = 1.0f;
	Word status = 0xFFFFFFFFu;
	AccelEnemy enemy = {};
	enemy.status_flags = &status;
	enemy.clock.control = &scale;
	enemy.duration = 10;
	enemy.speed = 1.0f;
	enemy.speed_accel = 0.5f;
	enemy.accel[0] = 1.0f;
	enemy.accel[1] = 2.0f;
	ClockEnv clock_env = MakeClockEnv();

	Enemy_AccelStep(&enemy, 1.0f, 0.01f, &clock_env);
	assert(enemy.speed == 1.5f);
	assert(enemy.velocity[0] == 1.0f && enemy.velocity[1] == 2.0f);
	assert(fabsf(enemy.angle - atan2f(2.0f, 1.0f)) < 1e-5f);
	assert(enemy.clock.frame == 1 && enemy.clock.previous == 0);
	assert(status == 0xFFFFFFFFu);

	// Past the duration the run bit clears.
	enemy.clock.frame = 10;
	Enemy_AccelStep(&enemy, 1.0f, 0.01f, &clock_env);
	assert((status & 0x10u) == 0);
}

void TestEnemyHomingStep() {
	float scale = 1.0f;
	float target[2] = {10.0f, 0.0f};
	Word status = 0xFFFFFFFFu;
	HomingEnemy enemy = {};
	enemy.status_flags = &status;
	enemy.clock.control = &scale;
	enemy.duration = 10;
	enemy.speed = 2.0f;
	enemy.turn_rate = 0.5f;
	enemy.turn_limit = 0.25f;
	HomingEnv env = {};
	env.target_position = target;
	env.wrap_turn = &WrapTurn;
	env.limit_turn = &LimitTurn;
	env.set_velocity = &SetVelocity;
	env.frame_scale = 1.0f;
	env.clock_env = MakeClockEnv();

	// Target dead ahead at angle 0: aim=0, wrapped=0.25, limited=0.25,
	// angle = 0 + 0.25*0.5 = 0.125.
	g_set_velocity_calls = 0;
	Enemy_HomingStep(&enemy, &env);
	assert(g_set_velocity_calls == 1);
	assert(fabsf(enemy.angle - 0.125f) < 1e-5f);
	assert(fabsf(g_set_velocity_speed - 2.0f) < 1e-5f);
	assert(enemy.clock.frame == 1);

	// Overlapping target aims straight down (+pi/2).
	enemy.position[0] = 10.0f;
	enemy.position[1] = 0.0f;
	enemy.angle = 0.0f;
	Enemy_HomingStep(&enemy, &env);
	float expected = (0.25f + 1.5707964f - 0.0f) * 0.5f;
	assert(fabsf(enemy.angle - expected) < 1e-4f);

	// Expiry clears the homing bit.
	enemy.clock.frame = 10;
	g_set_velocity_calls = 0;
	Enemy_HomingStep(&enemy, &env);
	assert((status & 0x04000000u) == 0);
	assert(g_set_velocity_calls == 0);
}

void TestEnemyEaseSteps() {
	float scale = 1.0f;
	Word status = 0xFFFFFFFFu;
	EaseEnemy enemy = {};
	enemy.status_flags = &status;
	enemy.clock.clock.control = &scale;
	enemy.duration = 10;
	enemy.speed = 8.0f;
	enemy.final_speed = 3.0f;
	enemy.final_angle = 0.5f;
	enemy.angle = 1.0f;
	enemy.ambient_sound = 2;
	enemy.repeat_limit = 1;
	EaseEnv env = {};
	env.stop_ambient_sound = &StopAmbient;
	env.set_velocity = &SetVelocity;
	env.frame_scale = &scale;
	env.clock_env = MakeClockEnv();

	// Mid-ease: timer 5 of 10 halves the speed.
	enemy.clock.clock.timer = 5.0f;
	enemy.clock.clock.frame = 5;
	g_ambient_stop_calls = 0;
	Enemy_EaseStopStep(&enemy, &env);
	assert(fabsf(g_set_velocity_speed - 4.0f) < 1e-5f);
	assert(g_ambient_stop_calls == 0);
	assert(enemy.clock.clock.frame == 6);

	// Completion: ambient stops, repeat hits the limit clearing bit 0x100,
	// the angle is assigned, and the clock re-registers.
	enemy.clock.clock.frame = 10;
	Enemy_EaseStopStep(&enemy, &env);
	assert(g_ambient_stop_calls == 1);
	assert((status & 0x100u) == 0);
	assert(enemy.angle == 0.5f);
	assert(enemy.speed == 3.0f);
	assert((enemy.clock.flags & 1u) != 0);
	assert(enemy.clock.clock.control == &scale);
	assert(enemy.clock.clock.frame == 1);   // advanced after the reset
	assert(enemy.clock.clock.previous == 0);

	// Turn variant adds the angle and clears bit 0x40.
	status = 0xFFFFFFFFu;
	enemy.repeat_count = 0;
	enemy.angle = 1.0f;
	enemy.clock.clock.frame = 10;
	enemy.clock.clock.timer = 10.0f;
	Enemy_EaseTurnStep(&enemy, &env);
	assert((status & 0x40u) == 0);
	assert(fabsf(enemy.angle - 1.5f) < 1e-5f);
}

// --- EnemySpawner_CreateFromTable (0x0040B110) -------------------------------

SpawnEffectVm g_effect_vm;
int g_assigned_sprite = -1;
int g_spawn_layout_calls = 0;
int g_on_spawn_calls = 0;
SpawnedEnemy g_spawned_enemy;
SpawnedEnemy* g_resolve_result = 0;

SpawnEffectVm* AcquireEffect() { return &g_effect_vm; }
void AssignSprite(SpawnEffectVm*, int sprite_id) { g_assigned_sprite = sprite_id; }
void SpawnRefreshLayout(void*) { ++g_spawn_layout_calls; }
SpawnedEnemy* ResolveEnemy(void*, int) { return g_resolve_result; }
void OnSpawnCallback() { ++g_on_spawn_calls; }

void TestEnemySpawner() {
	SpawnEntry table[2] = {
	    {7, 0, 1.0f, 2.0f},
	    {9, &OnSpawnCallback, 3.0f, 4.0f},
	};
	SpawnEnv env = {};
	env.acquire_effect = &AcquireEffect;
	env.assign_sprite = &AssignSprite;
	env.refresh_layout = &SpawnRefreshLayout;
	env.resolve_enemy = &ResolveEnemy;

	int result = -1;
	g_resolve_result = &g_spawned_enemy;
	EnemySpawner_CreateFromTable(table, 1, 55, &result, &env);
	assert(g_effect_vm.layer == 0xF);
	assert((g_effect_vm.flags & 0x40000000u) != 0);
	assert(g_assigned_sprite == 9);
	assert(g_spawn_layout_calls == 1);
	assert(g_on_spawn_calls == 1);
	assert(g_spawned_enemy.anchor_x == 3.0f && g_spawned_enemy.anchor_y == 4.0f);
	assert(result == 55);

	// Failed resolution zeroes the handle and skips the anchor write.
	g_resolve_result = 0;
	result = -1;
	EnemySpawner_CreateFromTable(table, 0, 55, &result, &env);
	assert(result == 0);
	assert(g_on_spawn_calls == 1);  // entry 0 has no callback
}

// --- PauseMenu_ResetTimers (0x00424D90) --------------------------------------

int g_release_script_arg = -1;
int g_played_track = -1;

void ReleaseScript(float*, void*, int script) { g_release_script_arg = script; }
void PlayMusic(int track) { g_played_track = track; }

void TestPauseMenuReset() {
	float scale = 1.0f;
	PauseMenu menu = {};
	menu.script_handle = 77;
	PauseResetEnv env = {};
	env.frame_scale = &scale;
	env.release_script = &ReleaseScript;
	env.play_music = &PlayMusic;
	env.music_track = 12;

	PauseMenu_ResetTimers(&menu, &env);
	assert(menu.active == 1);
	assert((menu.fade.flags & 1u) != 0);
	assert(menu.fade.clock.control == &scale);
	assert(menu.fade.clock.frame == -1);
	assert(menu.fade.clock.timer == -1.0f);
	assert(menu.fade.clock.previous == -2);
	assert(menu.cursor.clock.frame == 0 && menu.cursor.clock.previous == -1);
	assert(menu.slide.clock.frame == 0 && menu.slide.clock.previous == -1);
	assert(g_release_script_arg == 77);
	assert(menu.script_handle == 0);
	assert(g_played_track == 12);
}

// --- Item_TestFieldContact (0x004266B0) --------------------------------------

int g_collect_calls = 0;
void CollectAll(ItemField*) { ++g_collect_calls; }

void TestItemFieldContact() {
	ItemField field = {};
	field.min_x = 0.0f;
	field.min_y = 0.0f;
	field.max_x = 100.0f;
	field.max_y = 100.0f;
	ItemFieldEnv env = {};
	env.half_scale = 0.5f;
	env.margin = 50.0f;
	env.collect_all = &CollectAll;

	float size[2] = {4.0f, 4.0f};
	float inside[2] = {50.0f, 50.0f};
	float near_edge[2] = {-10.0f, 50.0f};
	float far_away[2] = {-200.0f, 50.0f};

	// Inside triggers collection when the timer allows it.
	assert(Item_TestFieldContact(inside, size, &field, &env) == 1);
	assert(g_collect_calls == 1);
	field.autocollect_timer = 5;
	assert(Item_TestFieldContact(inside, size, &field, &env) == 1);
	assert(g_collect_calls == 1);

	// Suppressed modes and active dialogue return 1 without collecting.
	field.autocollect_timer = 0;
	field.mode = 3;
	assert(Item_TestFieldContact(inside, size, &field, &env) == 0);
	field.mode = 0;
	int dialogue = 1;
	env.dialogue_active = &dialogue;
	assert(Item_TestFieldContact(inside, size, &field, &env) == 0);
	env.dialogue_active = 0;

	// Outside but within the margin keeps the item alive.
	assert(Item_TestFieldContact(near_edge, size, &field, &env) == 2);
	// Far outside lets it die.
	assert(Item_TestFieldContact(far_away, size, &field, &env) == 0);
}

// --- AnmSurface_UploadPixels (0x00446D70) -----------------------------------

int g_lock_calls = 0;
int g_file_load_calls = 0;
const Byte* g_mem_pixels = 0;
int g_mem_format = -1;
int g_mem_pitch = -1;
int g_mem_width = -1;
int g_mem_height = -1;
int g_release_calls = 0;
int g_finalize_calls = 0;
int g_surface_cookie = 0;

void* LockLevelSurface(void*) { ++g_lock_calls; return &g_surface_cookie; }
int LoadFromFileMemory(void*, const Byte*) { ++g_file_load_calls; return 0; }
int LoadFromMemory(void*, const Byte* pixels, int format, int pitch,
                   int width, int height) {
	g_mem_pixels = pixels;
	g_mem_format = format;
	g_mem_pitch = pitch;
	g_mem_width = width;
	g_mem_height = height;
	return 0;
}
void ReleaseSurface(void*) { ++g_release_calls; }
void FinalizeTexture(void*) { ++g_finalize_calls; }

void TestTextureUpload() {
	int format_ids[8] = {0, 0x15, 0x14, 21, 22, 23, 24, 25};
	int bytes_per_pixel[8] = {4, 4, 2, 2, 4, 2, 1, 4};
	AnmUploadEnv env = {};
	env.format_ids = format_ids;
	env.bytes_per_pixel = bytes_per_pixel;
	env.lock_level_surface = &LockLevelSurface;
	env.load_from_file_memory = &LoadFromFileMemory;
	env.load_from_memory = &LoadFromMemory;
	env.release_surface = &ReleaseSurface;
	env.finalize_texture = &FinalizeTexture;

	int texture_cookie = 0;
	int bpp = -1;

	// File-in-memory path.
	Byte file_bytes[4] = {};
	assert(AnmSurface_UploadPixels(&texture_cookie, 4, 0, file_bytes, &bpp,
	                                &env) == 0);
	assert(g_lock_calls == 1 && g_file_load_calls == 1);
	assert(g_release_calls == 1 && g_finalize_calls == 1);
	assert(bpp == 4);

	// 16-bit remap: format id 0x15 remaps index to 5.
	env.config_flags = 1;
	assert(AnmSurface_UploadPixels(&texture_cookie, 1, 0, file_bytes, &bpp,
	                                &env) == 0);
	assert(bpp == 2);  // bytes_per_pixel[5]

	// Sprite-header path reads format/width/height from the header.
	Byte header[0x20] = {};
	short format = 6;
	short width = 8;
	short height = 4;
	std::memcpy(header + 6, &format, 2);
	std::memcpy(header + 8, &width, 2);
	std::memcpy(header + 10, &height, 2);
	env.config_flags = 0;
	assert(AnmSurface_UploadPixels(&texture_cookie, 4, 1, header, &bpp,
	                                &env) == 0);
	assert(g_mem_pixels == header + 0x10);
	assert(g_mem_format == 24);      // format_ids[6]
	assert(g_mem_pitch == 8 * 1);    // width * bytes_per_pixel[6]
	assert(g_mem_width == 8 && g_mem_height == 4);
	assert(bpp == 1);                // bytes_per_pixel[6]
}

// --- Texture restore (0x00447FD0 / 0x00448120) -------------------------------

int g_cooperative_result = 0;
int g_create_default_result = 0;
int g_create_managed_result = 0;
int g_create_default_calls = 0;
int g_create_managed_calls = 0;
int g_copy_calls = 0;
int g_copy_result = 0;
int g_restore_release_calls = 0;
int g_update_surface_calls = 0;
const int* g_update_rect = 0;
int g_texture_cookie = 0;
int g_level_cookie = 0;

int TestCooperative(void*) { return g_cooperative_result; }
int CreateDefaultTexture(void*, int, int, int, void** out) {
	++g_create_default_calls;
	if (g_create_default_result == 0) *out = &g_texture_cookie;
	return g_create_default_result;
}
int CreateManagedTexture(void*, int, int, int, void** out) {
	++g_create_managed_calls;
	if (g_create_managed_result == 0) *out = &g_texture_cookie;
	return g_create_managed_result;
}
int CopySurface(void*, void*) { ++g_copy_calls; return g_copy_result; }
void* GetLevelSurface(void*) { return &g_level_cookie; }
void ReleaseObject(void*) { ++g_restore_release_calls; }
void UpdateSurface(void*, void*, void*, const int* rect) {
	++g_update_surface_calls;
	g_update_rect = rect;
}

void TestTextureRestore() {
	int cached_cookie = 0;
	AnmRestoreEnv env = {};
	env.test_cooperative = &TestCooperative;
	env.create_render_texture = &CreateDefaultTexture;
	env.create_managed_texture = &CreateManagedTexture;
	env.copy_surface = &CopySurface;
	env.get_level_surface = &GetLevelSurface;
	env.release_object = &ReleaseObject;
	env.update_surface = &UpdateSurface;

	// No cached surface: nothing happens.
	AnmTextureSlot slot = {};
	slot.width = 256;
	slot.height = 128;
	AnmArchive_RestoreTexture(&slot, &env);
	assert(g_update_surface_calls == 0);

	// Device not cooperative: nothing happens.
	slot.cached_surface = &cached_cookie;
	g_cooperative_result = 1;
	AnmArchive_RestoreTexture(&slot, &env);
	assert(g_update_surface_calls == 0);

	// Default-pool creation fails, managed fallback succeeds, then the
	// level surface refreshes.
	g_cooperative_result = 0;
	g_create_default_result = 1;
	AnmArchive_RestoreTexture(&slot, &env);
	assert(g_create_default_calls == 1 && g_create_managed_calls == 1);
	assert(g_copy_calls == 1);
	assert(slot.texture == &g_texture_cookie);
	assert(g_update_surface_calls == 1);
	assert(g_restore_release_calls == 1);  // level surface released

	// Existing texture skips creation; rect variant forwards the rect.
	int rect[4] = {1, 2, 3, 4};
	AnmArchive_RestoreTextureRect(&slot, rect, &env);
	assert(g_create_default_calls == 1 && g_create_managed_calls == 1);
	assert(g_update_surface_calls == 2);
	assert(g_update_rect == rect);
}

// --- EnemyPool_BlastRadius (0x00408100) --------------------------------------

int g_kill_calls = 0;
BlastEnemy* g_last_killed = 0;
int g_convert_result = 0;
int g_convert_calls = 0;
int g_effect_calls = 0;
int g_effect_id = -1;
float g_effect_angle = 0.0f;
float g_effect_scale = 0.0f;

void KillEnemy(BlastEnemy* enemy) {
	++g_kill_calls;
	g_last_killed = enemy;
}
int ConvertToItem(float*, float, float) { ++g_convert_calls; return g_convert_result; }
void SpawnEffect(void*, int id, Word, float angle, float scale) {
	++g_effect_calls;
	g_effect_id = id;
	g_effect_angle = angle;
	g_effect_scale = scale;
}

void TestBlastRadius() {
	BlastEnemy enemies[4] = {};
	// In range and alive.
	enemies[0].state = 1;
	enemies[0].position[0] = 3.0f;
	enemies[0].position[1] = 4.0f;   // distance 5
	enemies[0].size = 2.0f;          // reach = 1 + 10 = 11
	// Free slot.
	enemies[1].state = 0;
	enemies[1].position[0] = 1.0f;
	// Dying.
	enemies[2].state = 3;
	enemies[2].position[0] = 1.0f;
	// Boss in range.
	enemies[3].state = 1;
	enemies[3].boss_flag = 1;
	enemies[3].position[0] = 1.0f;

	float center[2] = {0.0f, 0.0f};
	BlastEnv env = {};
	env.half_scale = 0.5f;
	env.kill_enemy = &KillEnemy;
	env.convert_to_item = &ConvertToItem;
	env.spawn_effect = &SpawnEffect;

	// Boss skipped, effect spawned for non-converting kills.
	g_convert_result = 0;
	assert(EnemyPool_BlastRadius(enemies, 4, center, 10.0f, 1, 1, &env) == 0);
	assert(g_kill_calls == 1);
	assert(g_last_killed == &enemies[0]);
	assert(g_convert_calls == 1);
	assert(g_effect_calls == 1);
	assert(g_effect_id == 8);
	assert(fabsf(g_effect_angle + 1.5707964f) < 1e-6f);
	assert(fabsf(g_effect_scale - 0.6f) < 1e-6f);

	// Bosses included when skip_bosses is 0; converted kills skip the effect.
	enemies[0].state = 1;
	g_convert_result = 1;
	assert(EnemyPool_BlastRadius(enemies, 4, center, 10.0f, 1, 0, &env) == 0);
	assert(g_kill_calls == 3);       // enemy 0 again + boss
	assert(g_effect_calls == 1);     // no new effects

	// Out-of-range enemies survive.
	enemies[0].position[0] = 100.0f;
	enemies[3].position[0] = 100.0f;
	g_kill_calls = 0;
	assert(EnemyPool_BlastRadius(enemies, 4, center, 10.0f, 0, 0, &env) == 0);
	assert(g_kill_calls == 0);
}

} // namespace

int main() {
	TestFrameRateCounter();
	TestEndingDispatch();
	TestViewportCallbacks();
	TestRelinkActive();
	TestBulletOnDraw();
	TestTitleLoadCoreAssets();
	TestMidiVolumes();
	TestSoundInitCommonBuffers();
	TestAnmDrawDispatch();
	TestStageScriptLoad();
	TestEnemyAccelStep();
	TestEnemyHomingStep();
	TestEnemyEaseSteps();
	TestEnemySpawner();
	TestPauseMenuReset();
	TestItemFieldContact();
	TestTextureUpload();
	TestTextureRestore();
	TestBlastRadius();
	std::printf("BATCH9_TESTS_PASS\n");
	return 0;
}
