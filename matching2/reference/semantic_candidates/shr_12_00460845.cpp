// 0x00460845: shift a three-word, little-endian 96-bit value right by one.
// Word 0 is the least significant word.  The old low bit of each higher word
// feeds the next lower word's top bit.
extern "C" void __cdecl asm_shr_12_00460845(unsigned int words[3]) {
    const unsigned int lowWord = words[0];
    const unsigned int middleWord = words[1];
    const unsigned int highWord = words[2];

    const unsigned int carryFromMiddle = middleWord << 31;
    const unsigned int carryFromHigh = highWord << 31;

    words[0] = (lowWord >> 1) | carryFromMiddle;
    words[1] = (middleWord >> 1) | carryFromHigh;
    words[2] = highWord >> 1;
}
