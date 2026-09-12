#pragma once

// Texture stage state initialization (retail 0x0043BFA0).
#include "th10/util/scalars.hpp"

struct StageResetCache {
	Word cached_color;
	Byte cached_blend;   // reset to 3
	Byte cached_a;       // reset to 0xff
	Byte cached_b;       // reset to 0xff
	Byte cached_c;       // reset to 0xff
	int cached_d;               // reset to 0
};

struct StageResetEnv {
	void (*flush)(void);
	void (*set_stage_state)(Word stage, Word type,
	                        Word value);
	void (*set_render_state)(Word state, Word value);
	void (*set_fvf)(Word fvf);
	void (*draw_quad)(const void* vertices, Word stride);
};

void Renderer_InitTextureStages(StageResetCache* cache,
                                StageResetEnv* env);
