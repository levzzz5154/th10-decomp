// Ghidra identifies this as the Visual Studio 2003 CRT helper __RoundMan.
// Its two cdecl arguments are a three-word (96-bit) mantissa and the number
// of significant bits to keep.
extern "C" int __cdecl asm_ZeroTail_0045d2ca(const unsigned int* words, int bits);

extern "C" int __cdecl asm_RoundMan_0045d349(unsigned int* words, int bits) {
    const int wordIndex = bits / 32;
    const int bitInWord = bits % 32;
    const int roundingBit = 31 - bitInWord;
    const unsigned int roundingMask = 1u << roundingBit;

    int overflow = 0;
    if ((words[wordIndex] & roundingMask) != 0 &&
        asm_ZeroTail_0045d2ca(words, bits) == 0) {
        // Increment the last retained mantissa bit.  Carry moves toward the
        // most significant word, matching the CRT's three-word mantissa.
        const int incrementBit = bits - 1;
        int incrementWord = incrementBit / 32;
        const unsigned int increment = 1u << (31 - incrementBit % 32);
        unsigned int previous = words[incrementWord];
        words[incrementWord] = previous + increment;
        overflow = words[incrementWord] < previous;

        for (--incrementWord; overflow != 0 && incrementWord >= 0; --incrementWord) {
            previous = words[incrementWord];
            words[incrementWord] = previous + 1u;
            overflow = words[incrementWord] == 0;
        }
    }

    // Discard the rounding bit and all less-significant bits.  The bit at
    // `roundingBit` is retained; the mask clears only the suffix below it.
    words[wordIndex] &= 0xffffffffu << roundingBit;
    for (int i = wordIndex + 1; i < 3; ++i) {
        words[i] = 0;
    }
    return overflow;
}
