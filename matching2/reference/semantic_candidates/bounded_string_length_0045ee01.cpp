#include <stddef.h>

// Retail 0x0045EE01..0x0045EE1C is a second _strncnt implementation.
// It receives text in EAX and the bound as one stack argument. This typed
// source expresses the same bounded scan with ordinary cdecl parameters.
extern "C" size_t __cdecl GetBoundedStringLength_0045ee01(
    const char* text, size_t bound) {
    size_t length = 0;
    while (length < bound && text[length] != '\0')
        ++length;
    return length;
}
