// Tests for recovery batch 22 (0x0040BA90 / 0x0044D850 / 0x00445620).
#include "th10/game/ending_text.hpp"
#include "th10/platform/bgm_streamer_refill.hpp"
#include "th10/render/effect_ring_update.hpp"
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
// EndingText_Construct
// ---------------------------------------------------------------------------

static EndingAnimationVm g_vms[5];
static int g_alloc_count;
static int g_scripts[5];
static void* g_manager_seen;
static EndingAnimationVm* g_registry[8];
static int g_registry_count;
static int g_fail_handle;
static float g_frame_speed = 1.0f;
static int g_dummy_vtable;

static EndingAnimationVm* TestAllocateVm(void* manager) {
	g_manager_seen = manager;
	return &g_vms[g_alloc_count++];
}
static void TestInitScript(EndingAnimationVm* vm, int script) {
	g_scripts[vm - g_vms] = script;
}
static int TestRegisterVm(EndingAnimationVm* vm, void* manager) {
	(void)manager;
	vm->handle = 100 + g_registry_count;
	g_registry[g_registry_count++] = vm;
	return vm->handle;
}
static EndingAnimationVm* TestFindVm(void* manager, int handle) {
	(void)manager;
	if (handle == 0 || handle == g_fail_handle) {
		return 0;
	}
	for (int i = 0; i < g_registry_count; ++i) {
		if (g_registry[i]->handle == handle) {
			return g_registry[i];
		}
	}
	return 0;
}

static void ResetEndingFixture() {
	std::memset(g_vms, 0, sizeof(g_vms));
	std::memset(g_scripts, 0, sizeof(g_scripts));
	g_alloc_count = 0;
	g_registry_count = 0;
	g_manager_seen = 0;
	g_fail_handle = 0;
}

static void TestEndingTextConstruct() {
	ResetEndingFixture();
	int manager = 0;
	EndingTextEnv env = {};
	env.manager = &manager;
	env.allocate_vm = TestAllocateVm;
	env.init_script = TestInitScript;
	env.register_vm = TestRegisterVm;
	env.find_vm = TestFindVm;
	env.frame_speed = &g_frame_speed;
	env.on_deck_vtable = &g_dummy_vtable;

	unsigned char script[8] = {};
	EndingText text;
	std::memset(&text, 0xAB, sizeof(text)); // garbage to verify the clear
	EndingText* result = EndingText_Construct(&text, script, &env);

	CHECK(result == &text);
	CHECK(g_alloc_count == 5);
	CHECK(g_manager_seen == &manager);
	for (int slot = 0; slot < 5; ++slot) {
		CHECK(text.vm_handles[slot] == 100 + slot);
		CHECK(g_scripts[slot] == 0x42 + slot);
		CHECK(g_vms[slot].layer == 15);
		CHECK((g_vms[slot].anim_flags & 0x40000000u) != 0);
		CHECK(g_vms[slot].marker_a == 0x10);
		CHECK(g_vms[slot].marker_b == 0x10);
		CHECK((g_vms[slot].state_flags & 2u) != 0);
	}
	CHECK(text.script_cursor == script);
	CHECK(text.handle == 0);
	for (int i = 0; i < 7; ++i) {
		CHECK(text.fields_58[i] == 0);
	}
	const EndingTimer* timers[3] = {&text.timer_a, &text.timer_b,
	                                 &text.timer_c};
	for (int i = 0; i < 3; ++i) {
		CHECK(timers[i]->previous == -1);
		CHECK(timers[i]->current == 0);
		CHECK(timers[i]->elapsed == 0.0f);
		CHECK(timers[i]->speed == &g_frame_speed);
		CHECK(timers[i]->flags == 1u);
	}
	CHECK(text.flags == 1u);
	CHECK(text.color == 0x00FFFFFFu);
	CHECK(text.on_deck_vtable == &g_dummy_vtable);

	// A failed handle resolve zeroes the stored handle and skips the markers.
	ResetEndingFixture();
	g_fail_handle = 103; // slot 3
	std::memset(&text, 0, sizeof(text));
	EndingText_Construct(&text, script, &env);
	CHECK(text.vm_handles[2] == 102);
	CHECK(text.vm_handles[3] == 0);
	CHECK(text.vm_handles[4] == 104);
	CHECK(g_vms[3].marker_a == 0);
	CHECK(g_vms[3].marker_b == 0);
	CHECK((g_vms[3].state_flags & 2u) == 0);
}

// ---------------------------------------------------------------------------
// Streamer_RefillSegment
// ---------------------------------------------------------------------------

struct StreamFixture {
	unsigned char buffer[0x1000];
	unsigned int play_sequence[2];
	int play_index;
	int prime_status;
	int restored;
	int lock_status;
	void* wrap_ptr;
	int read_status;
	unsigned char read_fill;
	int full_refill_status;
	int full_refill_calls;
	int lock_calls;
	int unlock_calls;
	int stop_calls;
	unsigned int locked_offset;
	unsigned int locked_request;
	unsigned char* unlocked_ptr;
	unsigned int unlocked_bytes;
};

static int FixGetPlayCursor(void* context, unsigned int* play_cursor) {
	StreamFixture* fixture = (StreamFixture*)context;
	*play_cursor = fixture->play_sequence[fixture->play_index];
	if (fixture->play_index < 1) {
		++fixture->play_index;
	}
	return 0;
}
static int FixPrimeBuffers(void* context, int* restored) {
	StreamFixture* fixture = (StreamFixture*)context;
	*restored = fixture->restored;
	return fixture->prime_status;
}
static int FixFullRefill(void* context) {
	StreamFixture* fixture = (StreamFixture*)context;
	++fixture->full_refill_calls;
	return fixture->full_refill_status;
}
static int FixLockSegment(void* context, unsigned int offset,
                          unsigned int bytes, unsigned char** pcm,
                          unsigned int* locked_bytes, void** wrap_pcm) {
	StreamFixture* fixture = (StreamFixture*)context;
	++fixture->lock_calls;
	fixture->locked_offset = offset;
	fixture->locked_request = bytes;
	*pcm = fixture->buffer + offset;
	*locked_bytes = bytes;
	*wrap_pcm = fixture->wrap_ptr;
	return fixture->lock_status;
}
static int FixReadPcm(void* context, unsigned char* pcm, unsigned int bytes) {
	StreamFixture* fixture = (StreamFixture*)context;
	if (fixture->read_status >= 0) {
		std::memset(pcm, fixture->read_fill, bytes);
	}
	return fixture->read_status;
}
static void FixUnlockSegment(void* context, unsigned char* pcm,
                             unsigned int locked_bytes) {
	StreamFixture* fixture = (StreamFixture*)context;
	++fixture->unlock_calls;
	fixture->unlocked_ptr = pcm;
	fixture->unlocked_bytes = locked_bytes;
}
static void FixStopBuffer(void* context) {
	++((StreamFixture*)context)->stop_calls;
}

static void InitStreamFixture(StreamFixture* fixture, StreamerEnv* env,
                              StreamerState* state) {
	std::memset(fixture, 0, sizeof(*fixture));
	fixture->read_fill = 0x11;
	env->context = fixture;
	env->get_play_cursor = FixGetPlayCursor;
	env->prime_buffers = FixPrimeBuffers;
	env->full_refill = FixFullRefill;
	env->lock_segment = FixLockSegment;
	env->read_pcm = FixReadPcm;
	env->unlock_segment = FixUnlockSegment;
	env->stop_buffer = FixStopBuffer;
	std::memset(state, 0, sizeof(*state));
	state->has_buffer = 1;
	state->has_reader = 1;
	state->buffer_bytes = 0x1000;
	state->segment_bytes = 0x400;
	state->write_offset = 0x400;
	state->total_pcm_bytes = 0x100000;
	state->bits_per_sample = 16;
}

static void TestStreamerRefillSegment() {
	StreamFixture fixture;
	StreamerEnv env;
	StreamerState state;

	// Missing buffer or reader reports not-ready.
	InitStreamFixture(&fixture, &env, &state);
	state.has_buffer = 0;
	CHECK(Streamer_RefillSegment(&state, &env) == (int)kStreamerNotReady);
	InitStreamFixture(&fixture, &env, &state);
	state.has_reader = 0;
	CHECK(Streamer_RefillSegment(&state, &env) == (int)kStreamerNotReady);

	// Play cursor inside the pending segment: busy, nothing locked.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0x500;
	fixture.play_sequence[1] = 0x500;
	CHECK(Streamer_RefillSegment(&state, &env) == (int)kStreamerNotReady);
	CHECK(fixture.lock_calls == 0);

	// Normal decode path: one segment locked, decoded, unlocked, progress
	// accounted, write offset advanced.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0xC00;
	fixture.play_sequence[1] = 0xC80;
	state.last_play_cursor = 0xC00;
	CHECK(Streamer_RefillSegment(&state, &env) == 0);
	CHECK(fixture.lock_calls == 1);
	CHECK(fixture.locked_offset == 0x400);
	CHECK(fixture.locked_request == 0x400);
	CHECK(fixture.buffer[0x400] == 0x11 && fixture.buffer[0x7FF] == 0x11);
	CHECK(fixture.unlock_calls == 1);
	CHECK(fixture.unlocked_ptr == fixture.buffer + 0x400);
	CHECK(fixture.unlocked_bytes == 0x400);
	CHECK(state.total_streamed == 0x80);
	CHECK(state.last_play_cursor == 0xC80);
	CHECK(state.write_offset == 0x800);
	CHECK(fixture.stop_calls == 0);

	// Wraparound progress accounting.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0x000;
	fixture.play_sequence[1] = 0x080;
	state.write_offset = 0x800;
	state.last_play_cursor = 0xF00;
	CHECK(Streamer_RefillSegment(&state, &env) == 0);
	CHECK(state.total_streamed == 0x180);
	CHECK(state.write_offset == 0xC00);

	// Lost-and-restored buffer: full rewrite instead of one segment.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0xC00;
	fixture.play_sequence[1] = 0xC00;
	fixture.restored = 1;
	CHECK(Streamer_RefillSegment(&state, &env) == 0);
	CHECK(fixture.full_refill_calls == 1);
	CHECK(fixture.lock_calls == 0);

	// Wrapped lock region is unexpected.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0xC00;
	fixture.play_sequence[1] = 0xC00;
	fixture.wrap_ptr = fixture.buffer;
	CHECK(Streamer_RefillSegment(&state, &env) == (int)kStreamerUnexpected);

	// End of stream: 8-bit silence and a stop once the tail played out.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0xC00;
	fixture.play_sequence[1] = 0xC00;
	state.last_play_cursor = 0xC00;
	state.end_of_stream = 1;
	state.bits_per_sample = 8;
	state.total_pcm_bytes = 0x40;
	state.total_streamed = 0x40;
	CHECK(Streamer_RefillSegment(&state, &env) == 0);
	CHECK(fixture.buffer[0x400] == 0x80 && fixture.buffer[0x7FF] == 0x80);
	CHECK(fixture.stop_calls == 1);

	// Decode failure propagates.
	InitStreamFixture(&fixture, &env, &state);
	fixture.play_sequence[0] = 0xC00;
	fixture.play_sequence[1] = 0xC00;
	fixture.read_status = -5;
	CHECK(Streamer_RefillSegment(&state, &env) == -5);
}

// ---------------------------------------------------------------------------
// EffectRing_Update
// ---------------------------------------------------------------------------

static void TestEffectRingUpdate() {
	static EffectRingState ring;
	std::memset(&ring, 0, sizeof(ring));
	CHECK(sizeof(ring) == 0x4B0);

	EffectRingOwner owner = {};
	owner.diffuse = 0xDD3366CCu;
	owner.base_position[0] = 100.0f;
	owner.base_position[1] = 50.0f;
	owner.base_position[2] = 0.25f;
	owner.offset_position[0] = 4.0f;
	owner.offset_position[1] = -2.0f;
	owner.offset_position[2] = 0.0f;
	owner.ring = &ring;

	ring.uv_scroll_speed = 0.25f;
	for (int i = 0; i < 33; ++i) {
		ring.vertices[i].u = 0.5f;
		ring.vertices[i].v = 0.5f;
		ring.vertices[i].w = 1.0f;
	}
	for (int i = 0; i < 31; ++i) {
		ring.radius[i] = 10.0f;
		ring.radial_speed[i] = 0.5f;
	}

	CHECK(EffectRing_Update(&owner) == 0);

	const float cx = 104.0f, cy = 48.0f, cz = 0.25f;
	CHECK(ring.vertices[0].x == cx);
	CHECK(ring.vertices[0].y == cy);
	CHECK(ring.vertices[0].z == cz);
	CHECK(ring.vertices[0].diffuse == 0xDD3366CCu); // center keeps alpha
	CHECK(NearlyEqual(ring.vertices[0].u, 0.75f, 1e-6f));
	CHECK(NearlyEqual(ring.vertices[0].v, 0.75f, 1e-6f));

	// Rim vertex 1 sits at angle -pi with the grown radius 10.5.
	CHECK(ring.radius[0] == 10.5f);
	CHECK(NearlyEqual(ring.vertices[1].x, cx - 10.5f, 1e-3f));
	CHECK(NearlyEqual(ring.vertices[1].y, cy, 1e-3f));
	CHECK(NearlyEqual(ring.vertices[1].z, cz, 1e-6f));
	CHECK(ring.vertices[1].diffuse == 0x003366CCu); // rim alpha cleared

	// Retail constant _DAT_00470B6C is float32(2*pi/31), because there are
	// 31 distinct rim vertices and slot 32 closes the fan by duplicating #1.
	const float retail_angle_step = 0.2026834f;
	const float vertex9_angle = -3.1415927f + 8.0f * retail_angle_step;
	CHECK(NearlyEqual(ring.vertices[9].x,
	                  cx + std::cos(vertex9_angle) * 10.5f, 1e-3f));
	CHECK(NearlyEqual(ring.vertices[9].y,
	                  cy + std::sin(vertex9_angle) * 10.5f, 1e-3f));
	const float vertex31_angle = -3.1415927f + 30.0f * retail_angle_step;
	CHECK(NearlyEqual(ring.vertices[31].x,
	                  cx + std::cos(vertex31_angle) * 10.5f, 1e-3f));
	CHECK(NearlyEqual(ring.vertices[31].y,
	                  cy + std::sin(vertex31_angle) * 10.5f, 1e-3f));

	// Slot 32 duplicates rim vertex 1 to close the fan.
	CHECK(std::memcmp(&ring.vertices[32], &ring.vertices[1],
	                  sizeof(EffectRingVertex)) == 0);

	// Negative texture scroll below zero re-wraps the whole column by +1.0:
	// 0.3 - 0.6 = -0.3 triggers the wrap, landing at 0.7; later vertices
	// scroll from the wrapped 1.3 back down to 0.7 without another wrap.
	ring.uv_scroll_speed = -0.6f;
	for (int i = 0; i < 33; ++i) {
		ring.vertices[i].u = 0.3f;
		ring.vertices[i].v = 0.3f;
	}
	CHECK(EffectRing_Update(&owner) == 0);
	CHECK(NearlyEqual(ring.vertices[0].u, 0.7f, 1e-5f));
	CHECK(NearlyEqual(ring.vertices[0].v, 0.7f, 1e-5f));
	CHECK(NearlyEqual(ring.vertices[5].u, 0.7f, 1e-5f));
	CHECK(NearlyEqual(ring.vertices[31].v, 0.7f, 1e-5f));

	// Faithful quirk: rim Z accumulates the owner Z sum every frame.
	CHECK(NearlyEqual(ring.vertices[1].z, 2.0f * cz, 1e-6f));
}

static int g_ring_flushes;
static int g_ring_syncs;
static int g_ring_binds;
static int g_ring_primitives;
static int g_ring_stride;
static const EffectRingVertex* g_ring_vertices;

static void RingFlush(void*) { ++g_ring_flushes; }
static void RingSync(void*) { ++g_ring_syncs; }
static void RingBind(void*) { ++g_ring_binds; }
static void RingDraw(void*, int primitive_count,
                     const EffectRingVertex* vertices, int stride) {
    g_ring_primitives = primitive_count;
    g_ring_vertices = vertices;
    g_ring_stride = stride;
}

static void TestEffectRingDraw() {
    EffectRingState ring = {};
    EffectRingOwner owner = {};
    owner.ring = &ring;
    EffectRingDrawEnv env = {
        nullptr, RingFlush, RingSync, RingBind, RingDraw};
    g_ring_flushes = g_ring_syncs = g_ring_binds = 0;
    g_ring_primitives = g_ring_stride = 0;
    g_ring_vertices = nullptr;
    CHECK(EffectRing_Draw(&owner, &env) == 0);
    CHECK(g_ring_flushes == 2);
    CHECK(g_ring_syncs == 1 && g_ring_binds == 1);
    CHECK(g_ring_primitives == 31);
    CHECK(g_ring_vertices == ring.vertices);
    CHECK(g_ring_stride == (int)sizeof(EffectRingVertex));
}

int main() {
	TestEndingTextConstruct();
	TestStreamerRefillSegment();
	TestEffectRingUpdate();
	TestEffectRingDraw();
	if (g_failures != 0) {
		std::printf("BATCH22_TESTS_FAIL (%d failures)\n", g_failures);
		return 1;
	}
	std::printf("BATCH22_TESTS_PASS\n");
	return 0;
}
