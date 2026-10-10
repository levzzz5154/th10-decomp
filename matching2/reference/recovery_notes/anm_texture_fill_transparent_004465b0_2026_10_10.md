# 0x004465B0 AnmTexture::FillTransparentPixels: state, 2026-10-10

`void AnmTexture::FillTransparentPixels()`, texture holder in EAX, called from
the upload at 0x00446C70. It takes level 0 of the texture, `GetDesc`,
`LockRect(&locked, 0, 0)`, switches on the format (0 and 21: A8R8G8B8, 25:
A1R5G5B5, 26: A4R4G4B4; everything else leaves), fills the transparent pixels
from their opaque left/right/above/below neighbours exactly as 0x00436DA0
does (no halving here), then `UnlockRect` and `Release`.

The 1,463-byte region is 1,417 bytes of code, 3 bytes of padding, a four-entry
jump table at 0x00446B3C and the 27-byte index table at 0x00446B4C.

## Model

Measured in a one-file `/GL` + `/LTCG` rig with a looping caller stub, which
gives the EAX receiver. 337 of 498 instructions line up (head 20/33, 8888
111/134, 1555 100/160, 4444 95/157, exit 11/14); model 1,408 bytes.

```cpp
struct Desc { int format, type, usage, pool, multisample_type, multisample_quality; unsigned int width, height; };
struct LockedRect { int pitch; void* bits; };
struct Surface {
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual void __stdcall Slot03() = 0; virtual void __stdcall Slot04() = 0; virtual void __stdcall Slot05() = 0;
    virtual void __stdcall Slot06() = 0; virtual void __stdcall Slot07() = 0; virtual void __stdcall Slot08() = 0;
    virtual void __stdcall Slot09() = 0; virtual void __stdcall Slot10() = 0; virtual void __stdcall Slot11() = 0;
    virtual long __stdcall GetDesc(Desc*) = 0;
    virtual long __stdcall LockRect(LockedRect*, const void* rect, unsigned int flags) = 0;
    virtual long __stdcall UnlockRect() = 0;
};
struct Texture {
    virtual long __stdcall QueryInterface(const void*, void**) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual void __stdcall S03() = 0; virtual void __stdcall S04() = 0; virtual void __stdcall S05() = 0; virtual void __stdcall S06() = 0;
    virtual void __stdcall S07() = 0; virtual void __stdcall S08() = 0; virtual void __stdcall S09() = 0; virtual void __stdcall S10() = 0;
    virtual void __stdcall S11() = 0; virtual void __stdcall S12() = 0; virtual void __stdcall S13() = 0; virtual void __stdcall S14() = 0;
    virtual void __stdcall S15() = 0; virtual void __stdcall S16() = 0;
    virtual long __stdcall GetLevelDesc(unsigned int, Desc*) = 0;
    virtual long __stdcall GetSurfaceLevel(unsigned int, Surface**) = 0;
};
struct Pixel8888 { unsigned char b, g, r, a; };
struct Pixel1555 { unsigned short b : 5; unsigned short g : 5; unsigned short r : 5; unsigned short a : 1; };
struct Pixel4444 { unsigned short b : 4; unsigned short g : 4; unsigned short r : 4; unsigned short a : 4; };
struct AnmTexture { Texture* texture; void FillTransparentPixels(); };

// Compiler entry only: a direct caller, so the compiler passes the texture in
// a register as the retail caller (0x00446C70) does.
extern "C" __declspec(noinline) void __stdcall AnmTextureFillEntry(AnmTexture** textures, int count) {
    while (count--)
        (*textures++)->FillTransparentPixels();
}

void AnmTexture::FillTransparentPixels() {
    Surface* surface = 0;
    Desc desc;
    LockedRect locked;
    unsigned int i;
    unsigned int j;
    unsigned int sum[3];
    unsigned int n;

    texture->GetSurfaceLevel(0, &surface);
    surface->GetDesc(&desc);
    surface->LockRect(&locked, 0, 0);
    switch (desc.format) {
    case 0:
    case 21:
        for (i = 0; i < desc.height; i++) {
            unsigned char* q = (unsigned char*)locked.bits + locked.pitch * i;
            unsigned char* c = q - 2;
            for (j = 0; j < desc.width; j++) {
                if (c[5] == 0) {
                    sum[0] = 0;
                    sum[1] = 0;
                    sum[2] = 0;
                    n = 0;
                    if (j > 0 && c[1] != 0) {
                        sum[0] = c[0];
                        sum[1] = c[-1];
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
                    c[4] = (unsigned char)sum[0];
                    c[3] = (unsigned char)sum[1];
                    q[0] = (unsigned char)sum[2];
                }
                c += 4;
                q += 4;
            }
        }
        break;
    case 25:
        for (i = 0; i < desc.height; i++) {
            Pixel1555* p = (Pixel1555*)((unsigned char*)locked.bits + locked.pitch * i);
            for (j = 0; j < desc.width; j++) {
                if (p->a == 0) {
                    n = 0;
                    sum[2] = 0;
                    sum[1] = 0;
                    sum[0] = 0;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                        n = 1;
                    }
                    if (j < desc.width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel1555* above = p - locked.pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < desc.height - 1) {
                        Pixel1555* below = p + locked.pitch / 2;
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
    case 26:
        for (i = 0; i < desc.height; i++) {
            Pixel4444* p = (Pixel4444*)((unsigned char*)locked.bits + locked.pitch * i);
            for (j = 0; j < desc.width; j++) {
                if (p->a == 0) {
                    n = 0;
                    sum[2] = 0;
                    sum[1] = 0;
                    sum[0] = 0;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                        n = 1;
                    }
                    if (j < desc.width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel4444* above = p - locked.pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < desc.height - 1) {
                        Pixel4444* below = p + locked.pitch / 2;
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
    surface->UnlockRect();
    surface->Release();
}
```

## What is known

- Every row recomputes its pointer: `p = bits + pitch * i`.
- The 8888 kernel has retail's two pointers (`lea ecx,[edi-2]` per row) only
  with the explicit second pointer declared inside the row loop. The struct
  form `p[-1].r` compiles to one pointer.
- The 1555 and 4444 kernels use `(unsigned char)sum[k]` casts; the masked
  in-place `and cl,1Fh; movzx cx,cl`, the byte load of blue and the
  right-neighbour temporary in ESI all appear in the model as in retail.
- Open: retail keeps a zero in ESI from the prologue on (`surface = 0`, the
  two null `LockRect` arguments, the loop-entry compares, the zero stores of
  green and blue) and pushes ESI first, EBX/EBP/EDI only inside the switch.
  The model either uses EBX for that zero or, with the explicit 8888 pointers,
  no register at all (`push 0`). The count then takes ESI inside the kernels
  and retail re-zeroes ESI at the bottom of each pixel. The order of the four
  zero assignments moves this a lot (see the table).

| zero order (8888 / 1555, 4444) | total | note |
| --- | --- | --- |
| r,g,b,n everywhere | 329 | no zero register |
| n,b,g,r in 1555 and 4444 | 337 | no zero register |
| b,g,r,n in 8888 | 291 | zero in EBX, red spilled in 8888 |
| chained `sum[0] = sum[1] = sum[2] = 0` everywhere | 293 | zero in EBX |

Scratch tools used: an LTCG rig diff (`lg.py`: compile one source with `/GL`,
link with the stub as entry, diff the named function against retail) and a
per-kernel counter split at 0x00446606 / 0x00446798 / 0x0044695E / 0x00446B1D.
See also `font_atlas_convert_00436da0_regalloc_2026_10_10.md`.
