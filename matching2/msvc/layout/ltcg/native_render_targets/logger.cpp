// 0x0044B810..0x0044B8D8: TextLog::Append
//
// Formats into an 8 KiB staging buffer while holding the text-log critical
// section, then appends the result when it fits in the log's 8 KiB ring.
#include <stdarg.h>
#include <string.h>
#include "th10/platform/text_log.hpp"
#include "th10/platform/thread_sync.hpp"

extern "C" int __cdecl asm_vsprintf_004524a6(
    char* buffer, const char* format, char* arguments);


#pragma code_seg(".text$a18logger")
__declspec(noinline) char* TextLog_0044b810::Append(char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&g_thread_synchronization.critical_sections[3]);
    ++g_thread_synchronization.text_log_lock_depth;
    asm_vsprintf_004524a6(staging, format, arguments);

    unsigned int length = strlen(staging);
    char* destination = cursor;
    if ((unsigned int)(destination + length) <
        (unsigned int)((char*)this + 0x1FFF)) {
        strcpy(cursor, staging);
        cursor = (char*)((unsigned int)cursor + length);
        *cursor = 0;
    }

    LeaveCriticalSection(&g_thread_synchronization.critical_sections[3]);
    --g_thread_synchronization.text_log_lock_depth;
    return format;
}
#pragma code_seg()
