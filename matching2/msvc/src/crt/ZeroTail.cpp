// 0x0045D2CA..0x0045D2FB: Test whether all trailing mantissa bits are zero.
extern "C" int __cdecl asm_ZeroTail_0045d2ca(const unsigned int* words, int bits) {
    int index = bits / 32;
    unsigned int mask = ~(-1u << (31 - bits % 32));
    if (words[index] & mask) return 0;
    while (++index < 3) {
        if (words[index] != 0) return 0;
    }
    return 1;
}
