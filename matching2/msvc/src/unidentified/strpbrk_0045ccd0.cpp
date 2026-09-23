#include <stddef.h>

// 0x0045CCD0..0x0045CD0F: return the first string byte found in accept, or
// null if the string ends first. The asm_ name preserves the existing linker
// alias; the body is ordinary C++.
extern "C" char* __cdecl asm_strpbrk_0045ccd0(
    const unsigned char* string, const unsigned char* accept) {
    unsigned int byte_set[8] = { 0 };

    while (*accept != 0) {
        const unsigned int byte = *accept++;
        byte_set[byte >> 5] |= 1u << (byte & 31u);
    }

    while (*string != 0) {
        const unsigned int byte = *string;
        const unsigned int mask = 1u << (byte & 31u);
        if ((byte_set[byte >> 5] & mask) != 0)
            return (char*)string;
        ++string;
    }

    return 0;
}
