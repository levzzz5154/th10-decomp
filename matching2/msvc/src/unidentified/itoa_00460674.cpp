#include "asm_symbols.hpp"

// 0x00460674..0x0046069D: __itoa
// The cdecl wrapper implements xtoa's formatting directly. The retail xtoa
// helper itself takes its value and destination through EAX and ECX.
extern "C" char* __cdecl asm_itoa_00460674(int value, char* destination, int radix) {
    char* const result = destination;
    unsigned int remaining = static_cast<unsigned int>(value);
    const bool negative = radix == 10 && value < 0;
    if (negative) {
        *destination++ = '-';
        remaining = 0u - remaining;
    }

    char* const first_digit = destination;
    const unsigned int base = static_cast<unsigned int>(radix);
    do {
        const unsigned int digit = remaining % base;
        remaining /= base;
        *destination++ = static_cast<char>(digit < 10 ? '0' + digit : 'W' + digit);
    } while (remaining != 0);

    *destination = '\0';
    char* left = first_digit;
    char* right = destination - 1;
    while (left < right) {
        const char temporary = *left;
        *left++ = *right;
        *right-- = temporary;
    }
    return result;
}
