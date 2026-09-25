#include "asm_symbols.hpp"

// Existing assembly callers keep their raw symbol through regions.json.
extern "C" unsigned __int64 __stdcall Allmul_00456640(
    unsigned int leftLow,
    unsigned int leftHigh,
    unsigned int rightLow,
    unsigned int rightHigh) {
    // Form the low 64 bits of the 32-by-32 product without a wide multiply.
    // Splitting into 16-bit limbs keeps every product within 32-bit arithmetic
    // and avoids recursively invoking this runtime helper.
    const unsigned int leftLowLow16 = leftLow & 0xFFFF;
    const unsigned int leftLowHigh16 = leftLow >> 16;
    const unsigned int rightLowLow16 = rightLow & 0xFFFF;
    const unsigned int rightLowHigh16 = rightLow >> 16;

    const unsigned int limb00 = leftLowLow16 * rightLowLow16;
    const unsigned int limb01 = leftLowLow16 * rightLowHigh16;
    const unsigned int limb10 = leftLowHigh16 * rightLowLow16;
    const unsigned int limb11 = leftLowHigh16 * rightLowHigh16;
    const unsigned int middle = (limb00 >> 16) + (limb01 & 0xFFFF) + (limb10 & 0xFFFF);

    const unsigned int productLow = (middle << 16) | (limb00 & 0xFFFF);
    const unsigned int productHigh = limb11 + (limb01 >> 16) + (limb10 >> 16) + (middle >> 16);

    // Cross-products contribute only to the high half of the 64-bit result.
    const unsigned int resultHigh = productHigh + leftHigh * rightLow + leftLow * rightHigh;
    return (static_cast<unsigned __int64>(resultHigh) << 32) | productLow;
}
