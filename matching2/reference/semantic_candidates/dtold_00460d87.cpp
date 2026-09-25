#include <cstdint>

// Convert the two little-endian binary64 words into the ten significant bytes
// of the x87 extended representation used by the neighboring CRT routines.
// The destination is a twelve-byte, four-byte-aligned stack temporary; the
// helper writes dwords at offsets 0 and 4 and a 16-bit word at offset 8.
extern "C" void __cdecl Dtold_00460D87(
    std::uint32_t* extendedWords,
    const std::uint32_t* binary64Words) {
    const std::uint32_t significandLow = binary64Words[0];
    const std::uint32_t highWord = binary64Words[1];
    const std::uint16_t signAndExponent =
        static_cast<std::uint16_t>(highWord >> 16);
    const std::uint16_t binaryExponent =
        static_cast<std::uint16_t>((signAndExponent >> 4) & 0x07FFu);
    const std::uint32_t fractionHigh = highWord & 0x000FFFFFu;

    // The retail helper canonicalizes either binary64 zero, including -0, to
    // an all-zero extended value.
    if (binaryExponent == 0 && fractionHigh == 0 && significandLow == 0) {
        extendedWords[0] = 0;
        extendedWords[1] = 0;
        reinterpret_cast<std::uint16_t*>(extendedWords)[4] = 0;
        return;
    }

    std::uint16_t extendedExponent;
    std::uint32_t explicitIntegerBit;
    if (binaryExponent == 0) {
        // A nonzero binary64 subnormal has no implicit leading one. Normalize
        // its fraction below and lower this initial exponent for each shift.
        extendedExponent = 0x3C01u;
        explicitIntegerBit = 0;
    } else if (binaryExponent == 0x07FFu) {
        // Infinity and NaN share the reserved x87 exponent; retain the payload.
        extendedExponent = 0x7FFFu;
        explicitIntegerBit = 0x80000000u;
    } else {
        extendedExponent = static_cast<std::uint16_t>(binaryExponent + 0x3C00u);
        explicitIntegerBit = 0x80000000u;
    }

    extendedWords[0] = significandLow << 11;
    extendedWords[1] = (fractionHigh << 11) |
                       (significandLow >> 21) |
                       explicitIntegerBit;

    if (explicitIntegerBit == 0) {
        while ((extendedWords[1] & 0x80000000u) == 0) {
            extendedWords[1] = (extendedWords[1] << 1) |
                               (extendedWords[0] >> 31);
            extendedWords[0] <<= 1;
            --extendedExponent;
        }
    }

    reinterpret_cast<std::uint16_t*>(extendedWords)[4] =
        static_cast<std::uint16_t>((signAndExponent & 0x8000u) |
                                   extendedExponent);
}
