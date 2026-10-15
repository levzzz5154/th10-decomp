#include "th10/platform/startup_shortcut.hpp"
#include <stdarg.h>
#include <string.h>
#pragma code_seg(".text$04log")
__declspec(noinline) char* TextLog_0044b8e0::AppendLine(char* format, ...) {
    char buffer[512];
    va_list va;
    va_start(va, format);
    EnterCriticalSection(&data_004922bc);
    ++data_0049231f;
    asm_vsprintf_004524a6(buffer, format, va);
    unsigned int length = strlen(buffer);
    char* dest = cursor;
    if ((unsigned int)(dest + length) < (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, buffer);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }
    dirty = 1;
    LeaveCriticalSection(&data_004922bc);
    --data_0049231f;
    return format;
}
#pragma code_seg()
