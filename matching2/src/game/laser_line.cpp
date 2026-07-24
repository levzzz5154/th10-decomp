#include "th10/game/laser_line.hpp"

// 0x0041D3D0 - line-laser per-frame update (vtable off_46DA60 slot +0x08).
// Runs the embedded command stream, dispatches the flag-selected motion
// modifiers through the resolved virtual slots, grows the beam toward its
// limit and then walks the tail forward, retires the laser when it is fully
// consumed or entirely off-screen, tests the player for hits and grazes,
// and finally rescales and ticks the two embedded animation VMs.
int LaserLine_Update(LineLaser* laser, LineLaserEnv* env) {
	env->run_commands(laser);

	// Retail loads the flag word once for the outer test but re-reads it
	// before every bit test, because the slots (notably the bounce at
	// vtbl+0x3C) rewrite it.
	if (laser->flags != 0) {
		if ((laser->flags & 0x00000001u) != 0)
			env->on_flag_0001(laser);
		if ((laser->flags & 0x00000010u) != 0)
			env->on_flag_0010(laser);
		if ((laser->flags & 0x00000020u) != 0)
			env->on_flag_0020(laser);
		if ((laser->flags & 0x00000040u) != 0)
			env->on_flag_0040(laser);
		if ((laser->flags & 0x00000100u) != 0)
			env->on_flag_0100(laser);
		if ((laser->flags & 0x00000080u) != 0)
			env->on_flag_0080(laser);
		if ((laser->flags & 0x08000C00u) != 0)
			env->on_flag_bounce(laser);
		if ((laser->flags & 0x00100000u) != 0)
			env->on_flag_100000(laser);
		if ((laser->flags & 0x00200000u) != 0)
			env->on_flag_200000(laser);
		if ((laser->flags & 0x04000000u) != 0)
			env->on_flag_4000000(laser);
		if ((laser->flags & 0x00008000u) != 0) {
			if (laser->flash_timer.current > 0)
				env->advance_timer(&laser->flash_timer, -1.0f);
			else
				laser->flags ^= 0x00008000u;
		}
	}

	if (laser->length_limit <= laser->length) {
		// Fully extended: the whole beam moves and the tail consumes the
		// emitted length.
		laser->traveled += env->frame_speed * laser->grow_speed;
		laser->position.x += env->frame_speed * laser->velocity.x;
		laser->position.y += env->frame_speed * laser->velocity.y;
		laser->position.z += env->frame_speed * laser->velocity.z;
		if (0.0f < laser->total_length &&
		    laser->total_length < laser->traveled + laser->length) {
			laser->length = laser->total_length - laser->traveled;
			laser->length_limit = laser->total_length - laser->traveled;
			if (laser->length <= 0.0f)
				return 1;
		}
	} else {
		// Still growing from the origin toward the emission limit.
		laser->length += env->frame_speed * laser->grow_speed;
		if (laser->length_limit < laser->length)
			laser->length = laser->length_limit;
	}

	if (laser->hold_timer.current > 0) {
		// Cull grace: count the hold timer down instead of testing the
		// viewport.
		env->advance_timer(&laser->hold_timer, -1.0f);
	} else {
		// Retire the laser when both the tail and the head are entirely
		// off-screen. Retail leaves the head z as untouched stack garbage;
		// the viewport test only reads x/y, so zero-seeding it here is
		// observationally identical.
		float head[3];
		head[2] = 0.0f;
		env->set_polar(head, laser->angle, laser->length);
		head[0] += laser->position.x;
		head[1] += laser->position.y;
		head[2] += laser->position.z;
		if (env->outside_viewport(&laser->position.x, laser->width,
		                          laser->width) != 0 &&
		    env->outside_viewport(head, laser->width, laser->width) != 0)
			return 1;
	}

	if (laser->length > 16.0f && laser->width > 3.0f) {
		// Probe a point 10% along the beam and classify it against the
		// player region.
		float probe[3];
		probe[2] = 0.0f;
		env->set_polar(probe, laser->angle, laser->length * 0.1f);
		probe[0] += laser->position.x;
		probe[1] += laser->position.y;
		probe[2] += laser->position.z;
		float half_width;
		if (laser->width >= 32.0f)
			half_width = laser->width - (laser->width + 16.0f) * 0.5f;
		else
			half_width = laser->width * 0.5f;
		int result = env->classify_player(probe, env->player, laser->angle,
		                                  half_width, laser->length * 0.8f);
		if (result == 1) {
			const float box[3] = {32.0f, 32.0f, 0.0f};
			env->hit_player(laser, env->player_state, box, 0);
		} else if (result == 2 && laser->age.current % 5 == 0) {
			env->register_graze(env->player_state, &half_width);
			env->play_graze_sound(28, laser->position.x);
		}
	}

	// Rescale the body sprite to the current width/length and run the two
	// embedded VMs; the head VM only runs until the tail starts moving.
	LineLaserVm* body = env->body_vm;
	body->flags |= 0x8u;
	body->growth_x = laser->width / body->sprite->height;
	body->flags |= 0x8u;
	body->growth_y = laser->length / body->sprite->width;
	env->tick_vm(body);
	if (laser->traveled == 0.0f)
		env->tick_vm(env->head_vm);
	return 0;
}

// 0x0041F400 - laser cancel sweep (vtable off_46DA60 slot +0x14). Walks the
// beam in 12-unit steps starting 6 units past the tail, converts each
// on-screen step into a sparkle VM (script 17 + 2*colour, screen-space
// position x+224/y+16), optionally drops item kind 8 falling straight down,
// and finally retires the laser. Retail also advances the step z by an
// uninitialized stack float (Hex-Rays "v3 possibly undefined"); the readable
// form advances z by zero, which only affects the garbage depth already
// noted in the raw body.
int LaserLine_SweepIntoItems(LineLaser* laser, int spawn_items,
                             LaserSweepEnv* env) {
	int count = 0;
	float distance = 6.0f;
	float step[2];
	env->set_polar(step, laser->angle, 6.0f);
	float x = step[0] + laser->position.x;
	float y = step[1] + laser->position.y;
	float z = laser->position.z;
	step[0] += step[0];
	step[1] += step[1];
	if (laser->length <= 12.0f) {
		laser->retired = 1;
		return 0;
	}
	do {
		++count;
		if (x + 16.0f > -192.0f && x - 16.0f < 192.0f && y + 16.0f > 0.0f &&
		    y - 16.0f < 448.0f) {
			int script_id = 2 * laser->colour + 17;
			LaserSweepVm* vm = env->allocate_vm(env->anm_manager);
			vm->flags |= 0x40000000u;
			vm->pending_word = 0;
			vm->position[0] = x + 224.0f;
			vm->position[1] = y + 16.0f;
			vm->position[2] = z;
			env->load_script(vm, env->anm_file, script_id);
			env->register_vm(vm, env->anm_manager);
			if (spawn_items != 0 && x + 32.0f > -192.0f &&
			    x - 32.0f < 192.0f && y + 32.0f > 0.0f && y - 32.0f < 448.0f) {
				float point[2] = {x, y};
				env->spawn_item(env->item_manager, point, 8, -1,
				                -1.5707964f, 0.6f);
			}
		}
		x += step[0];
		y += step[1];
		distance += 12.0f;
	} while (distance + 6.0f < laser->length);
	laser->retired = 1;
	return count;
}
