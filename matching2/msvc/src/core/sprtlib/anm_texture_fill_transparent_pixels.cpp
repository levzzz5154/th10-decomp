// 0x004465B0 (1463 bytes): fill the fully transparent pixels of a loaded ANM
// texture from the opaque pixels touching them, so that filtering the texture
// does not bleed black into glyph and sprite edges. Takes level 0 of the D3D
// texture, locks it, and switches on the pixel format: 0 and 21 are A8R8G8B8,
// 25 is A1R5G5B5, 26 is A4R4G4B4; every other format is left untouched. A
// transparent pixel takes the plain average of the opaque pixels to its left,
// right, above and below (no halving, unlike the font atlas pass at
// 0x00436DA0); its own alpha stays zero. Then UnlockRect and Release.
#include "th10/render/anm_texture.hpp"
#include "th10/render/anm_surface_fill.hpp"
#include "th10/render/texture_pixels.hpp"

using namespace TexturePixels;

static void AddOpaque1555(unsigned int* rgb, const Argb1555* pixel, unsigned int* count) {
    if (pixel->a != 0) {
        rgb[0] += pixel->r;
        rgb[1] += pixel->g;
        rgb[2] += pixel->b;
        ++*count;
    }
}

static void AddOpaque4444(unsigned int* rgb, const Argb4444* pixel, unsigned int* count) {
    if (pixel->a != 0) {
        rgb[0] += pixel->r;
        rgb[1] += pixel->g;
        rgb[2] += pixel->b;
        ++*count;
    }
}

#pragma code_seg(".text$00fill")
void AnmTexture::FillTransparentPixels() {
    AnmSurfaceFill* surface = 0;
    AnmLockedRect locked;
    unsigned int rgb[3];
    unsigned int neighbors;
    AnmSurfaceDesc desc;

    AnmD3DTexture* tex = texture;
    tex->GetSurfaceLevel(0, reinterpret_cast<AnmSurface**>(&surface));
    surface->GetDesc(&desc);
    surface->LockRect(&locked, 0, 0);
    switch (desc.format) {
    case 0:
    case A8R8G8B8: {
        for (unsigned int row = 0; row < desc.height; row++) {
            Argb8888* pixel = reinterpret_cast<Argb8888*>(static_cast<unsigned char*>(locked.bits) + locked.pitch * row);
            for (unsigned int column = 0; column < desc.width; column++) {
                if (pixel->a == 0) {
                    rgb[0] = 0;
                    rgb[2] = 0;
                    rgb[1] = 0;
                    neighbors = 0;
                    if (column > 0)
                        AddOpaque8888(rgb, &neighbors, pixel - 1);
                    if (column < desc.width - 1)
                        AddOpaque8888(rgb, &neighbors, pixel + 1);
                    if (row > 0)
                        AddOpaque8888(rgb, &neighbors, pixel - locked.pitch / 4);
                    if (row < desc.height - 1)
                        AddOpaque8888(rgb, &neighbors, pixel + locked.pitch / 4);
                    if (neighbors > 1) {
                        rgb[0] /= neighbors;
                        rgb[1] /= neighbors;
                        rgb[2] /= neighbors;
                    }
                    pixel->g = static_cast<unsigned char>(rgb[1]);
                    pixel->b = static_cast<unsigned char>(rgb[2]);
                    pixel->r = static_cast<unsigned char>(rgb[0]);
                }
                pixel++;
            }
        }
        break;
    }
    case A1R5G5B5: {
        for (unsigned int row = 0; row < desc.height; row++) {
            Argb1555* pixel = reinterpret_cast<Argb1555*>(static_cast<unsigned char*>(locked.bits) + locked.pitch * row);
            for (unsigned int column = 0; column < desc.width; column++) {
                if (pixel->a == 0) {
                    rgb[0] = rgb[1] = rgb[2] = 0;
                    neighbors = 0;
                    if (column > 0)
                        AddOpaque1555(rgb, pixel - 1, &neighbors);
                    if (column < desc.width - 1)
                        AddOpaque1555(rgb, pixel + 1, &neighbors);
                    if (row > 0)
                        AddOpaque1555(rgb, pixel - locked.pitch / 2, &neighbors);
                    if (row < desc.height - 1)
                        AddOpaque1555(rgb, pixel + locked.pitch / 2, &neighbors);
                    if (neighbors > 1) {
                        rgb[0] /= neighbors;
                        rgb[1] /= neighbors;
                        rgb[2] /= neighbors;
                    }
                    pixel->r = static_cast<unsigned char>(rgb[0]);
                    pixel->g = static_cast<unsigned char>(rgb[1]);
                    pixel->b = static_cast<unsigned char>(rgb[2]);
                }
                pixel++;
            }
        }
        break;
    }
    case A4R4G4B4: {
        for (unsigned int row = 0; row < desc.height; row++) {
            Argb4444* pixel = reinterpret_cast<Argb4444*>(static_cast<unsigned char*>(locked.bits) + locked.pitch * row);
            for (unsigned int column = 0; column < desc.width; column++) {
                if (pixel->a == 0) {
                    rgb[0] = rgb[1] = rgb[2] = 0;
                    neighbors = 0;
                    if (column > 0)
                        AddOpaque4444(rgb, pixel - 1, &neighbors);
                    if (column < desc.width - 1)
                        AddOpaque4444(rgb, pixel + 1, &neighbors);
                    if (row > 0)
                        AddOpaque4444(rgb, pixel - locked.pitch / 2, &neighbors);
                    if (row < desc.height - 1)
                        AddOpaque4444(rgb, pixel + locked.pitch / 2, &neighbors);
                    if (neighbors > 1) {
                        rgb[0] /= neighbors;
                        rgb[1] /= neighbors;
                        rgb[2] /= neighbors;
                    }
                    pixel->r = static_cast<unsigned char>(rgb[0]);
                    pixel->g = static_cast<unsigned char>(rgb[1]);
                    pixel->b = static_cast<unsigned char>(rgb[2]);
                }
                pixel++;
            }
        }
        break;
    }
    default:
        break;
    }
    surface->UnlockRect();
    surface->Release();
}
#pragma code_seg()
