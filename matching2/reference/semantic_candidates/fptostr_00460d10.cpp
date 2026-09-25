#include <stddef.h>

#include "asm_symbols.hpp"

struct FptostrRecord_00460D10 {
    int sign;                  // +0x00
    int exponent;              // +0x04
    int conversion_status;     // +0x08
    const char* digits;        // +0x0C
};

typedef char FptostrRecord_00460D10_offset_check[
    offsetof(FptostrRecord_00460D10, digits) == 0x0C ? 1 : -1];
typedef char FptostrRecord_00460D10_size_check[
    sizeof(FptostrRecord_00460D10) == 0x10 ? 1 : -1];

// The effective cdecl arguments are (output, signed digit count, record).
// Ghidra's apparent fourth argument is a caller's uncleaned prior call word;
// this routine never reads it.
// Known callers ignore EAX; the void model does not expose the raw output result.
extern "C" void __cdecl Fptostr_00460D10(
    char* output, int digitCount, FptostrRecord_00460D10* record) {
    const char* source = record->digits;
    char* const digits = output + 1;
    char* cursor = digits;

    *output = '0';

    if (digitCount > 0) {
        int remaining = digitCount;
        while (remaining != 0) {
            char digit = *source;
            if (digit != '\0') {
                ++source;
            } else {
                digit = '0';
            }
            *cursor = digit;
            ++cursor;
            --remaining;
        }
    }

    *cursor = '\0';

    // Negative counts skip rounding; zero still rounds the first source digit.
    if (digitCount >= 0 &&
        static_cast<signed char>(*source) >= static_cast<signed char>('5')) {
        unsigned char* current = reinterpret_cast<unsigned char*>(cursor);
        for (;;) {
            --current;
            if (*current != static_cast<unsigned char>('9')) {
                ++*current;
                break;
            }
            *current = static_cast<unsigned char>('0');
        }
    }

    if (output[0] == '1') {
        ++record->exponent;
    } else {
        const unsigned int digitLength = asm_strlen_00456720(digits);
        asm_memmove_00453280(output, digits, digitLength + 1);
    }
}
