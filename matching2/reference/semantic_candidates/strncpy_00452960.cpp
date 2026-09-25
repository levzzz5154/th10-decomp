#include <cstddef>

// 0x00452960..0x00452A83: Visual Studio 2003 _strncpy implementation.
// Copy up to count source bytes and pad the remainder if a NUL is reached.
extern "C" char* __cdecl asm_strncpy_00452960(
    char* destination, const char* source, std::size_t count) {
    char* const result = destination;

    while (count != 0 && *source != '\0') {
        *destination++ = *source++;
        --count;
    }

    while (count != 0) {
        *destination++ = '\0';
        --count;
    }

    return result;
}
