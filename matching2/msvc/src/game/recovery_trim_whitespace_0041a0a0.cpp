// 0x0041A0A0..0x0041A111: Recovery_TrimWhitespace
//
// Strip leading and trailing spaces, tabs, newlines and carriage returns from a
// NUL-terminated string, in place.  Retail receives and returns the string
// pointer in EAX; the model is co-compiled in the 0x0041A050 cluster so the
// whole-program pass derives that convention from its only caller.
//
// The leading shift is a written-out byte loop (`for`), which is what produces
// retail's `test/jle` guard plus the single `rep movsb`; the same code spelled
// as memmove emits a call and as memcpy the movsd/movsb pair.
#include <string.h>

#pragma code_seg(".text$02trim")
char* __stdcall TrimWhitespace_0041a0a0(char* text) {
    while (*text == ' ' || *text == '\t' || *text == '\n' || *text == '\r') {
        int length = (int)strlen(text);
        for (int index = 0; index < length; ++index) {
            text[index] = text[index + 1];
        }
    }
    int length = (int)strlen(text);
    for (int index = length - 1; index >= 0; --index) {
        char c = text[index];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') break;
        text[index] = 0;
    }
    return text;
}
#pragma code_seg()
