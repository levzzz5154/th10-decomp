#pragma once

// The 8 KiB diagnostic text log at 0x00474F70.
struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    char* Append(char* format, ...);
    __declspec(noinline) void WriteToFile();
};
