#pragma once

struct GameThread;
typedef unsigned int GameThreadQueueWord;
typedef unsigned int uint32_t;

void GameThread_AppendRecord(GameThread* gameThread, const char* name,
                             const GameThreadQueueWord* vector);
void GameThread_AppendFormatted(GameThread* gameThread,
                                const GameThreadQueueWord* vector,
                                const char* format, ...);
void GameThread_AppendFormattedMarked(GameThread* gameThread,
                                      const GameThreadQueueWord* vector,
                                      const char* format, ...);


// Packed 0x68-byte text record consumed by retail 0x00401760. It is the same
// record written by GameThread_AppendRecord and its formatted wrappers.
struct GameThreadTextRecord {
    char text[0x40];
    float x;
    float y;
    float z;
    unsigned int color;
    float horizontal_scale;
    float vertical_scale;
    unsigned int view_mode;
    unsigned int font_mode;
    unsigned int shadow;
};

struct GameThreadGlyph {
    unsigned int words[0x11];  // retail glyph entry stride is 0x44 bytes
};

struct GameThreadTextDrawEnvironment {
    void* context;
    // Flush pending geometry and select/apply the requested camera/view.
    void (*switch_view)(void* context, unsigned int view_mode);
    // Publish the glyph record selected from the 2x98-entry table.
    void (*bind_glyph)(void* context, const GameThreadGlyph* glyph);
    void (*draw_glyph)(void* context, float x, float y, float z,
                       unsigned int color);
};

// 0x00401760 - Draw all queued text records. Retail starts in view 1, changes
// views only when a record requests a different one, and restores view 0 on
// exit. Newlines move by 9 or 14 scaled pixels and, like every byte including
// spaces, still consume one horizontal advance.
int GameThread_DrawQueuedText(const GameThreadTextRecord* records, int count,
                              int proportional_advance_multiplier,
                              const GameThreadGlyph* glyph_table,
                              const GameThreadTextDrawEnvironment* environment);
