#include <stddef.h>

// 0x0045BE80..0x0045BEC5: return the length of the prefix of string that
// contains no byte from reject. The asm_ name preserves the existing linker
// alias; the body is ordinary C++.
extern "C" size_t __cdecl asm_strcspn_0045be80(
    const unsigned char* string, const unsigned char* reject) {
    unsigned int byte_set[8] = { 0 };

    while (*reject != 0) {
        const unsigned int byte = *reject++;
        byte_set[byte >> 5] |= 1u << (byte & 31u);
    }

    size_t length = 0;
    while (string[length] != 0) {
        const unsigned int byte = string[length];
        const unsigned int mask = 1u << (byte & 31u);
        if ((byte_set[byte >> 5] & mask) != 0)
            break;
        ++length;
    }

    return length;
}
