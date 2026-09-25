// 0x0046074C..0x0046077C: __i64toa
// Standard cdecl wrapper.  The body spells out the conversion performed by
// the retail register-ABI x64toa helper so this entry has a typed C++ body.
extern "C" char* __cdecl asm_i64toa_0046074c(
    long long value, char* buffer, int radix) {
    const bool negative = radix == 10 && value < 0;
    unsigned long long magnitude = static_cast<unsigned long long>(value);
    if (negative)
        magnitude = 0ULL - magnitude;

    const unsigned int base = static_cast<unsigned int>(radix);
    unsigned char* output = reinterpret_cast<unsigned char*>(buffer);
    if (negative)
        *output++ = '-';

    unsigned char* first_digit = output;
    do {
        const unsigned int remainder =
            static_cast<unsigned int>(magnitude % base);
        magnitude /= base;
        *output++ = static_cast<unsigned char>(
            remainder < 10 ? remainder + 0x30 : remainder + 0x57);
    } while (magnitude != 0);

    *output = 0;
    unsigned char* last_digit = output - 1;
    while (first_digit < last_digit) {
        const unsigned char digit = *first_digit;
        *first_digit++ = *last_digit;
        *last_digit-- = digit;
    }
    return buffer;
}
