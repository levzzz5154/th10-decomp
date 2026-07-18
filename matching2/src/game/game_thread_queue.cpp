#include "th10/game/game_thread_queue.hpp"
#ifndef _MSC_VER
#include <cstdarg>
#include <cstdio>
#endif
// 0x00401530 - Append one bounded game-thread work record. The retail ABI
// supplies the name and three-word vector through hidden registers; the clean
// API exposes both values explicitly.
void GameThread_AppendRecord(GameThread* gameThread, const char* name,
                             const uint32_t* vector) {
    unsigned char* bytes = (unsigned char*)gameThread;
    uint32_t count = *(uint32_t*)(bytes + 0x896C);
    if (count >= 0x100)
        return;

    unsigned char* record = bytes + 0x76C + count * 0x68;
    *(uint32_t*)(bytes + 0x896C) = count + 1;
    char* destination = (char*)record;
    do {
        *destination = *name;
        if (*name++ == 0)
            break;
        ++destination;
    } while (true);
    *(uint32_t*)(record + 0x40) = vector[0];
    *(uint32_t*)(record + 0x44) = vector[1];
    *(uint32_t*)(record + 0x48) = vector[2];
    *(uint32_t*)(record + 0x4C) = *(uint32_t*)(bytes + 0x8974);
    *(uint32_t*)(record + 0x50) = *(uint32_t*)(bytes + 0x8978);
    *(uint32_t*)(record + 0x54) = *(uint32_t*)(bytes + 0x897C);
    *(uint32_t*)(record + 0x5C) = *(uint32_t*)(bytes + 0x8980);
    *(uint32_t*)(record + 0x60) = 0;
    *(uint32_t*)(record + 0x64) = *(uint32_t*)(bytes + 0x8988);
}

#ifdef _MSC_VER
static unsigned int GameThread_CopyText(char* destination, unsigned int at,
                                        const char* text) {
    while (*text != 0 && at + 1 < 512)
        destination[at++] = *text++;
    return at;
}
#endif

#ifdef _MSC_VER
static void GameThread_AppendText(GameThread* gameThread,
                               const GameThreadQueueWord* vector,
                               const char* format, const char* arguments,
                               bool mark) {
    char text[512];
    unsigned int length = 0;
    while (*format != 0 && length + 1 < 512) {
        if (*format != '%') {
            text[length++] = *format++;
            continue;
        }
        ++format;
        if (*format == 'd') {
            int value = *(const int*)arguments;
            arguments += 4;
            char digits[16];
            unsigned int count = 0;
            if (value < 0) { text[length++] = '-'; value = -value; }
            do { digits[count++] = (char)('0' + value % 10); value /= 10; }
            while (value != 0 && count != sizeof(digits));
            while (count != 0) text[length++] = digits[--count];
        } else if (*format == 's') {
            length = GameThread_CopyText(
                text, length, *(const char* const*)arguments);
            arguments += 4;
        } else {
            text[length++] = *format;
        }
        ++format;
    }
    text[length] = 0;
    unsigned char* bytes = (unsigned char*)gameThread;
    uint32_t count = *(uint32_t*)(bytes + 0x896C);
    GameThread_AppendRecord(gameThread, text, vector);
    if (mark && count < 0x100)
        *(uint32_t*)(bytes + 0x764 + count * 0x68) = 1;
}
#endif

#ifndef _MSC_VER
static void GameThread_AppendPortable(GameThread* gameThread,
                                      const GameThreadQueueWord* vector,
                                      const char* format, va_list arguments,
                                      bool mark) {
    char text[512];
    std::vsnprintf(text, sizeof(text), format, arguments);
    unsigned char* bytes = (unsigned char*)gameThread;
    uint32_t count = *(uint32_t*)(bytes + 0x896C);
    GameThread_AppendRecord(gameThread, text, vector);
    if (mark && count < 0x100)
        *(uint32_t*)(bytes + 0x764 + count * 0x68) = 1;
}
#endif

// 0x00401630 - Format a work-record name before appending it.
void GameThread_AppendFormatted(GameThread* gameThread,
                                const GameThreadQueueWord* vector,
                                const char* format, ...) {
#ifndef _MSC_VER
    va_list arguments;
    va_start(arguments, format);
    GameThread_AppendPortable(gameThread, vector, format, arguments, false);
    va_end(arguments);
#else
    GameThread_AppendText(gameThread, vector, format,
                          (const char*)&format + sizeof(format), false);
#endif
}

// 0x00401690 - Formatted append variant that marks the inserted record.
void GameThread_AppendFormattedMarked(GameThread* gameThread,
                                      const GameThreadQueueWord* vector,
                                      const char* format, ...) {
#ifndef _MSC_VER
    va_list arguments;
    va_start(arguments, format);
    GameThread_AppendPortable(gameThread, vector, format, arguments, true);
    va_end(arguments);
#else
    GameThread_AppendText(gameThread, vector, format,
                          (const char*)&format + sizeof(format), true);
#endif
}
