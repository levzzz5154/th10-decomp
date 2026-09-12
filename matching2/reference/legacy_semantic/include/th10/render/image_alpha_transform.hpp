#pragma once

#include <cstdint>

#include "th10/render/transparent_pixel_fill.hpp"

// Apply the retail format-specific alpha inversion to the first row_count
// rows. Returns one for supported formats and zero otherwise.
int Image_InvertAlpha(TransparentPixelSurface* surface,
                      std::uint32_t row_count);
