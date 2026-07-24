#include "th10/game/spell_timeout.hpp"
#include "th10/game/trigger_region.hpp"
#include "th10/math/oriented_rect.hpp"
#include "th10/render/special_quad.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {

void TestOrientedRectIntersectsCircle() {
	OrientedRect rect = {{10.0f, 20.0f}, 0.0f, 8.0f, 6.0f};
	OrientedRectVec2 center = {12.0f, 20.0f};
	assert(OrientedRect_IntersectsCircle(&rect, &center, 0.5f) == 2);
	center = {20.0f, 20.0f};
	assert(OrientedRect_IntersectsCircle(&rect, &center, 0.5f) == 0);
	center = {10.0f, 24.0f};
	assert(OrientedRect_IntersectsCircle(&rect, &center, 0.5f) == 0);

	// A quarter-turn maps a point above the center onto local +X.
	rect.angle = 1.57079632679f;
	center = {10.0f, 22.0f};
	assert(OrientedRect_IntersectsCircle(&rect, &center, 0.5f) == 2);
}

int g_activations;
void Activate(TriggerRegion* region) {
	++g_activations;
	region->cooldown = 1;
}

TriggerRegionEnv MakeTriggerEnv() {
	TriggerRegionEnv env;
	env.half_extent_factor = 0.5f;
	env.negative_half_extent_factor = -0.5f;
	env.outer_upper_factor = 1.5f;
	env.outer_lower_factor = -1.5f;
	env.trigger_suppressed = false;
	env.activate = Activate;
	return env;
}

void TestTriggerRegionClassify() {
	TriggerRegionEnv env = MakeTriggerEnv();
	OrientedRectVec2 origin = {0.0f, 0.0f};
	TriggerRegion region = {{3.0f, 0.0f}, 1.0f, 1.0f, 0, 0};
	g_activations = 0;
	assert(TriggerRegion_Classify(&region, &origin, 0.0f, 10.0f, 5.0f,
	                              &env) == 1);
	assert(g_activations == 1 && region.cooldown == 1);

	// Still in the inner rectangle, but cooldown makes it ineligible.
	assert(TriggerRegion_Classify(&region, &origin, 0.0f, 10.0f, 5.0f,
	                              &env) == 0);
	assert(g_activations == 1);

	// Outside the inner vertical range, but inside the wider transition band.
	region.position = {3.0f, 8.0f};
	region.cooldown = 0;
	assert(TriggerRegion_Classify(&region, &origin, 0.0f, 10.0f, 5.0f,
	                              &env) == 2);

	// Outside the horizontal limit entirely.
	region.position = {20.0f, 0.0f};
	assert(TriggerRegion_Classify(&region, &origin, 0.0f, 10.0f, 5.0f,
	                              &env) == 0);

	// Rotation is applied before classification.
	region.position = {0.0f, 3.0f};
	region.mode = 0;
	region.cooldown = 0;
	assert(TriggerRegion_Classify(&region, &origin, 1.57079632679f, 10.0f,
	                              5.0f, &env) == 1);
}

struct StageWrite { unsigned stage, state, value; };
std::vector<StageWrite> g_stage_writes;
int g_flush;
unsigned g_render_state, g_render_value, g_shader;
unsigned g_primitive, g_primitive_count, g_stride;
void Flush() { ++g_flush; }
void SetStage(unsigned stage, unsigned state, unsigned value) {
	g_stage_writes.push_back({stage, state, value});
}
void SetRender(unsigned state, unsigned value) {
	g_render_state = state;
	g_render_value = value;
}
void SetShader(unsigned shader) { g_shader = shader; }
void Draw(unsigned primitive, unsigned count, const void* vertices,
          unsigned stride) {
	assert(vertices != 0);
	g_primitive = primitive;
	g_primitive_count = count;
	g_stride = stride;
}


int g_published_countdown;
int g_stop_calls;
int g_retired[8];
int g_retired_count;
int g_caution_calls;

void TestSpellTimeoutTransition() {
	SpellTimeoutHost host = {};
	for (int i = 0; i < 4; ++i) {
		host.animation_pairs[i].marker = 9;
		host.animation_pairs[i].primary_handle = 10 + i * 2;
		host.animation_pairs[i].secondary_handle = 11 + i * 2;
	}
	host.caution_active = 1;
	host.sound_owner = (void*)0x55;
	SpellTimeoutPlayer player = {};
	player.stage_frames = 60;
	player.charge = 7;
	player.main_flags = 3;
	for (int i = 0; i < 8; ++i) player.option_flags[i] = 3;
	int bonus = 8000;
	int countdown = 2;
	int gauge = 3000;
	float speed = 1.0f;
	g_published_countdown = -1;
	g_stop_calls = g_retired_count = g_caution_calls = 0;
	SpellTimeoutEnv env = {};
	env.bonus_pool = &bonus;
	env.countdown = &countdown;
	env.transition_gauge = &gauge;
	env.frame_speed = &speed;
	env.player = &player;
	env.warning_mode = 0;
	env.publish_countdown = [](int value) { g_published_countdown = value; };
	env.stop_sound = [](void* owner) { assert(owner == (void*)0x55); ++g_stop_calls; };
	env.retire_animation = [](int handle) { g_retired[g_retired_count++] = handle; };
	env.show_caution = [](const char* text) {
		assert(std::strcmp(text, "Caution!") == 0); ++g_caution_calls;
	};

	SpellTimeout_EnterTransition(&host, &env);
	assert(bonus == 7000 && countdown == 1 && g_published_countdown == 1);
	assert(host.phase == 2 && g_stop_calls == 1);
	assert(host.short_timer.target == -1 && host.short_timer.current == 0);
	assert(host.short_timer.speed == &speed && host.short_timer.flags == 1);
	assert(host.grace_timer.target == 179 && host.grace_timer.current == 180);
	assert(host.grace_timer.previous_bits == 0x43340000);
	assert(g_retired_count == 8 && g_retired[0] == 10 && g_retired[7] == 17);
	for (int i = 0; i < 4; ++i) assert(host.animation_pairs[i].marker == 0);
	assert(host.caution_active == 0 && g_caution_calls == 1);
	assert(player.charge == 0 && player.main_flags == 1);
	for (int i = 0; i < 8; ++i) assert(player.option_flags[i] == 1);
	assert(gauge == 1024);

	// Below the frame threshold, player flags survive; the gauge clamps low.
	player.stage_frames = 59;
	player.charge = 5;
	player.main_flags = 3;
	gauge = -500;
	countdown = 0;
	env.warning_mode = 1;
	SpellTimeout_EnterTransition(&host, &env);
	assert(player.charge == 5 && player.main_flags == 3);
	assert(gauge == -1024 && countdown == -1);
	assert(g_caution_calls == 1); // mode 1 suppresses the warning
}

void TestRendererDrawSpecialQuad() {
	SpecialQuadStateCache cache;
	std::memset(&cache, 0xA5, sizeof(cache));
	SpecialQuadRenderEnv env = {Flush, SetStage, SetRender, SetShader, Draw, &cache};
	g_stage_writes.clear();
	g_flush = 0;
	Renderer_DrawSpecialQuad(&env);
	assert(g_flush == 1);
	assert(g_stage_writes.size() == 8);
	const StageWrite expected[8] = {
	    {2, 4, 0}, {2, 1, 0}, {0, 5, 0}, {0, 2, 0},
	    {0, 4, 4}, {0, 1, 4}, {0, 5, 2}, {0, 2, 2},
	};
	for (unsigned i = 0; i < 8; ++i) {
		assert(g_stage_writes[i].stage == expected[i].stage);
		assert(g_stage_writes[i].state == expected[i].state);
		assert(g_stage_writes[i].value == expected[i].value);
	}
	assert(g_render_state == 0x14 && g_render_value == 6);
	assert(g_shader == 0x44);
	assert(g_primitive == 5 && g_primitive_count == 2 && g_stride == 0x14);
	assert(cache.alpha_ref == 0xFF && cache.stage == 3);
	assert(cache.color_op == 0xFF && cache.alpha_op == 0xFF);
	assert(cache.texture == 0 && cache.dirty == 0);
}

} // namespace

int main() {
	TestOrientedRectIntersectsCircle();
	TestTriggerRegionClassify();
	TestRendererDrawSpecialQuad();
	TestSpellTimeoutTransition();
	std::puts("BATCH13_TESTS_PASS");
	return 0;
}
