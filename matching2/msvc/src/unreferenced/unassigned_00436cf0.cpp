// 0x00436CF0..0x00436D27: GdiFormat_Find - locate a pixel-format record by id.
//
// The same walk is inlined at 0x00436B0A inside GdiSurface_Create (0x00436AF0)
// before the DIB section is built, so this address is the out-of-line copy of
// that lookup. The table at 0x00474918 holds 24-byte records terminated by an
// id of -1; its first record carries id 0x16.
//
// The retail callee takes the searched-for id in EDX, the second __fastcall
// register, and never reads ECX (its first use of ECX is the overwriting load
// of formats[0].id), so the leading register argument is left unnamed.

// Record layout shared with GdiSurface_Create: id, bits per pixel, four
// colour masks; id == -1 terminates the table.
struct GdiFormat {
    int id;
    int bits_per_pixel;
    unsigned int masks[4];
};

extern "C" unsigned char data_00474918;

extern "C" GdiFormat* __fastcall GdiFormat_Find(int unused, int id) {
    (void)unused;
    GdiFormat* formats = (GdiFormat*)&data_00474918;
    int index = 0;
    while (formats[index].id != -1 && formats[index].id != id)
        ++index;
    if (id == -1)
        return 0;
    return &formats[index];
}
