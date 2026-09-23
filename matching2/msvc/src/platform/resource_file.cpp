// 0x00436CA0..0x00436CE7: fill the bitmap's word buffer with a packed color.
// The caller supplies the color in ECX while LTCG keeps this object in ESI.
struct PackedColorBuffer_00436CA0 {
    unsigned char unknown_000[0x10c];
    volatile int byte_length_10c;
    unsigned char unknown_110[0x10];
    unsigned short* pixel_words_120;

    __declspec(noinline) void Fill(unsigned int packed_color);
};

#pragma code_seg(".text$01colorfill")
void PackedColorBuffer_00436CA0::Fill(unsigned int packed_color) {
    const unsigned short color_word = static_cast<unsigned short>(
        (((packed_color >> 20) & 0x0f) << 8) |
        (((packed_color >> 12) & 0x0f) << 4) |
        ((packed_color >> 4) & 0x0f));

    unsigned short* destination = pixel_words_120;
    int byte_offset = 0;
    if (byte_length_10c > 0) {
        do {
            *destination++ = color_word;
            byte_offset += 2;
        } while (byte_offset < byte_length_10c);
    }
}
#pragma code_seg()
