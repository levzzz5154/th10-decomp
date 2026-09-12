#pragma once

// 128-slot effect pool per-frame update (retail 0x00428280).
#include "th10/game/laser_line.hpp"

// ---------------------------------------------------------------------------
// 0x00428280 - effect-pool per-frame update
// ---------------------------------------------------------------------------
// Iterates the 128 effect slots (stride 0x5C, base manager+0x49C). Sound-
// driven kinds (record kind 3) release their animation scripts when the
// channel budget is exhausted (manager+0x464 < 0 or record index-1 >=
// manager+0x3500), when the pause menu opens (DAT_0047770C+0x9EB8), or when
// the game owner is gone (DAT_00477704 == 0). Active slots run their type
// callback, advance polar/linear motion, publish screen-space positions to
// the main and companion animation objects, cull established non-sound
// effects once off-screen, and advance the slot frame timer.

struct EffectPoolSlot;

// Effect-type record at slot+0x58.
struct EffectPoolRecord {
	signed char index; // +0x1C (per-type sound slot index)
	char kind;         // +0x1D (3 = sound-driven ambient effect)
	void (*tick)(void* manager, EffectPoolSlot* slot); // +0x28 (optional)
};

// Pool slot; retail stride 0x5C starting at manager+0x49C.
struct EffectPoolSlot {
	int previous_frame;       // +0x00
	int frame;                // +0x04
	float frame_elapsed;      // +0x08
	const float* game_speed;  // +0x0C (&DAT_00476F78)
	unsigned int timer_flags; // +0x10 (untouched here)
	float position[3];        // +0x14 (motion record base for 0x0044C2A0)
	float velocity[3];        // +0x20 (rebuilt from angle/rate in linear mode)
	float rate;               // +0x2C (linear speed / polar angular velocity)
	float angle;              // +0x30
	float radius;             // +0x34 (polar mode)
	float radius_step;        // +0x38
	unsigned int motion_flags; // +0x3C (bit0 = polar accumulate mode)
	int state;                // +0x40 (0 free, 1 active, 2 sound released)
	int handle1;              // +0x44 (main animation handle)
	int handle2;              // +0x48 (companion animation handle)
	int field_4C;             // +0x4C (untouched here)
	int suppress;             // +0x50 (cleared every frame)
	int stop_request;         // +0x54 (1 = stop the main script at frame 3)
	const EffectPoolRecord* record; // +0x58
};

struct EffectPoolVm;

struct EffectPoolVmNode {
	EffectPoolVm* vm;
	EffectPoolVmNode* next;
};

// Slice of the world animation object this update touches.
struct EffectPoolVm {
	EffectPoolVmNode* children; // +0x14
	int child_membership;          // +0x18 (propagate flags when 0)
	float angle;                   // +0x2C (receives the slot angle)
	float growth_x;                // +0x3C
	float growth_y;                // +0x40
	float position[3];             // +0x340 (screen space)
	unsigned int flags;            // +0x35C
	const LineLaserSprite* sprite; // +0x394
};

struct EffectPoolEnv {
	void* manager;           // raw owner forwarded to record ticks
	int sound_budget;        // manager+0x464 (< 0 releases all sound kinds)
	int sound_channel_limit; // manager+0x3500
	int* sound_slots;        // manager+0x42F4 (indexed by record->index)
	int pause_menu_open;     // DAT_0047770C != 0 && *(DAT_0047770C+0x9EB8)
	int game_inactive;       // DAT_00477704 == 0
	void (*release_handle)(int* handle_slot);       // 0x00409E50
	void (*stop_at_frame3)(const int* handle_slot); // 0x0040C4D0
	void (*set_polar)(float* out, float angle, float radius); // 0x0044C5D0
	float (*wrap_angle)(float angle);               // 0x0044BC70
	void (*advance_motion)(float* record);          // 0x0044C2A0 (&position[0])
	EffectPoolVm* (*find_vm)(int handle);        // 0x004491C0 on DAT_00491C10
	void (*release_root)(int handle);               // 0x004492A0 (root+children)
	int (*outside_viewport)(const float* point, float radius_x,
	                        float radius_y);        // 0x00428D70
};

// Always returns 0.
int EffectPool_Update(EffectPoolSlot* slots /* 128 entries */,
                      EffectPoolEnv* env);
