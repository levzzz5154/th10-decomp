// 0x00460817: shift a three-word, little-endian 96-bit value left by one.
// Word 0 is the least significant word.  Each word is unsigned so shifting
// left by one is defined modulo 2^32, and the old top bit feeds the next word.
extern "C" void __cdecl asm_shl_12_00460817(unsigned int words[3]) {
    const unsigned int lowWord = words[0];
    const unsigned int middleWord = words[1];
    const unsigned int highWord = words[2];

    const unsigned int carryFromLow = lowWord >> 31;
    const unsigned int carryFromMiddle = middleWord >> 31;

    words[0] = lowWord << 1;
    words[1] = (middleWord << 1) | carryFromLow;
    words[2] = (highWord << 1) | carryFromMiddle;
}
