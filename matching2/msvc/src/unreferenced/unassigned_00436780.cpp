// 0x00436780..0x00436790: `strlen` of the one stack argument, inlined by the
// compiler as the ADL-free byte scan. The function cleans nothing, so it is
// __cdecl rather than the /Gz default.
#include <string.h>

extern "C" int __cdecl Length_00436780(const char* text) {
    return (int)strlen(text);
}
