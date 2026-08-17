#include "th10/platform/text_log.hpp"

#include <cstdarg>
#include <cstring>
extern "C" int __cdecl _vsprintf(char* destination, const char* format,
                                 va_list arguments);
extern "C" void __stdcall EnterCriticalSection(void* critical_section);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);
extern unsigned int DAT_004922bc;
extern unsigned char DAT_0049231f;

namespace {

// Bounded append shared by both leaves: the staged line is copied only
// while it fits ahead of the cursor, keeping the trailing NUL inside the
// 0x2000-byte buffer. Oversized or out-of-room appends are dropped.
void TextLog_AppendStaged(TextLog* log, const char* staged) {
    unsigned int length = 0;
    while (staged[length] != 0)
        ++length;
    if (log->cursor + length < log->text + 0x1FFF) {
        for (unsigned int index = 0; index < length; ++index)
            log->cursor[index] = staged[index];
        log->cursor += length;
        *log->cursor = 0;
    }
}

} // namespace

// 0x0044B810 - Format into a 0x2000-byte staging buffer and append the
// result, all inside the text-log critical section; the depth byte is
// raised after entering and lowered after leaving.
void TextLog_Append(TextLog* log, const char* format, ...) {
    char staging[0x2000];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&DAT_004922bc);
    ++DAT_0049231f;
    _vsprintf(staging, format, arguments);
    TextLog_AppendStaged(log, staging);
    LeaveCriticalSection(&DAT_004922bc);
    --DAT_0049231f;

    va_end(arguments);
}

// 0x0044B8E0 - Format into a 0x200-byte staging buffer and append inside
// the text-log critical section, then raise the log's dirty byte after
// leaving.
void TextLog_AppendLine(TextLog* log, const char* format, ...) {
    char staging[0x200];
    va_list arguments;
    va_start(arguments, format);

    EnterCriticalSection(&DAT_004922bc);
    ++DAT_0049231f;
    _vsprintf(staging, format, arguments);
    TextLog_AppendStaged(log, staging);
    log->dirty = 1;
    LeaveCriticalSection(&DAT_004922bc);
    --DAT_0049231f;

    va_end(arguments);
}
