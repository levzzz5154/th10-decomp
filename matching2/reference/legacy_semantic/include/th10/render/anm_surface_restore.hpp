#pragma once

// ANM surface pixel upload and device-lost texture restore (retail 0x00446D70, 0x00447FD0, 0x00448120).
#include "th10/util/scalars.hpp"

struct AnmUploadEnv {
	Word config_flags; // bit 0 forces 16-bit texture formats
	const int* format_ids;
	const int* bytes_per_pixel;
	void* (*lock_level_surface)(void* texture);
	int (*load_from_file_memory)(void* surface, const Byte* file_data);
	int (*load_from_memory)(void* surface, const Byte* pixels, int format,
	                        int pitch, int width, int height);
	void (*release_surface)(void* surface);
	void (*finalize_texture)(void* texture);
};

int AnmSurface_UploadPixels(void* texture, int format_index,
                             int from_sprite_header, const Byte* payload,
                             int* bytes_per_pixel_out, AnmUploadEnv* env);

struct AnmTextureSlot {
	void* cached_surface; // system-memory copy that survives device loss
	void* texture;        // recreated when null
	int width;
	int height;
};

struct AnmRestoreEnv {
	void* device;
	int format;
	int (*test_cooperative)(void* device); // nonzero = device not ready
	int (*create_render_texture)(void* device, int width, int height,
	                             int format, void** out);
	int (*create_managed_texture)(void* device, int width, int height,
	                              int format, void** out);
	int (*copy_surface)(void* dest_texture, void* source_surface);
	void* (*get_level_surface)(void* texture);
	void (*release_object)(void* object);
	void (*update_surface)(void* device, void* dest_surface,
	                       void* source_surface, const int* rect);
};

void AnmArchive_RestoreTexture(AnmTextureSlot* slot, AnmRestoreEnv* env);

void AnmArchive_RestoreTextureRect(AnmTextureSlot* slot, const int* rect,
                                   AnmRestoreEnv* env);
