#include "th10/game/projectile_bounce.hpp"
#include "th10/game/trigger_activation.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {

std::vector<int> g_scripts;
int g_sound_calls;
unsigned short g_animation;
void Spawn(int script, TriggerActivation*) { g_scripts.push_back(script); }
void PlaySound(int id) { assert(id == 0); ++g_sound_calls; }
void SetAnimation(unsigned short handle) { g_animation = handle; }

void TestTriggerRegionActivate() {
	float frame_scale = 1.0f;
	TriggerActivation trigger;
	std::memset(&trigger, 0, sizeof(trigger));
	trigger.animation_handle = 77;
	unsigned int flags[8];
	unsigned int* flag_ptrs[8];
	for (int i = 0; i < 8; ++i) {
		flags[i] = 3u;
		flag_ptrs[i] = &flags[i];
	}
	int latch = 9;
	TriggerActivationEnv env;
	std::memset(&env, 0, sizeof(env));
	env.frame_scale = &frame_scale;
	env.spawn_effect = Spawn;
	env.play_sound = PlaySound;
	env.set_animation = SetAnimation;
	env.stage_counter = 60;
	for (int i = 0; i < 8; ++i) env.stage_flags[i] = flag_ptrs[i];
	env.stage_latch = &latch;

	g_scripts.clear();
	g_sound_calls = 0;
	g_animation = 0;
	TriggerRegion_Activate(&trigger, &env);
	assert(trigger.mode == 4);
	assert(g_scripts.size() == 33 && g_scripts[0] == 0x162);
	for (std::size_t i = 1; i < g_scripts.size(); ++i)
		assert(g_scripts[i] == 0x163);
	assert(g_sound_calls == 1 && g_animation == 77);
	assert(trigger.activation_clock.previous == -1);
	assert(trigger.activation_clock.frame == 0);
	assert(trigger.activation_clock.timer == 0.0f);
	assert(trigger.activation_clock.control == &frame_scale);
	assert((trigger.activation_clock.flags & 1u) != 0);
	assert(trigger.cooldown_clock.previous == 5);
	assert(trigger.cooldown_clock.frame == 6);
	assert(trigger.cooldown_clock.timer == 6.0f);
	assert(latch == 0);
	for (int i = 0; i < 8; ++i) assert(flags[i] == 1u);

	// Sound and late-stage clearing are independently gated.
	env.sound_suppressed = true;
	env.stage_counter = 59;
	latch = 7;
	for (int i = 0; i < 8; ++i) flags[i] = 3u;
	TriggerRegion_Activate(&trigger, &env);
	assert(g_sound_calls == 1 && latch == 7);
	for (int i = 0; i < 8; ++i) assert(flags[i] == 3u);
}

float g_dx, g_dy;
int g_emits;
std::vector<float> g_angles;
void Project(float, float, float* dx, float* dy) { *dx = g_dx; *dy = g_dy; }
float Normalize(float angle) { return angle + 100.0f; }
void Emit(Projectile* projectile) {
	++g_emits;
	g_angles.push_back(projectile->emitted_angle);
}

ProjectileBounceEnv MakeBounceEnv() {
	ProjectileBounceEnv env = {-10.0f, 10.0f, -5.0f, 5.0f, 3.0f,
	                        Project, Normalize, PlaySound, Emit};
	return env;
}

void TestProjectileBounceAtBounds() {
	ProjectileBounceEnv env = MakeBounceEnv();
	Projectile projectile;
	std::memset(&projectile, 0, sizeof(projectile));
	projectile.heading = 1.0f;
	projectile.speed = 2.0f;
	projectile.sound_gate = 0;
	projectile.flags = 0x08000C03u;
	projectile.color = 0x12345678u;

	// In bounds: no sound, no emitted projectile, no flag changes.
	g_dx = 1.0f; g_dy = 1.0f;
	g_sound_calls = g_emits = 0;
	g_angles.clear();
	Projectile_BounceAtBounds(&projectile, &env);
	assert(g_sound_calls == 0 && g_emits == 0);
	assert(projectile.flags == 0x08000C03u);

	// Horizontal crossing reflects through normalize(-heading-bias).
	g_dx = 11.0f; g_dy = 0.0f;
	Projectile_BounceAtBounds(&projectile, &env);
	assert(g_sound_calls == 1 && g_emits == 1);
	assert(g_angles[0] == 96.0f);
	assert(projectile.emitted_position.x == 11.0f);
	assert(projectile.emitted_color == 0x12345678u);
	assert(projectile.flags == 3u);

	// Top crossing uses -heading directly.
	projectile.flags = 3u;
	g_dx = 0.0f; g_dy = -6.0f;
	Projectile_BounceAtBounds(&projectile, &env);
	assert(g_emits == 2 && g_angles[1] == -1.0f);
	assert(projectile.flags == 3u);

	// Bit 0x08000000 suppresses vertical reflection, but sound still plays.
	projectile.flags = 0x08000003u;
	g_dx = 0.0f; g_dy = -6.0f;
	int sounds_before = g_sound_calls;
	Projectile_BounceAtBounds(&projectile, &env);
	assert(g_emits == 2 && g_sound_calls == sounds_before + 1);
}

} // namespace

int main() {
	TestTriggerRegionActivate();
	TestProjectileBounceAtBounds();
	std::puts("BATCH14_TESTS_PASS");
	return 0;
}
