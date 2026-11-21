// 0x00436DA0: give the fully transparent pixels of the software font atlas
// the colour of the opaque pixels touching them, so that filtering the atlas
// texture does not bleed black into glyph edges.
//
// The atlas holds a GDI DIB; format 26 is A4R4G4B4 and format 21 is A8R8G8B8.
// A transparent pixel takes the average of the opaque pixels to its left,
// right, above and below (halved in the 4-bit format); its alpha stays zero.
#include "th10/render/font_atlas.hpp"
#include "th10/render/texture_pixels.hpp"

using namespace TexturePixels;

char __stdcall FontAtlas_FillTransparentPixels(FontAtlas* atlas, unsigned int rows) {
    unsigned int row, column;
    unsigned int rgb[3];
    unsigned int neighbors;

    switch (atlas->format) {
    case A4R4G4B4: {
        Argb4444* pixel = reinterpret_cast<Argb4444*>(atlas->pixels);
        for (row = 0; row < rows; ++row) {
            for (column = 0; column < static_cast<unsigned int>(atlas->width); ++column) {
                if (pixel->a == 0) {
                    rgb[0] = rgb[1] = rgb[2] = 0;
                    neighbors = 0;
                    if (column > 0 && pixel[-1].a != 0) {
                        rgb[0] = pixel[-1].r;
                        rgb[1] = pixel[-1].g;
                        rgb[2] = pixel[-1].b;
                        neighbors = 1;
                    }
                    if (column < static_cast<unsigned int>(atlas->width) - 1 && pixel[1].a != 0) {
                        rgb[0] += pixel[1].r;
                        rgb[1] += pixel[1].g;
                        rgb[2] += pixel[1].b;
                        ++neighbors;
                    }
                    if (row > 0) {
                        Argb4444* above = pixel - atlas->pitch / 2;
                        if (above->a != 0) {
                            rgb[0] += above->r;
                            rgb[1] += above->g;
                            rgb[2] += above->b;
                            ++neighbors;
                        }
                    }
                    if (row < static_cast<unsigned int>(atlas->height) - 1) {
                        Argb4444* below = pixel + atlas->pitch / 2;
                        if (below->a != 0) {
                            rgb[0] += below->r;
                            rgb[1] += below->g;
                            rgb[2] += below->b;
                            ++neighbors;
                        }
                    }
                    if (neighbors > 1) {
                        for (unsigned int channel = 0; channel < 3; ++channel)
                            rgb[channel] /= neighbors;
                    }
                    rgb[0] >>= 1;
                    rgb[1] >>= 1;
                    rgb[2] >>= 1;
                    pixel->r = static_cast<unsigned char>(rgb[0]);
                    pixel->g = static_cast<unsigned char>(rgb[1]);
                    pixel->b = static_cast<unsigned char>(rgb[2]);
                }
                ++pixel;
            }
        }
        break;
    }
    case A8R8G8B8: {
        Argb8888* pixel = reinterpret_cast<Argb8888*>(atlas->pixels);
        for (row = 0; row < rows; ++row) {
            for (column = 0; column < static_cast<unsigned int>(atlas->width); ++column) {
                if (pixel->a == 0) {
                    neighbors = rgb[0] = rgb[1] = rgb[2] = 0;
                    if (column > 0)
                        AddOpaque8888(rgb, &neighbors, pixel - 1);
                    if (column < static_cast<unsigned int>(atlas->width) - 1)
                        AddOpaque8888(rgb, &neighbors, pixel + 1);
                    if (row > 0)
                        AddOpaque8888(rgb, &neighbors, pixel - atlas->pitch / 4);
                    if (row < static_cast<unsigned int>(atlas->height) - 1)
                        AddOpaque8888(rgb, &neighbors, pixel + atlas->pitch / 4);
                    if (neighbors > 1) {
                        rgb[0] /= neighbors;
                        rgb[1] /= neighbors;
                        rgb[2] /= neighbors;
                    }
                    pixel->r = static_cast<unsigned char>(rgb[0]);
                    pixel->g = static_cast<unsigned char>(rgb[1]);
                    pixel->b = static_cast<unsigned char>(rgb[2]);
                }
                ++pixel;
            }
        }
        break;
    }
    }
    return 1;
}
