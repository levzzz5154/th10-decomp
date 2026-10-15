#ifndef SURFACE_LOADING_LOG_HPP
#define SURFACE_LOADING_LOG_HPP
struct TextLog_0044b8e0 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};

extern "C" TextLog_0044b8e0 g_log;
#endif
