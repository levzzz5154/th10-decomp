// 0x0044B810..0x0044B8D8: TextLog::Append
//
// Formats into an 8 KiB staging buffer while holding the text-log critical
// section, then appends the result when it fits in the log's 8 KiB ring.
#include <stdarg.h>
#include <string.h>

extern "C" int __cdecl asm_vsprintf_004524a6(
    char* buffer, const char* format, char* arguments);

struct CriticalSection_0044b810 { unsigned char storage[24]; };

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(
    CriticalSection_0044b810* section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(
    CriticalSection_0044b810* section);
extern CriticalSection_0044b810 data_004922bc;
extern unsigned char data_0049231f;
}

struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    char* Append(char* format, ...);
};

#pragma code_seg(".text$01textlog")
__declspec(noinline) char* TextLog_0044b810::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&data_004922bc);
    ++data_0049231f;
    asm_vsprintf_004524a6(staging, format, arguments);

    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) <
        (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }

    LeaveCriticalSection(&data_004922bc);
    --data_0049231f;
    return format;
}
#pragma code_seg()
