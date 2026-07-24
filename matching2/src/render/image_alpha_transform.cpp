#include "th10/render/image_alpha_transform.hpp"

#include <cstddef>

// 0x00437160 - Invert image alpha in place across pitch*row_count bytes.
// BGRA flips each alpha byte, A1R5G5B5 toggles the top bit and clears color
// when that produces a transparent pixel, and A4R4G4B4 flips its alpha nibble.
int Image_InvertAlpha(TransparentPixelSurface* surface,
                      std::uint32_t row_count) {
    if (surface == 0 || surface->pixels == 0) return 1;
    if (row_count > surface->height) row_count = surface->height;
    const std::size_t byte_count = static_cast<std::size_t>(
        surface->pitch_bytes < 0 ? -surface->pitch_bytes : surface->pitch_bytes) *
        row_count;
    unsigned char* bytes = static_cast<unsigned char*>(surface->pixels);

    if (surface->format == 0x15) {
        for (std::size_t offset = 3; offset < byte_count; offset += 4)
            bytes[offset] = static_cast<unsigned char>(~bytes[offset]);
        return 1;
    }
    if (surface->format == 0x19) {
        std::uint16_t* pixels = reinterpret_cast<std::uint16_t*>(bytes);
        const std::size_t count = byte_count / 2;
        for (std::size_t index = 0; index < count; ++index) {
            std::uint16_t value = static_cast<std::uint16_t>(
                static_cast<std::uint16_t>(~pixels[index]) ^ 0x7fffu);
            pixels[index] = (value & 0x8000u) != 0 ? value : 0;
        }
        return 1;
    }
    if (surface->format == 0x1a) {
        std::uint16_t* pixels = reinterpret_cast<std::uint16_t*>(bytes);
        const std::size_t count = byte_count / 2;
        for (std::size_t index = 0; index < count; ++index)
            pixels[index] ^= 0xf000u;
        return 1;
    }
    return 0;
}
