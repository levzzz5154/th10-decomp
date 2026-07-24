#include "th10/platform/font_texture_draw.hpp"

#include <cstring>

namespace {
int ClampFontSize(int size) {
	if (size < 17) return 17;
	if (size > 31) return 31;
	return size;
}

void UploadText(void* texture, int x, int font_size, unsigned int color,
                const char* text, bool shadowed,
                FontTextureUploadEnv* env) {
	font_size = ClampFontSize(font_size);
	if (shadowed) {
		std::memset(env->bitmap, 0, env->bitmap_size);
	} else {
		env->prepare_color(color);
	}
	void* previous = env->select_font(env->fonts[font_size - 17]);
	const int rows = font_size * 2 + 6;
	env->invert_alpha(rows);
	env->set_transparent_background();
	const int length = (int)std::strlen(text);
	if (shadowed) {
		env->set_text_color(0);
		env->draw_text(x * 2 + 2, 2, text, length);
	}
	env->set_text_color(color);
	env->draw_text(x * 2, 0, text, length);
	env->restore_font(previous);
	env->invert_alpha(rows);
	env->repair_transparent_pixels(rows);
	env->restore_font(previous);
	void* surface = env->acquire_surface(texture);
	env->upload_bitmap(surface, texture, env->bitmap, rows);
	if (surface != 0) env->release_surface(surface);
}
} // namespace

// 0x00437DB0 - rasterizes a black offset shadow followed by the colored text
// into a cleared DIB, repairs its transparent edge pixels, and uploads it.
void FontTexture_DrawShadowed(void* texture, int x, int font_size,
                              unsigned int color, const char* text,
                              FontTextureUploadEnv* env) {
	UploadText(texture, x, font_size, color, text, true, env);
}

// 0x00437FE0 - prepares the requested color and rasterizes the foreground-only
// variant through the same alpha inversion, edge repair, and upload pipeline.
void FontTexture_DrawPlain(void* texture, int x, int font_size,
                           unsigned int color, const char* text,
                           FontTextureUploadEnv* env) {
	UploadText(texture, x, font_size, color, text, false, env);
}
