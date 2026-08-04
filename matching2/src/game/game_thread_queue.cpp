#include "th10/game/game_thread_queue.hpp"
#ifndef _MSC_VER
#include <cstdarg>
#include <cstdio>
#else
extern "C" int _vsprintf(char*, const char*, char*);
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
extern "C" void sub_401530(void*);
#endif
// 0x00401530 - Append one bounded game-thread work record. The retail ABI
// supplies the name and three-word vector through hidden registers; the clean
// API exposes both values explicitly.
#ifdef _MSC_VER
__declspec(naked) void GameThread_AppendRecord(GameThread* gameThread,
                                               const char* name,
                                               const uint32_t* vector) {
    __asm {
        mov edx, [ecx+896Ch]
        cmp edx, 100h
        push esi
        mov esi, eax
        jge done
        mov eax, edx
        imul eax, eax, 68h
        push edi
        lea eax, [eax+ecx+76Ch]
        inc edx
        mov edi, eax
        mov [ecx+896Ch], edx
        sub edi, esi
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
copy_loop:
        mov dl, [esi]
        mov [edi+esi], dl
        inc esi
        test dl, dl
        jne copy_loop
        mov esi, [ebx]
        lea edx, [eax+40h]
        mov [edx], esi
        mov esi, [ebx+4]
        mov [edx+4], esi
        mov esi, [ebx+8]
        mov [edx+8], esi
        mov edx, [ecx+8974h]
        mov [eax+4Ch], edx
        mov edx, [ecx+8978h]
        mov [eax+50h], edx
        mov edx, [ecx+897Ch]
        mov [eax+54h], edx
        mov edx, [ecx+8980h]
        mov [eax+5Ch], edx
        mov dword ptr [eax+60h], 0
        mov ecx, [ecx+8988h]
        mov [eax+64h], ecx
        pop edi
done:
        pop esi
        ret
    }
}
#else
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
#endif

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
#ifdef _MSC_VER
__declspec(naked) void GameThread_AppendFormatted(
        GameThread* gameThread, const GameThreadQueueWord* vector,
        const char* format, ...) {
    __asm {
        sub esp, 204h
        mov eax, ___security_cookie
        mov ecx, [esp+20Ch]
        xor eax, esp
        mov [esp+200h], eax
        lea eax, [esp+210h]
        push eax
        push ecx
        lea edx, [esp+8]
        push edx
        call _vsprintf
        mov ecx, [esp+214h]
        add esp, 0Ch
        lea eax, [esp]
        call sub_401530
        mov ecx, [esp+200h]
        xor ecx, esp
        call security_check_cookie
        add esp, 204h
        ret
    }
}
#else
void GameThread_AppendFormatted(GameThread* gameThread,
                                const GameThreadQueueWord* vector,
                                const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    GameThread_AppendPortable(gameThread, vector, format, arguments, false);
    va_end(arguments);
}
#endif

// 0x00401690 - Formatted append variant that marks the inserted record.
#ifdef _MSC_VER
__declspec(naked) void GameThread_AppendFormattedMarkedRetail() {
    __asm {
        sub esp, 204h
        mov eax, ___security_cookie
        mov ecx, [esp+208h]
        xor eax, esp
        mov [esp+200h], eax
        lea eax, [esp+20Ch]
        push eax
        push ecx
        lea edx, [esp+8]
        push edx
        call _vsprintf
        add esp, 0Ch
        lea eax, [esp]
        mov ecx, esi
        call sub_401530
        mov eax, [esi+896Ch]
        mov ecx, [esp+200h]
        imul eax, 68h
        xor ecx, esp
        mov dword ptr [eax+esi+764h], 1
        call security_check_cookie
        add esp, 204h
        ret
    }
}
#endif

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


// 0x00401760 - Render the bounded queue written at game-thread +0x76C.
int GameThread_DrawQueuedText(const GameThreadTextRecord* records, int count,
                              int proportional_advance_multiplier,
                              const GameThreadGlyph* glyph_table,
                              const GameThreadTextDrawEnvironment* environment) {
    unsigned int current_view = 1;
    for (int record_index = 0; record_index < count; ++record_index) {
        const GameThreadTextRecord& record = records[record_index];
        if (current_view != record.view_mode) {
            environment->switch_view(environment->context, record.view_mode);
            current_view = record.view_mode;
        }

        float x = record.x;
        float y = record.y;
        const float advance = record.font_mode == 1
                                  ? 7.0f
                                  : proportional_advance_multiplier *
                                        record.horizontal_scale;
        const float line_height = record.font_mode == 1 ? 9.0f : 14.0f;
        const unsigned char* cursor =
            reinterpret_cast<const unsigned char*>(record.text);
        while (*cursor != 0) {
            const unsigned char character = *cursor++;
            if (character == '\n') {
                y += line_height * record.vertical_scale;
                x = record.x;
            } else if (character != ' ') {
                const unsigned int glyph_index =
                    record.font_mode * 98u + (unsigned int)character - 0x20u;
                const GameThreadGlyph* glyph = &glyph_table[glyph_index];
                environment->bind_glyph(environment->context, glyph);
                if (record.shadow != 0) {
                    // Retail keeps RGB at zero and halves the top alpha byte.
                    const unsigned int shadow_color =
                        (record.color >> 1) & 0x7F000000u;
                    environment->draw_glyph(environment->context, x + 2.0f,
                                            y + 2.0f, record.z,
                                            shadow_color);
                }
                environment->draw_glyph(environment->context, x, y, record.z,
                                        record.color);
            }
            // Retail advances for ordinary glyphs, spaces, and newlines.
            x += advance;
        }
    }

    if (current_view != 0) {
        environment->switch_view(environment->context, 0);
    }
    return 1;
}
