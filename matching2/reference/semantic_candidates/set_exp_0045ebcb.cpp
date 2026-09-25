// 0x0045EBCB..0x0045EBF4: __set_exp
// Replace the exponent bits of a double with the biased exponent requested by
// the caller, retaining its sign and fraction bits.
extern "C" double __cdecl SetExp_0045EBCB(double value, int exponent) {
    union DoubleRepresentation {
        double value;
        unsigned __int64 bits;
    } representation;

    representation.value = value;

    const unsigned int old_high_word =
        static_cast<unsigned int>(representation.bits >> 48);
    const unsigned int new_high_word =
        ((static_cast<unsigned int>(exponent) + 0x3FEu) << 4) |
        (old_high_word & 0x800Fu);
    const unsigned __int64 low_48_bits =
        (static_cast<unsigned __int64>(0xFFFFu) << 32) | 0xFFFFFFFFu;

    representation.bits =
        (representation.bits & low_48_bits) |
        (static_cast<unsigned __int64>(static_cast<unsigned short>(new_high_word)) << 48);
    return representation.value;
}
