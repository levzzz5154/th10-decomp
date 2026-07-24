#pragma once

// GDI surface creation for font rendering (retail 0x00436AF0).
#include "th10/util/scalars.hpp"

struct GdiFormat {
	int id; // -1 terminates the table
	int bits_per_pixel;
	Word masks[4];
};

struct BitmapRequest {
	int width;
	int height; // retail stores -1 - height (top-down quirk)
	int planes;
	int bit_count;
	int compression; // 3 when masked
	Word size_image;
	Word masks[4];
};

struct GdiSurface {
	int format;
	int width;
	int height;
	Word size_image;
	int pitch;
	void* dc;
	void* previous_object;
	void* bitmap;
	void* bits;
};

struct GdiEnv {
	void (*release_existing)(GdiSurface* surface);
	const GdiFormat* formats;
	void* (*create_dib_section)(BitmapRequest* request, void** bits_out);
	void* (*create_dc)(void);
	void* (*select_object)(void* dc, void* bitmap);
};

int GdiSurface_Create(GdiSurface* surface, int width, int height,
                      int format, GdiEnv* env);
