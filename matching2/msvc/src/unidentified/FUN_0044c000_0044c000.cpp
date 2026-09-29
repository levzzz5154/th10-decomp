// 0x0044C000: copy one line of Shift-JIS text into a cleared buffer and return
// the start of the next non-empty line.
#include <string.h>

#pragma code_seg(".text$01accessor")
__declspec(noinline) const unsigned char* __stdcall ReadLine_0044c000(unsigned char* line, const unsigned char* text, int size) {
    memset(line, 0, size);
    int length = 0;
    while (*text != '\n' && *text != '\r' && size != 0) {
        line[length++] = *text;
        if ((*text >= 0x81 && *text <= 0x9F) || (*text >= 0xE0 && *text <= 0xFC)) {
            ++text;
            --size;
            line[length++] = *text;
        }
        ++text;
        --size;
    }
    while (*text == '\n' || *text == '\r') ++text;
    return text;
}
#pragma code_seg()
