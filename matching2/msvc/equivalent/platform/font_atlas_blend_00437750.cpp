// 0x00437750: blend the software font atlas into a locked surface.
//
// The atlas holds text drawn through GDI in one of three pixel formats; the
// surface must have the same format. Retail never calls this function, so its
// private register convention (row in EAX, atlas in EDX, column in ECX) is
// reproduced with a direct caller.
//
// Equivalent recovery: in the 4-bit path retail adds and shifts the high
// nibble as a byte (`add al,dl; shl al,4`) where this compiles to the same
// operations on the whole register. The stored byte is identical.

struct FontSurface_00437750;
struct FontSurfaceMethods_00437750 {
    void* reserved_000[0x30 / 4];
    void (__stdcall* GetDesc)(FontSurface_00437750*, void* desc);
    int (__stdcall* LockRect)(FontSurface_00437750*, void* locked, const void* rect, unsigned int flags);
    int (__stdcall* UnlockRect)(FontSurface_00437750*);
};
struct FontSurface_00437750 {
    FontSurfaceMethods_00437750* methods;
};

struct FontSurfaceDesc_00437750 {
    unsigned int format;
    unsigned int reserved_004[7];
};

struct FontRect_00437750 {
    int left;
    int top;
    int right;
    int bottom;
};

struct FontLockedRect_00437750 {
    int pitch;
    unsigned char* bits;
};

// The software font atlas (0x00474CB0 in the callers of its siblings).
struct FontAtlas_00437750 {
    unsigned char palette[0x100];
    unsigned int format;                // +0x100
    int width;                          // +0x104
    int height;                         // +0x108
    unsigned char reserved_10c[4];
    int pitch;                          // +0x110
    unsigned char reserved_114[8];
    int ready;                          // +0x11C
    unsigned char* pixels;              // +0x120
};

char FontAtlas_BlendToSurface_00437750(FontAtlas_00437750* atlas, int column, int row,
                                       FontSurface_00437750* surface, int width, int height);

// Compiler entry only: a direct caller, so the compiler picks the private
// register homes.
extern "C" __declspec(noinline) int __stdcall FontAtlasBlendEntry(FontAtlas_00437750** atlases,
                                                                  FontSurface_00437750** surfaces, int count) {
    int result = 0;
    while (count--) {
        FontAtlas_00437750* atlas = *atlases++;
        result = FontAtlas_BlendToSurface_00437750(atlas, count, count, *surfaces++, atlas->width, atlas->height);
    }
    return result;
}

char FontAtlas_BlendToSurface_00437750(FontAtlas_00437750* atlas, int column, int row,
                                       FontSurface_00437750* surface, int width, int height) {
    if (atlas->ready == 0)
        goto fail;

    FontSurfaceDesc_00437750 desc;
    surface->methods->GetDesc(surface, &desc);

    FontRect_00437750 rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = atlas->width;
    rect.bottom = atlas->height;

    FontLockedRect_00437750 locked;
    if (surface->methods->LockRect(surface, &locked, &rect, 0) != 0)
        goto fail;

    {
        int source_pitch = atlas->pitch;
        unsigned char* src = atlas->pixels;
        int pitch = locked.pitch;
        int x;
        int y;

        if (desc.format == atlas->format) {
            switch (atlas->format) {
            case 0x15: {
                // A8R8G8B8: alpha blend the three colour bytes.
                unsigned char* d = locked.bits + pitch * row + column * 4;
                for (y = 0; y < height; ++y) {
                    for (x = 0; x < width; ++x) {
                        int alpha = src[3];
                        int blue = d[0];
                        d[0] = ((src[0] - blue) * alpha >> 8) + blue;
                        int green = d[1];
                        d[1] = ((src[1] - green) * alpha >> 8) + green;
                        int red = d[2];
                        d[2] = ((src[2] - red) * alpha >> 8) + red;
                        d += 4;
                        src += 4;
                    }
                    src += source_pitch - x * 4;
                    d += pitch - x * 4;
                }
                break;
            }
            case 0x1A: {
                // A4R4G4B4: 4-bit channels, the destination alpha accumulates.
                // The low nibble is blended against the byte just stored, whose
                // low nibble is already zero.
                unsigned char* d = locked.bits + pitch * row + column * 2;
                for (y = 0; y < height; ++y) {
                    for (x = 0; x < width; ++x) {
                        int alpha = src[1] >> 4;
                        int high = d[0] >> 4;
                        int nibble = ((((src[0] >> 4) - high) * alpha >> 4) + high) * 16;
                        d[0] = nibble;
                        nibble &= 0x0F;
                        d[0] |= (((src[0] & 0x0F) - nibble) * alpha >> 4) + nibble;
                        int green = d[1] & 0x0F;
                        int alpha_out = ((d[1] >> 2) & 0x3C) + alpha;
                        int source = src[1] & 0x0F;
                        if (alpha_out >= 0x10)
                            alpha_out = 0x0F;
                        d[1] = (alpha_out << 4) | (((source - green) * alpha >> 4) + green);
                        d += 2;
                        src += 2;
                    }
                    src += source_pitch - x * 2;
                    d += pitch - x * 2;
                }
                break;
            }
            case 0x19: {
                // A1R5G5B5: one-bit alpha, copy the pixel when it is set.
                unsigned char* d = locked.bits + pitch * row + column * 2;
                for (y = 0; y < height; ++y) {
                    for (x = 0; x < width; ++x) {
                        unsigned short pixel = *(unsigned short*)src;
                        if (pixel & 0x8000)
                            *(unsigned short*)d = pixel;
                        d += 2;
                        src += 2;
                    }
                    src += source_pitch - x * 2;
                    d += pitch - x * 2;
                }
                break;
            }
            default:
                goto fail;
            }
        }
    }
    surface->methods->UnlockRect(surface);
    return 1;
fail:
    return 0;
}
