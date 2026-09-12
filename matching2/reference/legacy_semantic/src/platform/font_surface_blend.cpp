#include "th10/platform/font_surface_blend.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>

namespace {


} // namespace

// 0x00437750 - blends the font cache's DIB bits onto the locked destination
// surface. The copy only proceeds when the cache is valid, the lock
// succeeds, and the destination format matches the cache format. Format
// 0x15 (A8R8G8B8) alpha-blends the three color channels with the source
// alpha byte; format 0x19 (A1R5G5B5) copies only pixels whose alpha bit is
// set; format 0x1A (A4R4G4B4) blends both packed nibble pairs and saturates
// the accumulated destination alpha at 0xF. Returns 1 after unlocking on a
// matching lock, and 0 when the cache is invalid, the lock fails, or the
// format is unsupported (the retail decompile is corrupted around the
// unsupported-format exit; this reconstruction still unlocks there).
int FontCache_BlendToSurface(FontCacheSurface* cache, void* texture,
                             int dst_x, int dst_y, int rows,
                             FontSurfaceEnv* env) {
	if (cache->valid == 0) {
		return 0;
	}
	LockedSurface locked;
	if (env->lock(texture, cache->width, cache->height, &locked) != 0) {
		return 0;
	}
	if (locked.format == cache->format) {
		const Byte* src = cache->src_bits;
		const int width = cache->width;
		if (cache->format == kFontFormatA8R8G8B8) {
			Byte* dst = locked.bits + locked.pitch * dst_y + dst_x * 4;
			for (int y = 0; y < rows; ++y) {
				for (int x = 0; x < width; ++x) {
					Word alpha = src[3];
					dst[0] = (Byte)(
					    (Byte)((((Word)src[0] - dst[0]) * alpha) >> 8) +
					    dst[0]);
					dst[1] = (Byte)(
					    (Byte)((((Word)src[1] - dst[1]) * alpha) >> 8) +
					    dst[1]);
					dst[2] = (Byte)(
					    (Byte)((((Word)src[2] - dst[2]) * alpha) >> 8) +
					    dst[2]);
					dst += 4;
					src += 4;
				}
				src += cache->src_pitch - width * 4;
				dst += locked.pitch - width * 4;
			}
		} else if (cache->format == kFontFormatA1R5G5B5) {
			Byte* dst = locked.bits + locked.pitch * dst_y + dst_x * 2;
			for (int y = 0; y < rows; ++y) {
				for (int x = 0; x < width; ++x) {
					short value;
					value = (short)(src[0] | (src[1] << 8));
					if (value < 0) {
						dst[0] = src[0];
						dst[1] = src[1];
					}
					dst += 2;
					src += 2;
				}
				src += cache->src_pitch - width * 2;
				dst += locked.pitch - width * 2;
			}
		} else if (cache->format == kFontFormatA4R4G4B4) {
			Byte* dst = locked.bits + locked.pitch * dst_y + dst_x * 2;
			for (int y = 0; y < rows; ++y) {
				for (int x = 0; x < width; ++x) {
					Word alpha = (Word)(src[1] >> 4);
					Word dst_hi = (Word)(dst[0] >> 4);
					dst[0] = (Byte)(
					    (Byte)(((int)(((Word)(src[0] >> 4) - dst_hi) *
					                          alpha) >>
					                   4) +
					                  dst_hi)
					    << 4);
					dst[0] = (Byte)(
					    dst[0] | (Byte)(((src[0] & 0xF) * alpha) >> 4));
					Word alpha_sum =
					    (Word)((dst[1] >> 2) & 0x3C) + alpha;
					Word red = (Word)(dst[1] & 0xF);
					Byte new_alpha = (Byte)alpha_sum;
					if (alpha_sum >= 0x10) {
						new_alpha = 0xF;
					}
					dst[1] = (Byte)(
					    (Byte)(((int)((((Word)(src[1] & 0xF)) - red) *
					                         alpha) >>
					                   4) +
					                  red) |
					    (Byte)(new_alpha << 4));
					dst += 2;
					src += 2;
				}
				src += cache->src_pitch - width * 2;
				dst += locked.pitch - width * 2;
			}
		} else {
			env->unlock(texture);
			return 0;
		}
	}
	env->unlock(texture);
	return 1;
}
