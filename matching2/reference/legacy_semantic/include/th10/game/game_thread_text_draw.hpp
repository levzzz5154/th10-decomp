#pragma once

// Queued text draw and centered debug line formatting (retail 0x00401A50, 0x00447BB0).
#include <cstdarg>

struct TextQueueVec3 { float x, y, z; };

struct QueuedTextRecord {
    const char* text;
    TextQueueVec3 position;
    unsigned int color;
    float advance;
    float line_scale;
    int font_bank;
};

struct TextGlyphDraw {
    int glyph_index;
    TextQueueVec3 position;
    unsigned int color;
    float scale;
    int scaled;
};

struct TextQueueHost {
    unsigned int render_flags;
    TextQueueVec3 cursor;
    float glyph_scale;
    int glyph_resource;
    const QueuedTextRecord* records;
    int record_count;
};

struct TextQueueEnv {
    float horizontal_spacing;
    int glyph_base;
    void (*select_font)(int font_bank);
    void (*draw_glyph)(const TextGlyphDraw* draw);
    void (*restore_default_font)();
};

int TextQueue_Draw(TextQueueHost* host, const TextQueueEnv* env);

struct DebugFont {
    float position[3];
    float width;
};

struct DebugTextHost {
    unsigned int draw_flags;
    unsigned int shadow_flags;
    unsigned char font_size;
    const DebugFont* font;
};

struct DebugTextDraw {
    int font_size;
    const char* text;
    const DebugFont* font;
    int line_height;
    int centered_x;
    unsigned int color;
    int shadow;
};

struct DebugTextEnv {
    void (*draw_text)(const DebugTextDraw* draw);
};

int DebugText_Printf(DebugTextHost* host, const DebugTextEnv* env,
                     unsigned int color, const char* format, ...);
