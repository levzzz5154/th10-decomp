// 0x00464F88..0x00464F9D: classify the upper word of a binary64 value.
// Keep the existing C symbol while the manifest still refers to its asm name.
extern "C" unsigned int __cdecl asm_FUN_00464f88_00464f88(
    unsigned int low_word, unsigned int high_word) {
    (void)low_word;

    const unsigned int exponent = high_word & 0x7FF00000u;
    if (exponent == 0x7FF00000u)
        return high_word;
    return exponent;
}
