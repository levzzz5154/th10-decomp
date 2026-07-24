#include "th10/render/anm_surface_restore.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x00446D70 - ANM texture surface upload: optionally remaps the format
// index when the config forces 16-bit textures, then fills the level-0
// surface either from an in-memory image file or from raw sprite-header
// pixels (format, width, and height shorts at +6/+8/+10, pixels at +0x10),
// and records the resulting bytes-per-pixel.
int AnmSurface_UploadPixels(void* texture, int format_index,
                             int from_sprite_header, const Byte* payload,
                             int* bytes_per_pixel_out, AnmUploadEnv* env) {
	if ((env->config_flags & 1) != 0) {
		int format_id = env->format_ids[format_index];
		if (format_id == 0x15 || format_id == 0) {
			format_index = 5;
		} else if (format_id == 0x14) {
			format_index = 3;
		}
	}
	void* surface = env->lock_level_surface(texture);
	if (from_sprite_header == 0) {
		env->load_from_file_memory(surface, payload);
	} else {
		short format;
		short width;
		short height;
		std::memcpy(&format, payload + 6, sizeof(format));
		std::memcpy(&width, payload + 8, sizeof(width));
		std::memcpy(&height, payload + 10, sizeof(height));
		env->load_from_memory(surface, payload + 0x10, env->format_ids[format],
		                      width * env->bytes_per_pixel[format], width,
		                      height);
		format_index = format;
	}
	env->release_surface(surface);
	env->finalize_texture(texture);
	*bytes_per_pixel_out = env->bytes_per_pixel[format_index];
	return 0;
}

namespace {

// Shared body for the device-lost texture restores (0x00447FD0 /
// 0x00448120): nothing to do without a cached surface or while the device
// is not cooperative; a missing texture is recreated in the default pool
// with a managed-pool fallback and refilled from the cached surface, then
// the level-0 surface is refreshed (optionally rect-bounded).
void RestoreTextureCommon(AnmTextureSlot* slot, const int* rect,
                          AnmRestoreEnv* env) {
	if (slot->cached_surface == 0) return;
	if (env->test_cooperative(env->device) != 0) return;
	if (slot->texture == 0) {
		if (env->create_render_texture(env->device, slot->width, slot->height,
		                               env->format, &slot->texture) != 0 &&
		    env->create_managed_texture(env->device, slot->width, slot->height,
		                                env->format, &slot->texture) != 0) {
			env->release_object(slot->cached_surface);
			return;
		}
		if (env->copy_surface(slot->texture, slot->cached_surface) != 0) {
			env->release_object(slot->cached_surface);
			return;
		}
	}
	void* level = env->get_level_surface(slot->texture);
	env->update_surface(env->device, level, slot->cached_surface, rect);
	env->release_object(level);
}

} // namespace

// 0x00447FD0 - restore a device-lost texture from its cached surface using
// the slot's full extent.
void AnmArchive_RestoreTexture(AnmTextureSlot* slot, AnmRestoreEnv* env) {
	int full_rect[4] = {0, 0, slot->width, slot->height};
	RestoreTextureCommon(slot, full_rect, env);
}

// 0x00448120 - rect-bounded variant of the device-lost texture restore.
void AnmArchive_RestoreTextureRect(AnmTextureSlot* slot, const int* rect,
                                   AnmRestoreEnv* env) {
	RestoreTextureCommon(slot, rect, env);
}
