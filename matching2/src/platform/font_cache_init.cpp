#include "th10/platform/font_cache_init.hpp"
#include "th10/render/queued_anm_cleanup.hpp"

// 0x00437A00 - creates the shared 1024x64 font surface (preferring A4R4G4B4),
// seeds the first 256 DIB bytes from the retail RNG, and creates fonts 17..31.
void FontCache_Initialize(FontCacheInitEnv* env) {
	if (!env->create_surface(0x400, 0x40, 0x1A)) {
		env->create_surface(0x400, 0x40, 0x15);
	}
	for (unsigned index = 0; index < 0x100; ++index) {
		unsigned short value = (unsigned short)((env->rng->seed ^ 0x9630u) + 0x9AADu);
		short next = (short)((value >> 14) + value * 4);
		env->rng->seed = (unsigned short)next;
		env->rng->generations += 1;
		env->seed_pixels[index] = (unsigned char)((unsigned short)next >> 9);
	}
	for (int index = 0; index < 15; ++index) {
		env->fonts[index] = env->create_font(0x20 + index * 2, 400, 0x80,
		                                     4, 0x11, env->face);
	}
}

namespace {
} // namespace
