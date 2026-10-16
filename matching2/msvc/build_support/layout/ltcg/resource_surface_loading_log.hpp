#ifndef SURFACE_LOADING_LOG_HPP
#define SURFACE_LOADING_LOG_HPP
struct TextLog5 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};

extern "C" TextLog5 g_log;
#endif
