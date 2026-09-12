#pragma once

// Player pickup and score-field collision sweep (retail 0x00428630).
// Retail function 0x00428630 (__thiscall, 1520 bytes).

struct PickupDescriptor {
	short value;             // retail +2
	float width;             // +12
	float height;            // +16
	unsigned char type;      // +29: 2 spawns indicator, 3 keeps animation
	short collected_script;  // +32; transformed script is this + 5
	int (*filter)(void* manager, void* pickup, const float* player_center); // +48
};

struct Pickup {
	int animation_handle;
	float position[2];
	float transition_scale;  // set to 0.1 on ordinary collection
	float velocity_scale;    // multiplied by 0.125
	int state;               // 0 inactive, 2 transformed, other active
	int collected;
	int initialized;
	PickupDescriptor* descriptor;
};

struct PickupCollisionRegion {
	float radius;             // circular mode radius
	float angle;              // zero selects axis-aligned rectangle
	float width;
	float height;
	float center[2];
	int previous_frame;
	int current_frame;
	int interval;
	unsigned int flags;       // bit 0 enabled, bit 1 circular
	int value;
	int accumulated;
	int limit;                // reaching this clears value
};

struct PickupManager {
	int generation_begin;     // retail +0x474
	int generation_end;       // +0x478; equality suppresses the sweep
	void* animation_resource; // retail +0x10
	Pickup pickups[128];
	PickupCollisionRegion regions[32];
};

struct PickupSweepEnv {
	int* score;
	int (*player_hit_test)(); // retail 0x004059F0
	int (*interval_test)(Pickup* pickup, int interval); // 0x00427C70
	void (*stop_animation)(Pickup* pickup,
	                       PickupDescriptor* descriptor); // 0x0040C480
	int (*read_animation_field)(int handle); // animation record dword 11
	void (*retire_animation)(Pickup* pickup); // 0x00449630
	int (*create_animation)(void* resource, int script, int layer); // 0x00448D00
	void (*write_animation_field)(int handle, int value);
	void (*or_animation_flags)(int handle, unsigned int flags); // record +0x35c
	void (*spawn_indicator)(short value, PickupManager* manager,
	                       const float* position, float size, float speed,
	                       int style, int count); // 0x00427B50
};

// 0x00428630 - Collect overlapping pickup slots, evaluate 32 score regions,
// add the player hit-test contribution, update score, and return raw value.
// optional_result is reset to zero when non-null, matching the hidden ECX use.
int Player_CollectAndScoreFields(int* optional_result, PickupManager* manager,
                                 const float player_center[2],
                                 const float player_size[2],
                                 const PickupSweepEnv* env);
