#include "asm_symbols.hpp"

// 0x00460636..0x00460673: digit formatter used by the CRT integer wrappers.
// Retail supplied value in EAX and destination in ECX, with radix and the
// negative flag on the stack. The wrappers now implement that behavior through
// ordinary cdecl entries, so this model gives the helper a typed C++ interface.
extern "C" void __cdecl asm_xtoa_00460636(
    unsigned int value, char* destination, unsigned int radix, int negative) {
    if (negative != 0) {
        *destination++ = '-';
        value = 0u - value;
    }

    char* const first_digit = destination;
    do {
        const unsigned int digit = value % radix;
        value /= radix;
        *destination++ = static_cast<char>(digit < 10 ? '0' + digit : 'W' + digit);
    } while (value != 0);
    *destination = '\0';

    char* left = first_digit;
    char* right = destination - 1;
    while (left < right) {
        const char temporary = *left;
        *left++ = *right;
        *right-- = temporary;
    }
}
