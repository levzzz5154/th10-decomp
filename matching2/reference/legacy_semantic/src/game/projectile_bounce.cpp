#include "th10/game/projectile_bounce.hpp"
#include "th10/game/trigger_activation.hpp"

namespace {
} // namespace

// 0x0041CFD0 - projects the next projectile position and emits a reflected
// copy when it crosses a configured edge. Horizontal and vertical reflections
// preserve the retail angle formulas and clear the one-shot bounce flag bits.
void Projectile_BounceAtBounds(Projectile* projectile,
                               ProjectileBounceEnv* env) {
	float dx = 0.0f;
	float dy = 0.0f;
	env->project_step(projectile->heading, projectile->speed, &dx, &dy);
	const float x = projectile->position.x + dx;
	const float y = projectile->position.y + dy;
	if (!(x < env->left || env->right <= x || y < env->top ||
	      env->bottom <= y)) {
		return;
	}

	if (projectile->sound_gate >= 0) {
		env->play_sound(0);
	}

	bool emitted = false;
	if (x < env->left || env->right <= x) {
		projectile->emitted_position = {x, y, 0.0f};
		projectile->emitted_angle =
		    env->normalize_angle(-projectile->heading -
		                         env->horizontal_angle_bias);
		projectile->emitted_color = projectile->color;
		env->emit_bounce(projectile);
		emitted = true;
	}

	const bool blocks_vertical = (projectile->flags & 0x08000000u) != 0;
	const bool below_bottom_without_override =
	    env->bottom <= y && (projectile->flags & 0x400u) == 0;
	if (!blocks_vertical && (y < env->top || below_bottom_without_override)) {
		projectile->emitted_position = {x, y, 0.0f};
		projectile->emitted_angle = -projectile->heading;
		projectile->emitted_color = projectile->color;
		env->emit_bounce(projectile);
		emitted = true;
	}

	if (emitted) {
		projectile->flags &= 0xF7FFF3FFu;
	}
}
