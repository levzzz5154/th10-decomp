#include "th10/game/game_thread_queue.hpp"
#include <cstdarg>
#include <cstdio>
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

// 0x00401630 - Format a work-record name before appending it.
void GameThread_AppendFormatted(GameThread* gameThread,
                                const GameThreadQueueWord* vector,
                                const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    GameThread_AppendPortable(gameThread, vector, format, arguments, false);
    va_end(arguments);
}

// 0x00401690 - Formatted append variant that marks the inserted record.

void GameThread_AppendFormattedMarked(GameThread* gameThread,
                                      const GameThreadQueueWord* vector,
                                      const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    GameThread_AppendPortable(gameThread, vector, format, arguments, true);
    va_end(arguments);
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
