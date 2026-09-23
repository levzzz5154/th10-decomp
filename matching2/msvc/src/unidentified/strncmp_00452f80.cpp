#include <stddef.h>

// 0x00452F80..0x00452FB8: compare up to max_count bytes, treating bytes as
// unsigned and returning only -1, 0, or 1.
extern "C" int __cdecl asm_strncmp_00452f80(
    const char* first, const char* second, size_t max_count) {
    const unsigned char* lhs = (const unsigned char*)first;
    const unsigned char* rhs = (const unsigned char*)second;

    for (size_t i = 0; i < max_count; ++i) {
        const unsigned char left = lhs[i];
        const unsigned char right = rhs[i];

        if (left != right)
            return left < right ? -1 : 1;
        if (left == 0)
            return 0;
    }

    return 0;
}
