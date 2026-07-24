#include "th10/game/result_screen_effects.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x0041FDD0 - lazily creates the result-screen interface effect on stage 1
// and resolves the cached sprite handle, then counts frames. Returns 1.
int ResultScreen_LazyCreateEffects(ResultLazyHost* host,
                                   ResultLazyEnv* env) {
	if (host->stage_a == 1) {
		ResultEffectVm* vm = env->acquire_effect();
		vm->layer = 0xF;
		vm->flags |= 0x40000000u;
		env->assign_script(vm, 0);
		env->register_front(env->manager);
		host->owner_slot = host;
		host->stage_a += 1;
	}
	if (host->stage_b == 1) {
		if (*env->cached_sprite_slot == 0) {
			*env->cached_sprite_slot = *env->clone_sprite(env->sprite_source);
		}
		host->stage_b += 1;
	}
	host->frame += 1;
	return 1;
}
