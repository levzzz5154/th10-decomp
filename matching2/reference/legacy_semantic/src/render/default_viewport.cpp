#include "th10/render/default_viewport.hpp"
#include "th10/game/registered_clock.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x0043C1A0 - device reset callback that flushes the draw queue, applies
// the default 640x480 viewport, and resets the text draw state.
int Renderer_ApplyDefaultViewport(ViewportEnv* env) {
	env->flush_draw_queue();
	env->viewport_slot[0] = 0;
	env->viewport_slot[1] = 0;
	env->viewport_slot[2] = 0x280;
	env->viewport_slot[3] = 0x1E0;
	env->set_viewport(env->device, env->viewport_slot);
	env->reset_text_state();
	return 1;
}
