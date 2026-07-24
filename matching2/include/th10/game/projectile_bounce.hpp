#pragma once

// Projectile edge-crossing reflection step (retail 0x0041CFD0).
// --- 0x0041CFD0: projectile boundary bounce --------------------------------
struct ProjectileVec3 { float x, y, z; };

struct Projectile {
	ProjectileVec3 position;
	float heading;
	float speed;
	int sound_gate;
	unsigned int flags;
	unsigned int color;
	ProjectileVec3 emitted_position;
	float emitted_angle;
	unsigned int emitted_color;
};

struct ProjectileBounceEnv {
	float left;
	float right;
	float top;
	float bottom;
	float horizontal_angle_bias;
	void (*project_step)(float heading, float speed,
	                     float* delta_x, float* delta_y);
	float (*normalize_angle)(float angle);
	void (*play_sound)(int id);
	void (*emit_bounce)(Projectile* projectile);
};

void Projectile_BounceAtBounds(Projectile* projectile,
                               ProjectileBounceEnv* env);
