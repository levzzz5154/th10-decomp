#include "th10/game/result_overlay.hpp"

namespace {
void Replace(int* slot, void* resource, int script,
             const ResultOverlayEnv* env) {
	env->retire(*slot);
	*slot = 0;
	*slot = env->create_animation(resource, script, 15);
}
} // namespace

// 0x004172E0 - result-overlay mode constructor and eight-digit display.
void ResultOverlay_SetMode(ResultOverlayState* state, int mode, int number,
                           const ResultOverlayEnv* env) {
	switch (mode) {
	case 0: {
		Replace(&state->main_handle, state->resource, 71, env);
		bool leading_digit_seen = false;
		int divisor = 10000000;
		for (int i = 0; i < 8; ++i) {
			env->retire(state->digit_handles[i]);
			state->digit_handles[i] = 0;
			ResultDigitVm* vm = env->allocate_digit_vm();
			vm->layer = 15;
			vm->flags |= 0x40000000u;
			env->assign_script(state->resource, vm, 39 + i);
			state->digit_handles[i] = env->register_vm(vm);
			const int digit = number / divisor;
			number %= divisor;
			if (digit != 0)
				leading_digit_seen = true;
			env->configure_digit(state->digit_handles[i], digit + 8);
			if (leading_digit_seen)
				env->show(&state->digit_handles[i]);
			else
				env->hide(&state->digit_handles[i]);
			divisor /= 10;
		}
		break;
	}
	case 1:
		Replace(&state->main_handle, state->resource, 72, env);
		break;
	case 2:
	case 3:
	case 4:
		Replace(&state->secondary_handle, state->resource, 71 + mode, env);
		break;
	case 6:
		Replace(&state->main_handle, state->resource, 76, env);
		break;
	default:
		break;
	}
}
