// 0x00435280..0x004352B2: advance a string cursor past its NUL-terminated
// string, padded to the next four-byte boundary, and return the new cursor.
// Native LTCG gives the cursor address its retail EDX entry register.
#include <string.h>

#pragma code_seg(".text$01accessor")
__declspec(noinline) char* AdvancePastAlignedString2(char** cursor) {
    int length = strlen(*cursor) + 1;
    if (length % 4 != 0)
        length += 4 - length % 4;
    *cursor += length;
    return *cursor;
}
#pragma code_seg()
