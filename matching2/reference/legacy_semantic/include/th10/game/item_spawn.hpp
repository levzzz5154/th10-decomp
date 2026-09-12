#pragma once

// Item spawn allocator with kind remapping (retail 0x0041BB00).
// Retail function 0x0041BB00 (__userpurge, 896 bytes).

struct ItemTimer {
	int target;
	int current;
	int previous;
	const float* speed;
	unsigned int flags;
};
struct Item {
	float position[3];
	float velocity[2];
	int motion_state;
	ItemTimer timer;
	int identifier;
	int state;
	int kind;
	int display_kind;
	int variant;
};
struct ItemManager {
	Item normal[150];
	Item special[2048];
	int special_cursor;
	int special_count;
};
struct ItemSpawnEnv {
	short bomb_fragments;
	const float* frame_scale;
	void (*set_velocity)(float velocity[2], float angle, float speed);
	void (*retire_kind3_effect)(Item* item, int effect_id);
	void (*load_animation)(Item* item, int script);
};

// 0x0041BB00 - Spawn an item. Kind 8 uses the 2048-slot ring and density
// variants; other kinds allocate the first free normal slot, clamp x to
// [-192,192], apply bomb-fragment remapping, and load the kind animation.
// Returns zero exactly as retail; a full pool silently drops the request.
int ItemManager_Spawn(ItemManager* manager, const float position[3],
                      int kind, int identifier, float angle, float speed,
                      const ItemSpawnEnv* env);
