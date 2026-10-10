# 0x00436DA0 transparent pixel fill: register-allocation state, 2026-10-10

`FontAtlas_Convert_00436da0(atlas, rows)` gives every fully transparent pixel
of the font atlas the (halved, for 4-bit) average colour of its opaque
left/right/up/down neighbours. 946 bytes, still assembly
(`src/render/transparent_pixel_fill.cpp`). Plain `cl /O2` model below: 934
bytes, 213 of 316 instructions (4-bit path 105 of 176, 32-bit path 108 of 140).

## The finding: the colour sums are one aggregate

Retail's frame has five slots: row `[esp+0x10]`, column `[esp+0x14]`, an
unused slot `[esp+0x18]`, green `[esp+0x1c]`, blue `[esp+0x20]`. The unused
slot is red's home: the three sums are `unsigned int sum[3]` (a struct of three
compiles the same). Elements of a local aggregate are register candidates
limited to ECX and EBX (`ChoosePhysReg` shows `avail=[2, 4]`), so red and
green take those two and blue always stays in memory, with its
load/operate/store code. Three scalars instead all get registers (127 of 316).

The same explains the 32-bit path, where only red is in a register (ECX is the
second pixel pointer there) and green and blue are in memory.

## Model

```cpp
struct Pixel8888 {
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

struct Pixel4444 {
    unsigned short b : 4;
    unsigned short g : 4;
    unsigned short r : 4;
    unsigned short a : 4;
};

extern "C" char __stdcall TransparentPixelFill_00436da0(TextSurface* surface, unsigned int rows) {
    unsigned int i;
    unsigned int j;
    unsigned int sum[3];
    unsigned int n;
    unsigned short v;

    switch (surface->format) {
    case 26: {
        Pixel4444* p = (Pixel4444*)surface->bits;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < (unsigned int)surface->width; j++) {
                if (p->a == 0) {
                    sum[0] = 0;
                    sum[1] = 0;
                    sum[2] = 0;
                    n = 0;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                        n = 1;
                    }
                    if (j < (unsigned int)surface->width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel4444* above = p - surface->pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < (unsigned int)surface->height - 1) {
                        Pixel4444* below = p + surface->pitch / 2;
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
                    p->r = (unsigned char)sum[0];
                    p->g = (unsigned char)sum[1];
                    p->b = (unsigned char)sum[2];
                }
                p++;
            }
        }
        break;
    }
    case 21: {
        unsigned char* q = surface->bits;
        unsigned char* c = q - 2;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < (unsigned int)surface->width; j++) {
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
                    if (j < (unsigned int)surface->width - 1 && c[9] != 0) {
                        sum[0] += c[8];
                        sum[1] += c[7];
                        sum[2] += c[6];
                        n++;
                    }
                    if (i > 0) {
                        unsigned char* above = q - surface->pitch / 4 * 4;
                        if (above[3] != 0) {
                            sum[0] += above[2];
                            sum[1] += above[1];
                            sum[2] += above[0];
                            n++;
                        }
                    }
                    if (i < (unsigned int)surface->height - 1) {
                        unsigned char* below = q + surface->pitch / 4 * 4;
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
```

## Still different

4-bit path (retail / model): neighbour count ESI / EDI, pixel pointer EDI /
EBP, column EBP / EDX, width EDX / ESI, atlas ESI / EBX. `ChoosePhysReg`
gives ESI to the right neighbour's zero-extended pixel temporary (its
`avail` is `[6, 7, 8]`, EAX and EDX excluded) before the count is chosen; in
retail all four neighbour temporaries are in EAX. Everything else follows:
count -> EDI, pointer -> EBP, the atlas only finds EBX. Equal costs are taken
in the order ESI, EDI, EBX, EBP, so with that temporary in EAX the count,
pointer and column would land where retail has them.

32-bit path: retail shares the zero register with red (EBX is zero before the
loops, is used for `rows > 0`, `width > 0` and the green/blue resets, and is
cleared again after the stores); the model shares it with the count in ESI
because the atlas holds EBX. Retail also computes the second pointer
(`lea ecx,[ebp-2]`) at the start of every row, so it is an inner-loop
induction pointer the compiler made from indexed accesses, not a source
variable; the model's explicit `c = q - 2` is computed once.

### What pushes that temporary out of EAX

Deleting `sum[2] += p[1].b` from the right-neighbour block (a diagnostic, not a
candidate) puts the temporary back in EAX and also fixes most of the 32-bit
path (114 of 140), because the atlas then gets ESI. So the blue element's
live piece running from the left block's store to the right block's update is
what excludes EAX and EDX. The above/below blocks are immune because their
pixel word is loaded through a pointer that is already in EAX. With three
scalar sums the right block is allocated like the others.

No change from: the right block written with a named pointer, nested `if`s,
blue first, `n++` first, the left block as `+=`, moving the right block after
the other neighbours (it is still the one that differs), or one shared
`Pixel4444` copy for the four neighbours (worse, 147).

## Tried on the scalar model, no change

Declaration order; initialisers at function scope with a reset after the
stores; the accumulation as a `__forceinline` helper with reference or pointer
parameters; `p->r = (unsigned char)(r >>= 1)` and similar; order and spelling
of the neighbour blocks. The regalloc tracers work on a plain compile: put the
`cl.exe` command line in a one-entry `cmds.json`.
