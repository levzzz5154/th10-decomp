// 0x00436DA0: give the fully transparent pixels of the software font atlas
// the colour of the opaque pixels touching them, so that filtering the atlas
// texture does not bleed black into glyph edges.
//
// The atlas holds a GDI DIB; format 26 is A4R4G4B4 and format 21 is A8R8G8B8.
// A transparent pixel takes the average of the opaque pixels to its left,
// right, above and below (halved in the 4-bit format); its alpha stays zero.
//
// Equivalent recovery: the loops, the neighbour tests and every register of
// the 4-bit loop body match retail. Retail reads the three halved 4-bit sums
// as bytes (`and cl,0Fh; movzx ax,cl`, the spilled blue sum through
// `mov cl,[esp+20h]`) where this source masks whole registers, and in the
// 32-bit path retail keeps a zero in EBX and recomputes the trailing pixel
// pointer for every row.

struct FontAtlas {
    unsigned char palette[0x100];
    int format;                         // +0x100
    int width;                          // +0x104
    int height;                         // +0x108
    unsigned char reserved_10c[4];
    int pitch;                          // +0x110
    unsigned char reserved_114[0x0C];
    unsigned char* pixels;              // +0x120
};

struct Pixel4444 {
    unsigned short b : 4;
    unsigned short g : 4;
    unsigned short r : 4;
    unsigned short a : 4;
};

char __stdcall FontAtlas_FillTransparentPixels(FontAtlas* atlas, unsigned int rows) {
    unsigned int i;
    unsigned int j;
    unsigned int sum[3];
    unsigned int n;
    unsigned short v;

    switch (atlas->format) {
    case 26: {
        Pixel4444* p = (Pixel4444*)atlas->pixels;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < (unsigned int)atlas->width; j++) {
                if (p->a == 0) {
                    sum[0] = sum[1] = sum[2] = 0;
                    n = 0;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                        n = 1;
                    }
                    if (j < (unsigned int)atlas->width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel4444* above = p - atlas->pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < (unsigned int)atlas->height - 1) {
                        Pixel4444* below = p + atlas->pitch / 2;
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
                    sum[0] >>= 1;
                    sum[1] >>= 1;
                    sum[2] >>= 1;
                    p->r = sum[0];
                    p->g = sum[1];
                    p->b = sum[2];
                }
                p++;
            }
        }
        break;
    }
    case 21: {
        unsigned char* q = atlas->pixels;
        unsigned char* c = q - 2;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < (unsigned int)atlas->width; j++) {
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
                    if (j < (unsigned int)atlas->width - 1 && c[9] != 0) {
                        sum[0] += c[8];
                        sum[1] += c[7];
                        sum[2] += c[6];
                        n++;
                    }
                    if (i > 0) {
                        unsigned char* above = q - atlas->pitch / 4 * 4;
                        if (above[3] != 0) {
                            sum[0] += above[2];
                            sum[1] += above[1];
                            sum[2] += above[0];
                            n++;
                        }
                    }
                    if (i < (unsigned int)atlas->height - 1) {
                        unsigned char* below = q + atlas->pitch / 4 * 4;
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
    }
    }
    return 1;
}
