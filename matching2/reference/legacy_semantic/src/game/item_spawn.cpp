#include "th10/game/item_spawn.hpp"

namespace {
void ResetTimer(Item* item, const ItemSpawnEnv* env) {
	item->motion_state = 0;
	if ((item->timer.flags & 1u) == 0) {
		item->timer.current = 0;
		item->timer.target = -999999;
		item->timer.previous = 0;
		item->timer.speed = env->frame_scale;
		item->timer.flags |= 1u;
	}
	item->timer.current = 0;
	item->timer.previous = 0;
	item->timer.target = -1;
}
void InitializeMotion(Item* item, const float position[3],
                      float angle, float speed, const ItemSpawnEnv* env) {
	item->position[0] = position[0];
	item->position[1] = position[1];
	item->position[2] = position[2];
	env->set_velocity(item->velocity, angle, speed);
	ResetTimer(item, env);
}
} // namespace

// 0x0041BB00 - item spawn allocator and kind remapping.
int ItemManager_Spawn(ItemManager* manager, const float position[3],
                      int kind, int identifier, float angle, float speed,
                      const ItemSpawnEnv* env) {
	if (kind == 8) {
		const int cursor = manager->special_cursor;
		Item& item = manager->special[cursor];
		++manager->special_count;
		if (item.state == 0) {
			int variant;
			if (manager->special_count < 256)
				variant = cursor % 4;
			else if (manager->special_count < 512)
				variant = cursor % 8 + 4;
			else if (manager->special_count < 1024)
				variant = cursor % 16 + 8;
			else
				variant = cursor % 32 + 16;
			item.variant = variant;
			item.kind = 8;
			item.display_kind = 8;
			item.state = 5;
			InitializeMotion(&item, position, angle, speed, env);
		}
		manager->special_cursor = (cursor + 1) % 2048;
		return 0;
	}

	Item* item = 0;
	for (int i = 0; i < 150; ++i) {
		if (manager->normal[i].state == 0) {
			item = &manager->normal[i];
			break;
		}
	}
	if (!item)
		return 0;
	item->state = 1;
	InitializeMotion(item, position, angle, speed, env);
	if (item->position[0] <= -192.0f)
		item->position[0] = -192.0f;
	else if (item->position[0] >= 192.0f)
		item->position[0] = 192.0f;

	int mapped_kind = kind;
	if (env->bomb_fragments >= 100) {
		if (kind == 1 || kind == 4)
			mapped_kind = 9;
		else if (kind == 10 || kind == 11)
			mapped_kind = 5;
	}
	if (item->kind == 3)
		env->retire_kind3_effect(item, 393);
	item->kind = mapped_kind;
	item->display_kind = mapped_kind;
	int script;
	if (mapped_kind == 10) {
		item->display_kind = 1;
		script = 375;
	} else if (mapped_kind == 11) {
		item->display_kind = 4;
		script = 378;
	} else {
		script = mapped_kind + 374;
	}
	env->load_animation(item, script);
	item->identifier = identifier;
	return 0;
}
