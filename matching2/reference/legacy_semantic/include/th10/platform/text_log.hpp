#pragma once

#include "th10/platform/windows_types.hpp"

// Retail log object at DAT_00474F70: an 0x2000-byte text buffer with a
// moving append cursor and a dirty byte. The startup and configuration
// diagnostics stage their messages here under the text-log critical section
// (retail lock DAT_004922BC, depth byte DAT_0049231F).
struct TextLog {
    char text[0x2000];        // +0x0000 accumulated log text
    char* cursor;             // +0x2000 next append position inside text
    BYTE dirty;               // +0x2004 set by TextLog_AppendLine
};

void TextLog_Append(TextLog* log, const char* format, ...);
void TextLog_AppendLine(TextLog* log, const char* format, ...);
