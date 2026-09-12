#include "th10/game/stage_controller_tick.hpp"

#include <cstdio>

// 0x00426360 - updates the controller's projected position, applies the shared
// camera transform, invokes four optional stage callbacks, and conditionally
// emits the paired spell-background effects. Dormant mode 2 skips the body.
int StageController_Tick(StageController* controller,
                         StageControllerEnv* env) {
	if (controller->mode == 2) {
		return 1;
	}

	controller->projected.x = controller->position.x + env->projected_x_bias;
	controller->projected.y = controller->position.y + env->projected_y_bias;
	controller->projected.z = controller->position.z;
	env->apply_camera(controller);

	for (int index = 0; index < 4; ++index) {
		if (controller->callbacks[index] != 0) {
			controller->callbacks[index](controller->callback_contexts[index]);
		}
	}

	if (env->effects_enabled) {
		env->spawn_effect(controller->position.x + env->effect_x_bias);
		env->spawn_effect(controller->position.y + env->effect_y_bias);
		env->flush_effects();
		env->flush_effects();
	}
	return 1;
}
