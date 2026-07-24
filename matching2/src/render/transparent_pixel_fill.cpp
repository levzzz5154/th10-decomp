#include "th10/render/transparent_pixel_fill.hpp"

#include <cstddef>

namespace {

static unsigned char* Row(TransparentPixelSurface* surface,
                          std::uint32_t y) {
    return static_cast<unsigned char*>(surface->pixels) +
           static_cast<std::ptrdiff_t>(surface->pitch_bytes) * y;
}

} // namespace

// 0x00436DA0 - Repair transparent image borders before texture upload. Retail
// scans in place and averages the RGB channels of opaque left/right/up/down
// neighbours. The 16-bit path preserves the destination alpha nibble and
// halves the averaged color nibbles, matching the A4R4G4B4 conversion path.
int Image_FillTransparentPixels(TransparentPixelSurface* surface,
                                std::uint32_t row_count) {
    if (surface == 0 || surface->pixels == 0) {
        return 1;
    }

    if (row_count > surface->height) {
        row_count = surface->height;
    }

    if (surface->format == 0x15) {
        for (std::uint32_t y = 0; y < row_count; ++y) {
            unsigned char* row = Row(surface, y);
            for (std::uint32_t x = 0; x < surface->width; ++x) {
                unsigned char* pixel = row + x * 4;
                if (pixel[3] != 0) {
                    continue;
                }

                unsigned int blue = 0;
                unsigned int green = 0;
                unsigned int red = 0;
                unsigned int count = 0;

#define ACCUMULATE_32(candidate) do { \
    const unsigned char* neighbour = (candidate); \
    if (neighbour[3] != 0) { \
        blue += neighbour[0]; \
        green += neighbour[1]; \
        red += neighbour[2]; \
        ++count; \
    } \
} while (0)

                if (x != 0) ACCUMULATE_32(pixel - 4);
                if (x + 1 < surface->width) ACCUMULATE_32(pixel + 4);
                if (y != 0) ACCUMULATE_32(pixel - surface->pitch_bytes);
                if (y + 1 < surface->height)
                    ACCUMULATE_32(pixel + surface->pitch_bytes);
#undef ACCUMULATE_32

                if (count > 1) {
                    blue /= count;
                    green /= count;
                    red /= count;
                }
                pixel[0] = static_cast<unsigned char>(blue);
                pixel[1] = static_cast<unsigned char>(green);
                pixel[2] = static_cast<unsigned char>(red);
            }
        }
    } else if (surface->format == 0x1a) {
        for (std::uint32_t y = 0; y < row_count; ++y) {
            std::uint16_t* row =
                reinterpret_cast<std::uint16_t*>(Row(surface, y));
            for (std::uint32_t x = 0; x < surface->width; ++x) {
                std::uint16_t* pixel = row + x;
                if ((*pixel & 0xf000u) != 0) {
                    continue;
                }

                unsigned int red = 0;
                unsigned int green = 0;
                unsigned int blue = 0;
                unsigned int count = 0;

#define ACCUMULATE_16(candidate) do { \
    const std::uint16_t value = *(candidate); \
    if ((value & 0xf000u) != 0) { \
        red += (value >> 8) & 0xf; \
        green += (value >> 4) & 0xf; \
        blue += value & 0xf; \
        ++count; \
    } \
} while (0)

                if (x != 0) ACCUMULATE_16(pixel - 1);
                if (x + 1 < surface->width) ACCUMULATE_16(pixel + 1);
                if (y != 0) ACCUMULATE_16(reinterpret_cast<std::uint16_t*>(
                    reinterpret_cast<unsigned char*>(pixel) -
                    surface->pitch_bytes));
                if (y + 1 < surface->height)
                    ACCUMULATE_16(reinterpret_cast<std::uint16_t*>(
                        reinterpret_cast<unsigned char*>(pixel) +
                        surface->pitch_bytes));
#undef ACCUMULATE_16

                if (count > 1) {
                    red /= count;
                    green /= count;
                    blue /= count;
                }
                *pixel = static_cast<std::uint16_t>(
                    (*pixel & 0xf000u) |
                    ((red >> 1) & 0xfu) << 8 |
                    ((green >> 1) & 0xfu) << 4 |
                    ((blue >> 1) & 0xfu));
            }
        }
    }
    return 1;
}
