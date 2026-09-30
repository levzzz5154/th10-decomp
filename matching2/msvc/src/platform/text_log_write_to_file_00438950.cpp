// 0x00438950: close the text log with a separator line, show it in an error
// box when the log was flagged, and save it to ./log.txt. An empty log is
// left alone. Native LTCG passes the log in ESI.
#include <string.h>
#include "th10/platform/text_log.hpp"

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void* window, const char* text,
                                                          const char* caption,
                                                          unsigned int type);
int File_WriteWholeFile(const char* path, const void* buffer, unsigned long size);

enum { kMessageBoxIconError = 0x10 };

#pragma code_seg(".text$00fn")
void TextLog_0044b810::WriteToFile() {
    if (cursor == text)
        return;
    Append("---------------------------------------------------------- \r\n");
    if (dirty)
        MessageBoxA(0, text, "log", kMessageBoxIconError);
    File_WriteWholeFile("./log.txt", text, strlen(text));
}
#pragma code_seg()
