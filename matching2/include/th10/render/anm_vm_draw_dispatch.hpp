#pragma once

// ANM VM draw-mode dispatch with anchored/rotated quads (retail 0x004451C0).
#include "th10/util/scalars.hpp"

struct AnmDrawVm {
	float rotation;     // +0x2c
	float scale_x;      // +0x3c
	float scale_y;      // +0x40
	float size_x;       // +0x4c
	float size_y;       // +0x50
	Byte visible; // +0x2ff
	Word flags;   // +0x35c
	float origin_x;     // sum of the three position triples
	float origin_y;
	float origin_z;
};

struct AnmQuad {
	float corners[4][3];
};

struct AnmDrawEnv {
	int (*draw_standard)(void* context);
	int (*draw_unrotated)(void* context);
	int (*draw_corner_quad)(void* context, int layer);
	int (*draw_mode4)(void* context);
	int (*draw_mode5)(void* context);
	int (*draw_mode6)(void* context);
	int (*draw_mode7)(void* context, AnmDrawVm* vm);
	int (*draw_mode8)(void* context);
	int (*draw_mode9)(void* context);
	AnmQuad* quad; // global rotated-corner vertex buffer
	float anchor_low;    // centered anchoring near-edge factor (-0.5)
	float anchor_high;   // centered anchoring far-edge factor (+0.5)
};

int AnmVm_DrawDispatch(AnmDrawVm* vm, void* context, AnmDrawEnv* env);
