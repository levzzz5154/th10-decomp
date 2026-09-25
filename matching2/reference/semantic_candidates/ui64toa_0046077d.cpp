// 0x0046077D..0x00460797: __ui64toa
// Standard cdecl wrapper.  The body spells out the conversion performed by
// the retail register-ABI x64toa helper so this entry has a typed C++ body.
extern "C" char* __cdecl asm_ui64toa_0046077d(
    unsigned long long value, char* buffer, int radix) {
    const unsigned int base = static_cast<unsigned int>(radix);
    unsigned char* output = reinterpret_cast<unsigned char*>(buffer);
    unsigned char* first_digit = output;
    do {
        const unsigned int remainder =
            static_cast<unsigned int>(value % base);
        value /= base;
        *output++ = static_cast<unsigned char>(
            remainder < 10 ? remainder + 0x30 : remainder + 0x57);
    } while (value != 0);

    *output = 0;
    unsigned char* last_digit = output - 1;
    while (first_digit < last_digit) {
        const unsigned char digit = *first_digit;
        *first_digit++ = *last_digit;
        *last_digit-- = digit;
    }
    return buffer;
}
