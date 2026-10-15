// 0x00436940..0x0043695E: append the NUL-terminated text in EDX to the string
// that lives at +0x0C of the owner passed on the stack.
#include <string.h>

#include "th10/util/heap.hpp"

void __fastcall AppendText(int unused, const char* text, unsigned char* owner) {
    ((LegacyString*)(owner + 0x0c))->AssignRange(text, (uint32_t)strlen(text));
}
