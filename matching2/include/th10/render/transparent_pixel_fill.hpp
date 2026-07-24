#pragma once

#include <cstdint>

// Minimal image descriptor used by the retail transparent-pixel repair pass.
struct TransparentPixelSurface {
    std::uint32_t format;       // +0x100 in the retail image owner
    std::uint32_t width;        // +0x104
    std::uint32_t height;       // +0x108
    std::int32_t pitch_bytes;   // +0x110
    void* pixels;               // +0x120
};

// Copy color into fully transparent texels from their non-transparent
// four-connected neighbours. Supported retail formats are 0x15 (32-bit
// BGRA) and 0x1A (A4R4G4B4).
int Image_FillTransparentPixels(TransparentPixelSurface* surface,
                                std::uint32_t row_count);

// Fill transparent colors without the A4R4G4B4 half-intensity conversion.
// This is the locked-surface animation texture variant.
int Image_FillTransparentColors(TransparentPixelSurface* surface);
