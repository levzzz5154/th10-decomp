#include "th10/render/anm_blend_state.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x004423E0 - applies the cached blend mode, texture-factor color (with
// optional fade modulation), and texture filter for the next draw,
// flushing the queued primitives whenever a cached state changes.
void AnmManager_ApplyBlendColorWrap(AnmStateCache* cache,
                                    const AnmBlendVmState* vm,
                                    AnmStateEnv* env) {
	Byte blend = (Byte)((vm->flags >> 4) & 3u);
	if (cache->cached_blend != blend) {
		env->flush();
		cache->cached_blend = blend;
		if (blend == 0) {
			env->set_blend_mode(6);
		} else if (blend == 1 || blend == 2) {
			env->set_blend_mode(2);
		}
		// blend == 3 leaves the device state untouched.
	}

	Word color = ((vm->flags & 0x8000u) != 0) ? vm->color_secondary
	                                                 : vm->color_primary;
	if (cache->fade_enabled != 0) {
		Word blue = color & 0xFFu;
		Word green = (color >> 8) & 0xFFu;
		Word red = (color >> 16) & 0xFFu;
		Word alpha = (color >> 24) & 0xFFu;
		red = (Word)cache->fade[2] * red >> 7;
		if (red > 0xFFu) red = 0xFFu;
		green = (Word)cache->fade[1] * green >> 7;
		if (green > 0xFFu) green = 0xFFu;
		blue = (Word)cache->fade[0] * blue >> 7;
		if (blue > 0xFFu) blue = 0xFFu;
		alpha = (Word)cache->fade[3] * alpha >> 7;
		if (alpha > 0xFFu) alpha = 0xFFu;
		color = (alpha << 24) | (red << 16) | (green << 8) | blue;
	}
	if (cache->cached_color != color) {
		env->flush();
		cache->cached_color = color;
		env->set_texture_factor(color);
	}

	// Retail 0x004423E0: bit 31 of the flag word picks the texture filter.
	// loc_442571 pushes 1 (D3DTEXF_POINT) when the bit is set, loc_442580's
	// fallthrough pushes 2 (D3DTEXF_LINEAR) when it is clear, and each arm
	// issues SetSamplerState(0, 5 /* MAGFILTER */, v) followed by
	// SetSamplerState(0, 6 /* MINFILTER */, v) through vtable +0x114.
	Byte filter = (Byte)((vm->flags >> 31) & 1u);
	if (cache->cached_filter != filter) {
		env->flush();
		cache->cached_filter = filter;
		env->set_texture_filter(filter != 0 ? 1 : 2);
	}

	cache->state_changes += 1;
}
