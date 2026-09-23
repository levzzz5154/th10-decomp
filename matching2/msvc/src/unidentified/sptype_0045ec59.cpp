// 0x0045EC59..0x0045ECB3: classify a binary64 special value.
// The retail routine uses integer loads only, so this byte-oriented form
// leaves the x87 stack and status word untouched.
extern "C" int __cdecl asm_sptype_0045ec59(double value) {
    const unsigned char* bytes =
        reinterpret_cast<const unsigned char*>(&value);

    const unsigned long low =
        static_cast<unsigned long>(bytes[0]) |
        (static_cast<unsigned long>(bytes[1]) << 8) |
        (static_cast<unsigned long>(bytes[2]) << 16) |
        (static_cast<unsigned long>(bytes[3]) << 24);
    const unsigned long high =
        static_cast<unsigned long>(bytes[4]) |
        (static_cast<unsigned long>(bytes[5]) << 8) |
        (static_cast<unsigned long>(bytes[6]) << 16) |
        (static_cast<unsigned long>(bytes[7]) << 24);

    if (high == 0x7ff00000UL && low == 0)
        return 1;
    if (high == 0xfff00000UL && low == 0)
        return 2;

    const unsigned long exponent_and_quiet = high & 0x7ff80000UL;
    if (exponent_and_quiet == 0x7ff80000UL)
        return 3;
    if (exponent_and_quiet == 0x7ff00000UL &&
        ((high & 0x0007ffffUL) != 0 || low != 0))
        return 4;

    return 0;
}
