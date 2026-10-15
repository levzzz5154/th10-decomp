// 0x00438220..0x0043823B: assign the NUL-terminated text in EDX to the string
// passed on the stack.
#include <string.h>

#include "th10/util/heap.hpp"

void __fastcall AssignText(int unused, const char* text, LegacyString* target) {
    target->AssignRange(text, (uint32_t)strlen(text));
}
