#include "th10/platform/gdi_surface.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x00436AF0 - creates a zeroed top-down DIB section for the GDI font cache
// and selects it into a fresh memory DC. Returns 1 on success, 0 otherwise.
int GdiSurface_Create(GdiSurface* surface, int width, int height,
                      int format, GdiEnv* env) {
	env->release_existing(surface);

	const GdiFormat* entry = env->formats;
	while (entry->id != -1 && entry->id != format) {
		++entry;
	}
	if (format == -1 || entry->id == -1) {
		return 0;
	}

	// Pitch: bits-to-bytes rounded up, then rounded up to 4 bytes.
	int pitch = ((entry->bits_per_pixel * width + 7) / 8 + 3) & ~3;

	BitmapRequest request;
	std::memset(&request, 0, sizeof(request));
	request.width = width;
	request.height = -1 - height; // retail quirk: -1 - height, not -height
	request.planes = 1;
	request.bit_count = entry->bits_per_pixel;
	request.size_image = (Word)(pitch * height);
	if (format != 0x18 && format != 0x16) {
		// Retail copies the masks rotated: [1], [2], [3], then [0].
		request.masks[0] = entry->masks[1];
		request.masks[1] = entry->masks[2];
		request.masks[2] = entry->masks[3];
		request.masks[3] = entry->masks[0];
		request.compression = 3; // BI_BITFIELDS
	}

	void* bits = 0;
	void* bitmap = env->create_dib_section(&request, &bits);
	if (bitmap == 0) {
		return 0;
	}
	std::memset(bits, 0, request.size_image);

	void* dc = env->create_dc();
	surface->previous_object = env->select_object(dc, bitmap);
	surface->pitch = pitch;
	surface->bits = bits;
	surface->size_image = request.size_image;
	surface->dc = dc;
	surface->bitmap = bitmap;
	surface->width = width;
	surface->height = height;
	surface->format = format;
	return 1;
}
