#pragma once

// The 8 KiB diagnostic text log at 0x00474F70.
struct TextLog {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    char* Append(char* format, ...);        // 0x0044B810
    char* AppendLine(char* format, ...);    // 0x0044B8E0
    __declspec(noinline) void WriteToFile();
};
