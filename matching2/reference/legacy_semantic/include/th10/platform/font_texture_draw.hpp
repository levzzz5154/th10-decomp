#pragma once

#include <cstddef>

// GDI font cache shadowed/plain text rasterization and upload (retail 0x00437DB0, 0x00437FE0).
struct FontTextureUploadEnv {
	void* fonts[15]; // sizes 17..31
	unsigned char* bitmap;
	std::size_t bitmap_size;
	void (*prepare_color)(unsigned int color);
	void* (*select_font)(void* font);
	void (*set_transparent_background)();
	void (*set_text_color)(unsigned int color);
	void (*draw_text)(int x, int y, const char* text, int length);
	void (*restore_font)(void* font);
	void (*invert_alpha)(int rows);
	void (*repair_transparent_pixels)(int rows);
	void* (*acquire_surface)(void* texture);
	void (*upload_bitmap)(void* destination_surface, void* texture,
	                     const unsigned char* bitmap, int rows);
	void (*release_surface)(void* surface);
};

// 0x00437DB0: clear, draw black offset shadow + colored foreground, upload.
void FontTexture_DrawShadowed(void* texture, int x, int font_size,
                              unsigned int color, const char* text,
                              FontTextureUploadEnv* env);

// 0x00437FE0: prepare color, draw one colored foreground pass, upload.
void FontTexture_DrawPlain(void* texture, int x, int font_size,
                           unsigned int color, const char* text,
                           FontTextureUploadEnv* env);
