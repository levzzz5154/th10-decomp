#pragma once

#include <cstddef>

// Special two-triangle quad draw and scheduler callback (retail 0x0043BDA0, 0x0043C500).
// --- 0x0043BDA0: special quad renderer-state setup --------------------------
struct SpecialQuadStateCache {
	unsigned char alpha_ref;
	unsigned char stage;
	unsigned char color_op;
	unsigned char alpha_op;
	unsigned int texture;
	unsigned int dirty;
};

struct SpecialQuadRenderEnv {
	void (*flush)();
	void (*set_texture_stage_state)(unsigned stage, unsigned state,
	                                unsigned value);
	void (*set_render_state)(unsigned state, unsigned value);
	void (*set_vertex_shader)(unsigned shader);
	void (*draw_primitive_up)(unsigned primitive, unsigned primitive_count,
	                          const void* vertices, unsigned stride);
	SpecialQuadStateCache* cache;
};

void Renderer_DrawSpecialQuad(SpecialQuadRenderEnv* env);

// --- 0x0043C500: per-frame special-quad callback ----------------------------
int Renderer_RunSpecialQuadCallback(void (*draw_special_quad)());
