#include <stdint.h>

// Retail 0x0045A77E..0x0045A7B3 receives value in EAX, remaining slots
// in ESI, and the output cursor address in EDI.
extern "C" void __cdecl AppendDecimalDigits_0045a77e(
    int32_t value, uint32_t* remaining_slots, char** cursor) {
    char* const first_digit = *cursor;
    char* output = first_digit;

    while (*remaining_slots > 1) {
        const int32_t quotient = value / 10;
        const int32_t remainder = value % 10;
        *output++ = static_cast<char>(remainder + '0');
        --*remaining_slots;
        value = quotient;
        if (value <= 0)
            break;
    }

    *cursor = output;
    char* left = first_digit;
    char* right = output - 1;
    do {
        const char leading = *left;
        const char trailing = *right;
        *right-- = leading;
        *left++ = trailing;
    } while (left < right);
}
