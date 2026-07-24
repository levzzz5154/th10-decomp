#include "th10/render/special_quad.hpp"
#include "th10/platform/font_texture_draw.hpp"

#include <cmath>

#include <cstring>

namespace {
} // namespace

// 0x0043BDA0 - flushes deferred state, installs the texture-stage and device
// state needed by the special two-triangle quad, draws it, updates the retail
// state cache, and restores stage zero's normal color/alpha operations.
void Renderer_DrawSpecialQuad(SpecialQuadRenderEnv* env) {
	env->flush();
	env->set_texture_stage_state(2, 4, 0);
	env->set_texture_stage_state(2, 1, 0);
	env->set_texture_stage_state(0, 5, 0);
	env->set_texture_stage_state(0, 2, 0);
	env->set_render_state(0x14, 6);
	env->set_vertex_shader(0x44);
	const unsigned marker = 6;
	env->draw_primitive_up(5, 2, &marker, 0x14);

	env->cache->alpha_ref = 0xFF;
	env->cache->stage = 3;
	env->cache->color_op = 0xFF;
	env->cache->alpha_op = 0xFF;
	env->cache->texture = 0;
	env->cache->dirty = 0;

	env->set_texture_stage_state(0, 4, 4);
	env->set_texture_stage_state(0, 1, 4);
	env->set_texture_stage_state(0, 5, 2);
	env->set_texture_stage_state(0, 2, 2);
}

// 0x0043C500 - scheduler callback that draws the special quad and remains live.
int Renderer_RunSpecialQuadCallback(void (*draw_special_quad)()) {
	draw_special_quad();
	return 1;
}
