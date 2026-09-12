#pragma once

// Shared 1024x64 font surface creation and font bank setup (retail 0x00437A00).
// --- 0x00437A00 -------------------------------------------------------------
struct FontCacheRngState { unsigned short seed; unsigned int generations; };
struct FontCacheInitEnv {
	bool (*create_surface)(int width, int height, int format);
	void* (*create_font)(int height, int weight, unsigned char charset,
	                     unsigned quality, unsigned pitch_family,
	                     const char* face);
	unsigned char* seed_pixels; // at least 256 bytes
	void** fonts;               // 15 entries, sizes 17..31
	FontCacheRngState* rng;
	const char* face;
};
void FontCache_Initialize(FontCacheInitEnv* env);
