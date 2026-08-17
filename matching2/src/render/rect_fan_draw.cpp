#include "th10/render/rect_fan_draw.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/util/scalars.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

// Each routine mirrors one retail function; the comment above each body
// names the retail address it was recovered from.


// 0x004450E0 - Draw a rectangle as a triangle fan with the standard blend
// state. Pending geometry is flushed first, blend mode 3 is applied if not
// already active, the world transform is committed, the vertex shader is
// rebound only when the handle changed, texture stage 0xE and two sampler
// states are reset, and the four 0x1C-byte vertices are submitted.
int Renderer_DrawRectFan(int pending_vertices, void (*flush)(void),
                         Byte* blend_state,
                         void (*set_blend_render_state)(void),
                         void (*commit_world)(void), int shader_handle,
                         int* bound_handle,
                         void (*bind_shader)(int stage, int handle),
                         void (*set_texture_stage)(int stage, int value),
                         void (*set_sampler_state)(int stage, int state,
                                                   int value),
                         void (*draw_fan)(int primitive_type,
                                          int primitive_count,
                                          const void* vertices, int stride),
                         const void* vertices, int primitive_count) {
	if (pending_vertices != 0) flush();
	if (*blend_state != 3) {
		set_blend_render_state();
		*blend_state = 3;
	}
	commit_world();
	if (*bound_handle != shader_handle) {
		*bound_handle = shader_handle;
		bind_shader(0, shader_handle);
	}
	flush();
	set_texture_stage(0xE, 0);
	set_sampler_state(0, 6, 0);
	set_sampler_state(0, 3, 0);
	draw_fan(6, primitive_count, vertices, 0x1C);
	return 0;
}
