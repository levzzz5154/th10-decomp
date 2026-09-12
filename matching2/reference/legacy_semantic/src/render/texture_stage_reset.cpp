#include "th10/render/texture_stage_reset.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x0043BFA0 - forces the texture stages through a known state: collapses
// them for a dummy quad draw, resets the cached state bytes, then restores
// the standard modulate configuration.
void Renderer_InitTextureStages(StageResetCache* cache,
                                StageResetEnv* env) {
	env->flush();
	env->set_stage_state(0, 4, 2);
	env->set_stage_state(0, 1, 2);
	env->set_stage_state(0, 5, 0);
	env->set_stage_state(0, 2, 0);
	env->set_render_state(0x14, 6);
	env->set_fvf(0x44);

	// Retail draws a 2-triangle strip from (stale) stack memory purely to
	// flush the state change through the driver; a zeroed quad keeps the
	// same effect deterministically.
	float vertices[20] = {};
	env->draw_quad(vertices, 0x14);

	cache->cached_b = 0xFF;
	cache->cached_d = 0;
	cache->cached_color = 0;
	cache->cached_a = 0xFF;
	cache->cached_blend = 3;
	cache->cached_c = 0xFF;

	env->set_stage_state(0, 4, 4);
	env->set_stage_state(0, 1, 4);
	env->set_stage_state(0, 5, 2);
	env->set_stage_state(0, 2, 2);
}
