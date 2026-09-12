#pragma once

// Font cache blend onto a locked texture surface (retail 0x00437750).
#include "th10/util/scalars.hpp"

// D3DFORMAT codes the retail font-cache blend supports.
enum FontPixelFormat {
	kFontFormatA8R8G8B8 = 0x15, // D3DFMT_A8R8G8B8 (21)
	kFontFormatA1R5G5B5 = 0x19, // D3DFMT_A1R5G5B5 (25)
	kFontFormatA4R4G4B4 = 0x1A, // D3DFMT_A4R4G4B4 (26)
};

struct LockedSurface {
	Byte* bits; // locked destination bits (surface origin)
	int pitch;         // destination pitch in bytes
	int format;        // destination D3D format code
};

struct FontSurfaceEnv {
	// Locks the destination surface (retail: GetDesc + LockRect on the
	// texture interface); returns 0 on success.
	int (*lock)(void* texture, int width, int height,
	            LockedSurface* out);
	int (*unlock)(void* texture); // retail UnlockRect
};

struct FontCacheSurface {
	int format;            // retail +0x100: a FontPixelFormat code
	int width;             // retail +0x104 (pixels per blended row)
	int height;            // retail +0x108
	int src_pitch;         // retail +0x110 (bytes per source row)
	void* valid;           // retail +0x11C; null skips the copy entirely
	const Byte* src_bits; // retail +0x120 (DIB bits)
};

int FontCache_BlendToSurface(FontCacheSurface* cache, void* texture,
                             int dst_x, int dst_y, int rows,
                             FontSurfaceEnv* env);
