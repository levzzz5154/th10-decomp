// 0x004465B0 (1463 bytes): fill the fully transparent pixels of a loaded ANM
// texture from the opaque pixels touching them, so that filtering the texture
// does not bleed black into glyph and sprite edges. Takes level 0 of the D3D
// texture, locks it, and switches on the pixel format: 0 and 21 are A8R8G8B8,
// 25 is A1R5G5B5, 26 is A4R4G4B4; every other format is left untouched. A
// transparent pixel takes the plain average of the opaque pixels to its left,
// right, above and below (no halving, unlike the font atlas pass at
// 0x00436DA0); its own alpha stays zero. Then UnlockRect and Release.
//
// The receiver (the AnmTexture holding the D3D texture) arrives in
// EAX, which no calling convention declaration can name, so the model is
// compiled against the anm_texture_upload2 cluster context (see the
// layout's context_cluster), whose retail-exact caller at 0x00446C70 ends in
// `mov eax,edi; call 0x004465B0` and gives the pass its receiver register.
// The interleaved declaration order of i/surface/j is load-bearing: it puts
// the locals in retail's frame slots.
#include "th10/render/anm_texture.hpp"
#include "th10/render/anm_surface_fill.hpp"

#pragma code_seg(".text$00fill")
void AnmTexture::FillTransparentPixels() {
    // The declaration order interleaves the loop counters with the pointer
    // locals on purpose: it is what puts each local in retail's frame slot
    // (surface at +0, i at +4, j at +8, locked at +0xC, sum at +0x14, desc at
    // +0x20).  The counters are redeclared in each for statement; the shadowed
    // outer declarations exist only to hold the slots the compiler assigns.
    unsigned int i;
    AnmSurfaceFill* surface = 0;
    unsigned int j;
    AnmLockedRect locked;
    unsigned int sum[3];
    unsigned int n;
    AnmSurfaceDesc desc;

    AnmD3DTexture* tex = texture;
    tex->GetSurfaceLevel(0, reinterpret_cast<AnmSurface**>(&surface));
    surface->GetDesc(&desc);
    surface->LockRect(&locked, 0, 0);
    switch (desc.format) {
    case 0:
    case 21: {
        for (unsigned int i = 0; i < desc.height; i++) {
            unsigned char* q = (unsigned char*)locked.bits + locked.pitch * i;
            unsigned char* c = q - 2;
            for (unsigned int j = 0; j < desc.width; j++) {
                if (c[5] == 0) {
                    // Order matters: this spelling is what retail's zero
                    // initialisation schedule reproduces (the sums first,
                    // n last).
                    sum[0] = 0;
                    sum[2] = 0;
                    sum[1] = 0;
                    n = 0;
                    if (j > 0 && c[1] != 0) {
                        sum[1] = c[-1];
                        sum[0] = c[0];
                        sum[2] = c[-2];
                        n = 1;
                    }
                    if (j < desc.width - 1 && c[9] != 0) {
                        sum[0] += c[8];
                        sum[1] += c[7];
                        sum[2] += c[6];
                        n++;
                    }
                    if (i > 0) {
                        unsigned char* above = q - locked.pitch / 4 * 4;
                        if (above[3] != 0) {
                            sum[0] += above[2];
                            sum[1] += above[1];
                            sum[2] += above[0];
                            n++;
                        }
                    }
                    if (i < desc.height - 1) {
                        unsigned char* below = q + locked.pitch / 4 * 4;
                        if (below[3] != 0) {
                            sum[0] += below[2];
                            sum[1] += below[1];
                            sum[2] += below[0];
                            n++;
                        }
                    }
                    if (n > 1) {
                        sum[0] /= n;
                        sum[1] /= n;
                        sum[2] /= n;
                    }
                    c[3] = (unsigned char)sum[1];
                    q[0] = (unsigned char)sum[2];
                    c[4] = (unsigned char)sum[0];
                }
                c += 4;
                q += 4;
            }
        }
        break;
    }
    case 25: {
        for (unsigned int i = 0; i < desc.height; i++) {
            Pixel15552* p = (Pixel15552*)(
                (unsigned char*)locked.bits + locked.pitch * i);
            for (unsigned int j = 0; j < desc.width; j++) {
                if (p->a == 0) {
                    sum[0] = 0;
                    sum[2] = 0;
                    sum[1] = 0;
                    n = 1;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                    } else {
                        n = 0;
                    }
                    if (j < desc.width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel15552* above = p - locked.pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < desc.height - 1) {
                        Pixel15552* below = p + locked.pitch / 2;
                        if (below->a != 0) {
                            sum[0] += below->r;
                            sum[1] += below->g;
                            sum[2] += below->b;
                            n++;
                        }
                    }
                    if (n > 1) {
                        sum[0] /= n;
                        sum[1] /= n;
                        sum[2] /= n;
                    }
                    p->r = (unsigned char)sum[0];
                    p->g = (unsigned char)sum[1];
                    p->b = (unsigned char)sum[2];
                }
                p++;
            }
        }
        break;
    }
    case 26: {
        for (unsigned int i = 0; i < desc.height; i++) {
            Pixel44442* p = (Pixel44442*)(
                (unsigned char*)locked.bits + locked.pitch * i);
            for (unsigned int j = 0; j < desc.width; j++) {
                if (p->a == 0) {
                    sum[0] = 0;
                    sum[2] = 0;
                    sum[1] = 0;
                    n = 1;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                    } else {
                        n = 0;
                    }
                    if (j < desc.width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel44442* above = p - locked.pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < desc.height - 1) {
                        Pixel44442* below = p + locked.pitch / 2;
                        if (below->a != 0) {
                            sum[0] += below->r;
                            sum[1] += below->g;
                            sum[2] += below->b;
                            n++;
                        }
                    }
                    if (n > 1) {
                        sum[0] /= n;
                        sum[1] /= n;
                        sum[2] /= n;
                    }
                    p->r = (unsigned char)sum[0];
                    p->g = (unsigned char)sum[1];
                    p->b = (unsigned char)sum[2];
                }
                p++;
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
