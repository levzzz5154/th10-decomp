#pragma once

// ANM blend/color/wrap state application (retail 0x004423E0).
#include "th10/util/scalars.hpp"

struct AnmStateCache {
	Byte cached_blend;
	Byte cached_wrap;
	Word cached_color;
	int fade_enabled;
	Byte fade[4]; // blue, green, red, alpha scale bytes
	int state_changes;
};

struct AnmBlendVmState {
	Word flags; // bits 4-5 blend, bit 15 color select, bit 31 wrap
	Word color_primary;
	Word color_secondary;
};

struct AnmStateEnv {
	void (*flush)(void);
	void (*set_blend_mode)(Word value);
	void (*set_texture_factor)(Word color);
	void (*set_address_mode)(Word value);
};

void AnmManager_ApplyBlendColorWrap(AnmStateCache* cache,
                                    const AnmBlendVmState* vm,
                                    AnmStateEnv* env);
