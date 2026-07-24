// Tests for recovery batch 24 (0x0043CD30 sound-device worker init).
#include "th10/platform/sound_device_init.hpp"
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

static char g_log[512];
static void Log(const char* text) {
	std::strncat(g_log, text, sizeof(g_log) - std::strlen(g_log) - 1);
}

static void* g_cell_storage;
static void** g_cell;
static int g_fake_device;
static int g_fake_buffer;
static unsigned char g_stream_memory[0x8000];

static void** HookAllocateCell() {
	Log("new;");
	g_cell_storage = 0;
	g_cell = &g_cell_storage;
	return g_cell;
}

static void** g_freed_cell;
static void HookFreeCell(void** cell) {
	g_freed_cell = cell;
	Log("free;");
}

static void* g_released_device;
static int g_release_count;
static void HookReleaseDevice(void* device) {
	g_released_device = device;
	++g_release_count;
	Log("release;");
}

static int g_create_device_result;
static int HookCreateDevice(void** cell) {
	Log("create;");
	if (g_create_device_result >= 0)
		*cell = &g_fake_device;
	return g_create_device_result;
}

static int g_coop_result;
static void* g_coop_device;
static void* g_coop_window;
static int g_coop_level;
static int HookSetCooperativeLevel(void* device, void* window, int level) {
	Log("coop;");
	g_coop_device = device;
	g_coop_window = window;
	g_coop_level = level;
	return g_coop_result;
}

static int g_format_result;
static int g_format_bits;
static int g_format_channels;
static int g_format_rate;
static void** g_format_cell;
static int g_format_count;
static int HookSetPrimaryFormat(int bits, int channels, int rate,
                                void** cell) {
	Log("format;");
	++g_format_count;
	g_format_bits = bits;
	g_format_channels = channels;
	g_format_rate = rate;
	g_format_cell = cell;
	return g_format_result;
}

static int g_create_buffer_result;
static void* g_create_buffer_device;
static SoundInitBufferDesc g_seen_desc;
static SoundInitWaveFormat g_seen_format;
static int HookCreateBuffer(void* device, const SoundInitBufferDesc* desc,
                            void** buffer_out) {
	Log("buffer;");
	g_create_buffer_device = device;
	g_seen_desc = *desc;
	g_seen_format = *desc->format;
	if (g_create_buffer_result >= 0)
		*buffer_out = &g_fake_buffer;
	return g_create_buffer_result;
}

static int g_lock_result;
static void* g_lock_buffer;
static unsigned int g_lock_offset;
static unsigned int g_lock_bytes;
static unsigned int g_lock_flags;
static int HookLockBuffer(void* buffer, unsigned int offset,
                          unsigned int bytes, void** region1,
                          unsigned int* length1, void** region2,
                          unsigned int* length2, unsigned int flags) {
	Log("lock;");
	g_lock_buffer = buffer;
	g_lock_offset = offset;
	g_lock_bytes = bytes;
	g_lock_flags = flags;
	if (g_lock_result >= 0) {
		*region1 = g_stream_memory;
		*length1 = sizeof(g_stream_memory);
		*region2 = 0;
		*length2 = 0;
	}
	return g_lock_result;
}

static void* g_unlock_buffer;
static void* g_unlock_region1;
static unsigned int g_unlock_length1;
static void* g_unlock_region2;
static unsigned int g_unlock_length2;
static void HookUnlockBuffer(void* buffer, void* region1,
                             unsigned int length1, void* region2,
                             unsigned int length2) {
	Log("unlock;");
	g_unlock_buffer = buffer;
	g_unlock_region1 = region1;
	g_unlock_length1 = length1;
	g_unlock_region2 = region2;
	g_unlock_length2 = length2;
}

static void* g_play_buffer;
static int g_play_reserved1;
static int g_play_reserved2;
static int g_play_flags;
static void HookPlayBuffer(void* buffer, int reserved1, int reserved2,
                           int flags) {
	Log("play;");
	g_play_buffer = buffer;
	g_play_reserved1 = reserved1;
	g_play_reserved2 = reserved2;
	g_play_flags = flags;
}

static void* g_timer_window;
static unsigned int g_timer_id;
static unsigned int g_timer_ms;
static int g_timer_count;
static void HookSetTimer(void* window, unsigned int timer_id,
                         unsigned int milliseconds) {
	Log("timer;");
	++g_timer_count;
	g_timer_window = window;
	g_timer_id = timer_id;
	g_timer_ms = milliseconds;
}

static const char* g_log_message;
static const char* g_log_argument;
static int g_log_count;
static void HookLog(const char* message, const char* argument) {
	Log("log;");
	++g_log_count;
	g_log_message = message;
	g_log_argument = argument;
}

static int g_load_indices[48];
static const char* g_load_names[48];
static int g_load_count;
static int g_load_fail_index;
static int g_load_shutdown_after; // set shutdown flag to 2 after this index
static volatile int g_shutdown_flag;
static int HookLoadWave(int index, const char* filename) {
	const int i = g_load_count < 48 ? g_load_count : 47;
	g_load_indices[i] = index;
	g_load_names[i] = filename;
	++g_load_count;
	if (g_load_shutdown_after >= 0 && index >= g_load_shutdown_after)
		g_shutdown_flag = 2;
	return g_load_fail_index >= 0 && index == g_load_fail_index ? 1 : 0;
}

static const char* g_filenames[37];
static char g_filename_storage[37][16];
static int g_window_tag;

static void MakeEnv(SoundInitEnv* env) {
	std::memset(env, 0, sizeof(*env));
	env->allocate_cell = HookAllocateCell;
	env->free_cell = HookFreeCell;
	env->release_device = HookReleaseDevice;
	env->create_device = HookCreateDevice;
	env->set_cooperative_level = HookSetCooperativeLevel;
	env->set_primary_format = HookSetPrimaryFormat;
	env->create_buffer = HookCreateBuffer;
	env->lock_buffer = HookLockBuffer;
	env->unlock_buffer = HookUnlockBuffer;
	env->play_buffer = HookPlayBuffer;
	env->set_timer = HookSetTimer;
	env->log = HookLog;
	env->load_wave = HookLoadWave;
	for (int i = 0; i < 37; ++i) {
		std::snprintf(g_filename_storage[i], sizeof(g_filename_storage[i]),
		              "se%02d.wav", i);
		g_filenames[i] = g_filename_storage[i];
	}
	env->filenames = g_filenames;
	env->shutdown_flag = &g_shutdown_flag;
	g_log[0] = 0;
	g_cell = 0;
	g_cell_storage = 0;
	g_freed_cell = 0;
	g_released_device = 0;
	g_release_count = 0;
	g_create_device_result = 0;
	g_coop_result = 0;
	g_format_result = 0;
	g_format_count = 0;
	g_create_buffer_result = 0;
	g_lock_result = 0;
	g_timer_count = 0;
	g_log_message = 0;
	g_log_argument = 0;
	g_log_count = 0;
	g_load_count = 0;
	g_load_fail_index = -1;
	g_load_shutdown_after = -1;
	g_shutdown_flag = 0;
	std::memset(g_stream_memory, 0xAB, sizeof(g_stream_memory));
}

static void MakeDevice(SoundDevice* device) {
	std::memset(device, 0, sizeof(*device));
}

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

static void TestSuccessPath() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == 0);
	// Handle tables are cleared to -1 before anything else.
	for (int i = 0; i < 128; ++i)
		CHECK(device.buffer_handles[i] == -1);
	for (int i = 0; i < 12; ++i)
		CHECK(device.music_handles[i] == -1);
	// The device cell holds the created interface and is published.
	CHECK(device.device_cell == g_cell);
	CHECK(g_cell_storage == &g_fake_device);
	CHECK(device.device == &g_fake_device);
	CHECK(device.stream_cursor == 0);
	// Cooperative level 2 on the created device against the window.
	CHECK(g_coop_device == &g_fake_device);
	CHECK(g_coop_window == &g_window_tag);
	CHECK(g_coop_level == 2);
	// Primary format request is 16-bit stereo 44100 on the cell.
	CHECK(g_format_count == 1);
	CHECK(g_format_bits == 16);
	CHECK(g_format_channels == 2);
	CHECK(g_format_rate == 44100);
	CHECK(g_format_cell == g_cell);
	// Streaming buffer description matches the retail stack image.
	CHECK(g_create_buffer_device == &g_fake_device);
	CHECK(g_seen_desc.size == 36);
	CHECK(g_seen_desc.flags == 32776);
	CHECK(g_seen_desc.bytes == 0x8000u);
	CHECK(g_seen_desc.reserved == 0);
	CHECK(g_seen_format.tag == 1);
	CHECK(g_seen_format.channels == 2);
	CHECK(g_seen_format.rate == 44100u);
	CHECK(g_seen_format.avg_bytes == 176400u);
	CHECK(g_seen_format.block_align == 4);
	CHECK(g_seen_format.bits == 16);
	CHECK(g_seen_format.cb_size == 0);
	CHECK(device.stream_buffer == &g_fake_buffer);
	// Lock/zero/unlock/play sequence over the whole buffer.
	CHECK(g_lock_buffer == &g_fake_buffer);
	CHECK(g_lock_offset == 0);
	CHECK(g_lock_bytes == 0x8000u);
	CHECK(g_lock_flags == 0);
	int all_zero = 1;
	for (unsigned int i = 0; i < sizeof(g_stream_memory); ++i)
		all_zero &= g_stream_memory[i] == 0;
	CHECK(all_zero);
	CHECK(g_unlock_buffer == &g_fake_buffer);
	CHECK(g_unlock_region1 == g_stream_memory);
	CHECK(g_unlock_length1 == 0x8000u);
	CHECK(g_unlock_region2 == 0);
	CHECK(g_unlock_length2 == 0);
	CHECK(g_play_buffer == &g_fake_buffer);
	CHECK(g_play_reserved1 == 0);
	CHECK(g_play_reserved2 == 0);
	CHECK(g_play_flags == 1);
	// Volumes, timer, and window publication.
	CHECK(device.volume_a == 100);
	CHECK(device.volume_b == 100);
	CHECK(g_timer_count == 1);
	CHECK(g_timer_window == &g_window_tag);
	CHECK(g_timer_id == 0);
	CHECK(g_timer_ms == 250u);
	CHECK(device.window == &g_window_tag);
	// All 37 WAVs preload in order with their table filenames.
	CHECK(g_load_count == 37);
	CHECK(g_load_indices[0] == 0);
	CHECK(g_load_indices[36] == 36);
	CHECK(g_load_names[0] == g_filenames[0]);
	CHECK(g_load_names[36] == g_filenames[36]);
	// Success log with no argument.
	CHECK(g_log_count == 1);
	CHECK(g_log_message == kSoundInitLogDirectSoundReady);
	CHECK(g_log_argument == 0);
	// Full edge order.
	CHECK(std::strcmp(g_log,
	                  "new;create;coop;format;buffer;lock;unlock;play;"
	                  "timer;log;") == 0);
}

static void TestDeviceCreateFailure() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	g_create_device_result = -1;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	// Error log, cell freed, slot cleared; nothing was created so no
	// interface release happens.
	CHECK(g_log_count == 1);
	CHECK(g_log_message == kSoundInitLogDirectSoundError);
	CHECK(g_release_count == 0);
	CHECK(g_freed_cell == g_cell);
	CHECK(device.device_cell == 0);
	CHECK(g_format_count == 0);
	CHECK(g_timer_count == 0);
	CHECK(g_load_count == 0);
	CHECK(std::strcmp(g_log, "new;create;log;free;") == 0);
}

static void TestCooperativeLevelFailure() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	g_coop_result = -1;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	// The created interface is released and its slot zeroed before free.
	CHECK(g_release_count == 1);
	CHECK(g_released_device == &g_fake_device);
	CHECK(g_cell_storage == 0);
	CHECK(g_freed_cell == g_cell);
	CHECK(device.device_cell == 0);
	CHECK(g_log_message == kSoundInitLogDirectSoundError);
	CHECK(std::strcmp(g_log, "new;create;coop;log;release;free;") == 0);
}

static void TestPrimaryFormatFailureIsIgnored() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	g_format_result = -1;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == 0);
	CHECK(g_format_count == 1);
	CHECK(g_load_count == 37);
}

static void TestBufferCreateFailure() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	g_create_buffer_result = -1;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	// No lock, play, timer, loads, or logs; the cell survives.
	CHECK(std::strcmp(g_log, "new;create;coop;format;buffer;") == 0);
	CHECK(device.device_cell == g_cell);
	CHECK(device.device == &g_fake_device);
}

static void TestLockFailure() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	g_lock_result = -1;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	CHECK(std::strcmp(g_log, "new;create;coop;format;buffer;lock;") == 0);
	// The buffer memory is untouched on a lock failure.
	CHECK(g_stream_memory[0] == 0xAB);
}

static void TestLoadFailure() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	g_load_fail_index = 3;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	CHECK(g_load_count == 4);
	CHECK(g_log_count == 1);
	CHECK(g_log_message == kSoundInitLogSoundError);
	CHECK(g_log_argument == g_filenames[3]);
}

static void TestShutdownAbortsPreload() {
	SoundInitEnv env;
	SoundDevice device;
	MakeEnv(&env);
	MakeDevice(&device);
	// The flag flips to 2 after the load of index 5 completes; the poll
	// before index 6 aborts the loop.
	g_load_shutdown_after = 5;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	CHECK(g_load_count == 6);
	CHECK(g_log_count == 0);
	// A pre-set shutdown flag skips the preload entirely.
	MakeEnv(&env);
	MakeDevice(&device);
	g_shutdown_flag = 2;
	CHECK(SoundDevice_InitializeWorker(&device, &g_window_tag, &env) == -1);
	CHECK(g_load_count == 0);
	CHECK(g_timer_count == 1);
}

int main() {
	TestSuccessPath();
	TestDeviceCreateFailure();
	TestCooperativeLevelFailure();
	TestPrimaryFormatFailureIsIgnored();
	TestBufferCreateFailure();
	TestLockFailure();
	TestLoadFailure();
	TestShutdownAbortsPreload();

	if (g_failures != 0) {
		std::printf("%d check(s) failed\n", g_failures);
		return 1;
	}
	std::printf("recovery_batch24_test passed\n");
	return 0;
}
