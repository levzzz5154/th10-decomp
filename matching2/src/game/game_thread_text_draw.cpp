#include "th10/game/game_thread_text_draw.hpp"

#include <cstdio>
#include <cstring>

// 0x00401A50 - draw the queued text records, switching between the two font
// banks as requested, honoring newlines and spaces, and restoring the default
// render font before returning.
int TextQueue_Draw(TextQueueHost* host, const TextQueueEnv* env) {
    host->render_flags = (host->render_flags & 0xffc3fffeu) | 0x00140001u;
    int current_font = 1;

    for (int record_index = 0; record_index < host->record_count;
         ++record_index) {
        const QueuedTextRecord& record = host->records[record_index];
        host->cursor = record.position;
        host->glyph_scale = record.advance;
        host->render_flags |= 8u;
        const float step = env->horizontal_spacing * record.advance;

        if (current_font != record.font_bank) {
            current_font = record.font_bank;
            env->select_font(current_font);
        }

        const unsigned char* text =
            reinterpret_cast<const unsigned char*>(record.text);
        while (*text != 0) {
            const unsigned char character = *text++;
            if (character == '\n') {
                host->cursor.y += record.line_scale * 14.0f;
                host->cursor.x = record.position.x;
                continue;
            }
            if (character != ' ') {
                TextGlyphDraw draw = {};
                draw.glyph_index = env->glyph_base + 68 * (character - 32);
                draw.position = host->cursor;
                draw.color = record.color;
                draw.scale = record.advance;
                draw.scaled = record.advance == 1.0f ? 0 : 1;
                host->glyph_resource = draw.glyph_index;
                env->draw_glyph(&draw);
            }
            host->cursor.x += step;
        }
    }

    if (current_font == 0) {
        env->restore_default_font();
    }
    // Retail unconditionally restores the normal bank and render state after
    // an empty queue or after finishing in bank 1 as well.
    env->select_font(0);
    env->restore_default_font();
    return 1;
}

// 0x00447BB0 - format one centered debug line. A zero font-size byte selects
// the retail default of 17 pixels; bit 1 of shadow_flags enables the shadow
// pass, and draw_flags bit 0 records that text was submitted.
int DebugText_Printf(DebugTextHost* host, const DebugTextEnv* env,
                     unsigned int color, const char* format, ...) {
    char buffer[128];
    va_list arguments;
    va_start(arguments, format);
    std::vsnprintf(buffer, sizeof(buffer), format, arguments);
    va_end(arguments);
    buffer[sizeof(buffer) - 1] = '\0';

    const int font_size = host->font_size != 0 ? host->font_size : 17;
    DebugTextDraw draw = {};
    draw.font_size = font_size;
    draw.text = buffer;
    draw.font = host->font;
    draw.line_height = static_cast<int>(host->font->position[1]);
    draw.centered_x = static_cast<int>(host->font->width) / 2 -
        (static_cast<int>(std::strlen(buffer)) * (font_size - 1)) / 4;
    draw.color = color;
    draw.shadow = static_cast<int>((host->shadow_flags >> 1) & 1u);
    env->draw_text(&draw);
    host->draw_flags |= 1u;
    return static_cast<int>(host->draw_flags);
}
