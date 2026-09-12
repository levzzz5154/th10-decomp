#pragma once

// ANM blend/color/wrap state application (retail 0x004423E0).
#include "th10/util/scalars.hpp"

struct AnmStateCache {
	Byte cached_blend;      // retail manager+0x3ADA68
	Byte cached_filter;     // retail manager+0x3ADA6E
	Word cached_color;
	int fade_enabled;
	Byte fade[4]; // blue, green, red, alpha scale bytes
	int state_changes;
};

struct AnmBlendVmState {
	Word flags; // bits 4-5 blend, bit 15 color select, bit 31 texture filter
	Word color_primary;
	Word color_secondary;
};

struct AnmStateEnv {
	void (*flush)(void);
	void (*set_blend_mode)(Word value);
	void (*set_texture_factor)(Word color);
	// Retail 0x004423E0 loc_442571/loc_442580 issues SetSamplerState (device
	// vtable +0x114) twice, for D3DSAMP_MAGFILTER (5) and D3DSAMP_MINFILTER
	// (6), with 1 (D3DTEXF_POINT) or 2 (D3DTEXF_LINEAR). It is a texture
	// filter selector, not an address mode.
	void (*set_texture_filter)(Word value);
};

void AnmManager_ApplyBlendColorWrap(AnmStateCache* cache,
                                    const AnmBlendVmState* vm,
                                    AnmStateEnv* env);
