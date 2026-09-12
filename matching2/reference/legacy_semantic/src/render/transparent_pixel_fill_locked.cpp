#include "th10/render/transparent_pixel_fill.hpp"

#include <cstddef>
#include <cstdint>

namespace {
unsigned char* LockedRow(TransparentPixelSurface* surface, std::uint32_t y) {
    return static_cast<unsigned char*>(surface->pixels) +
           static_cast<std::ptrdiff_t>(surface->pitch_bytes) * y;
}
}

// 0x004465B0 - Lock an animation surface and copy neighboring color into fully
// transparent texels for BGRA, A1R5G5B5, and A4R4G4B4 formats. The clean form
// operates on the already-locked descriptor; device lock/unlock ownership stays
// at the caller boundary. Colors are averaged in place without the half-scale
// conversion used by the separate 0x00436DA0 image-owner path.
int Image_FillTransparentColors(TransparentPixelSurface* surface) {
    if (surface == 0 || surface->pixels == 0) return 1;
    const std::uint32_t width = surface->width;
    const std::uint32_t height = surface->height;

    if (surface->format == 0 || surface->format == 0x15) {
        for (std::uint32_t y = 0; y < height; ++y) {
            unsigned char* row = LockedRow(surface, y);
            for (std::uint32_t x = 0; x < width; ++x) {
                unsigned char* pixel = row + x * 4;
                if (pixel[3] != 0) continue;
                unsigned int c0 = 0, c1 = 0, c2 = 0, count = 0;
#define ADD32(p) do { const unsigned char* n=(p); if(n[3]) { c0+=n[0]; c1+=n[1]; c2+=n[2]; ++count; } } while(0)
                if (x) ADD32(pixel - 4);
                if (x + 1 < width) ADD32(pixel + 4);
                if (y) ADD32(pixel - surface->pitch_bytes);
                if (y + 1 < height) ADD32(pixel + surface->pitch_bytes);
#undef ADD32
                if (count > 1) { c0 /= count; c1 /= count; c2 /= count; }
                pixel[0] = static_cast<unsigned char>(c0);
                pixel[1] = static_cast<unsigned char>(c1);
                pixel[2] = static_cast<unsigned char>(c2);
            }
        }
        return 1;
    }

    if (surface->format == 0x19 || surface->format == 0x1a) {
        const std::uint16_t alpha_mask =
            surface->format == 0x19 ? 0x8000u : 0xf000u;
        const unsigned shift0 = surface->format == 0x19 ? 10 : 8;
        const unsigned shift1 = surface->format == 0x19 ? 5 : 4;
        const std::uint16_t channel_mask =
            surface->format == 0x19 ? 0x1fu : 0x0fu;
        for (std::uint32_t y = 0; y < height; ++y) {
            std::uint16_t* row =
                reinterpret_cast<std::uint16_t*>(LockedRow(surface, y));
            for (std::uint32_t x = 0; x < width; ++x) {
                std::uint16_t* pixel = row + x;
                if ((*pixel & alpha_mask) != 0) continue;
                unsigned int c0 = 0, c1 = 0, c2 = 0, count = 0;
#define ADD16(p) do { const std::uint16_t v=*(p); if(v & alpha_mask) { c0+=(v>>shift0)&channel_mask; c1+=(v>>shift1)&channel_mask; c2+=v&channel_mask; ++count; } } while(0)
                if (x) ADD16(pixel - 1);
                if (x + 1 < width) ADD16(pixel + 1);
                if (y) ADD16(reinterpret_cast<std::uint16_t*>(
                    reinterpret_cast<unsigned char*>(pixel) - surface->pitch_bytes));
                if (y + 1 < height) ADD16(reinterpret_cast<std::uint16_t*>(
                    reinterpret_cast<unsigned char*>(pixel) + surface->pitch_bytes));
#undef ADD16
                if (count > 1) { c0 /= count; c1 /= count; c2 /= count; }
                *pixel = static_cast<std::uint16_t>(
                    (*pixel & alpha_mask) |
                    ((c0 & channel_mask) << shift0) |
                    ((c1 & channel_mask) << shift1) |
                    (c2 & channel_mask));
            }
        }
    }
    return 1;
}
