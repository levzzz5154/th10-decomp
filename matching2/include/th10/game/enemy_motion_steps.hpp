#pragma once

// Enemy motion steps: accel, homing, ease, bounce, and homing relaunch (retail batches 9-11).
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

struct AccelEnemy {
	float velocity[3];        // +0x3c0
	float speed;              // +0x3d8
	float angle;              // +0x3e4
	Word* status_flags; // +0x43c, bit 0x10 cleared when finished
	FrameClock clock;   // +0x648
	float speed_accel;        // +0x65c
	float accel[3];           // +0x664
	int duration;             // +0x670
};

void Enemy_AccelStep(AccelEnemy* enemy, float frame_scale,
                     float min_component, const ClockEnv* clock_env);

struct HomingEnemy {
	float position[2];        // +0x3b4
	float velocity[3];        // +0x3c0
	float speed;              // +0x3d8
	float angle;              // +0x3e4
	Word* status_flags; // +0x43c, bit 0x04000000 cleared when finished
	FrameClock clock;   // +0x7b4
	float turn_rate;          // +0x7c8
	float turn_limit;         // +0x7cc
	int duration;             // +0x7dc
};

struct HomingEnv {
	const float* target_position;
	float (*wrap_turn)(float reference, float amount);
	float (*limit_turn)(float turn, float angle);
	void (*set_velocity)(float* velocity, float angle, float speed);
	float frame_scale;
	ClockEnv clock_env;
};

void Enemy_HomingStep(HomingEnemy* enemy, HomingEnv* env);

struct EaseEnemy {
	float velocity[3];           // +0x3c0
	float speed;                 // +0x3d8
	float angle;                 // +0x3e4
	Word* status_flags;    // +0x43c
	int ambient_sound;           // +0x458, >= 0 keeps an ambient loop alive
	RegisteredClock clock; // +0x6b0
	float final_speed;           // +0x6c4
	float final_angle;           // +0x6c8
	int duration;                // +0x6d8
	int repeat_limit;            // +0x6dc
	int repeat_count;            // +0x6e0
};

struct EaseEnv {
	void (*stop_ambient_sound)(void* channel, int argument);
	void* ambient_channel;
	void (*set_velocity)(float* velocity, float angle, float speed);
	float* frame_scale;
	ClockEnv clock_env;
};

void Enemy_EaseStopStep(EaseEnemy* enemy, EaseEnv* env);

void Enemy_EaseTurnStep(EaseEnemy* enemy, EaseEnv* env);

struct BounceEnemy {
	float x;
	float y;
	float velocity[3];
	float speed;
	float angle;
	Word flags; // bits 0x8000000/0x400 gate vertical bounce
	int sound_id;
	float floor_speed;
	int bounce_count;
	int bounce_limit;
};

struct BounceEnv {
	float min_x;
	float max_x;
	float min_y;
	float max_y;
	float reflect_low;  // 2 * min_x
	float reflect_high; // 2 * max_x
	float speed_floor;
	float pi;
	void (*play_sound)(void* sound_manager, int id);
	void* sound_manager;
	float (*normalize_angle)(float angle, float reference);
	void (*set_velocity)(float* velocity, float angle, float speed);
};

void Enemy_BounceStep(BounceEnemy* enemy, BounceEnv* env);

// Enemy mode bit at +0x43C: the homing-relaunch behavior stays armed until
// the relaunch counter reaches its limit.
constexpr Word kEnemyModeRelaunchArmed = 0x80;

// Retail fallback aim used when an enemy sits exactly on the player.
constexpr float kRelaunchHalfPi = 1.5707964f;

struct RelaunchEnemy {
	float pos_x;             // retail +0x3B4
	float pos_y;             // retail +0x3B8
	float velocity[3];       // retail +0x3C0 (updated through set_velocity)
	float speed;             // retail +0x3D8
	float angle;             // retail +0x3E4
	Word mode_flags;  // retail +0x43C; see kEnemyModeRelaunchArmed
	int sound_gate;          // retail +0x458; >= 0 plays the relaunch sound
	RegisteredClock clock; // retail +0x6B0..+0x6C0
	float relaunch_speed;    // retail +0x6C4
	float angle_offset;      // retail +0x6C8
	int duration;            // retail +0x6D8
	int relaunch_limit;      // retail +0x6DC
	int relaunch_count;      // retail +0x6E0
};

struct RelaunchEnv {
	ClockEnv clock_env;
	const float* player_pos; // retail DAT_00477834 +0x3C0 (x, y)
	float* frame_scale;      // retail &DAT_00476f78
	void (*play_sound)(void* sound_state, int id); // retail 0x0043DC90
	void* sound_state;       // retail &DAT_00492590
	float (*normalize_sum)(float angle, float delta); // retail 0x0044BC10
	void (*set_velocity)(float* velocity, float angle, float speed); // 0x00408750
};

void Enemy_HomingRelaunchStep(RelaunchEnemy* enemy, RelaunchEnv* env);
