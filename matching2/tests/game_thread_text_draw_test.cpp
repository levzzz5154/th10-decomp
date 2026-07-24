#include "th10/game/game_thread_text_draw.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace {
int selected[8], selected_count, restore_count, glyph_count;
TextGlyphDraw glyphs[16];
void SelectFont(int bank) { selected[selected_count++] = bank; }
void DrawGlyph(const TextGlyphDraw* draw) { glyphs[glyph_count++] = *draw; }
void RestoreFont() { ++restore_count; }

DebugTextDraw debug_draw;
char debug_text[128];
void DrawDebug(const DebugTextDraw* draw) {
    debug_draw = *draw;
    std::strcpy(debug_text, draw->text);
    debug_draw.text = debug_text;
}
}

int main() {
    const QueuedTextRecord records[] = {
        {"A B\nC", {10.0f, 20.0f, 3.0f}, 0x11223344u, 1.0f, 2.0f, 0},
        {"!", {4.0f, 5.0f, 6.0f}, 0xaabbccddu, 0.5f, 1.0f, 1},
    };
    TextQueueHost queue = {};
    queue.render_flags = 0xffffffffu;
    queue.records = records;
    queue.record_count = 2;
    TextQueueEnv queue_env = {8.0f, 1000, SelectFont, DrawGlyph,
                                  RestoreFont};
    assert(TextQueue_Draw(&queue, &queue_env) == 1);
    assert((queue.render_flags & 0x00140009u) == 0x00140009u);
    assert(glyph_count == 4);
    assert(glyphs[0].glyph_index == 1000 + 68 * ('A' - 32));
    assert(glyphs[1].position.x == 26.0f); // space advanced without drawing
    assert(glyphs[2].position.x == 10.0f && glyphs[2].position.y == 48.0f);
    assert(glyphs[3].scaled == 1 && glyphs[3].scale == 0.5f);
    assert(selected_count == 3 && selected[0] == 0 && selected[1] == 1 &&
           selected[2] == 0);
    assert(restore_count == 1);

    DebugFont font = {{0.0f, 24.9f, 0.0f}, 200.0f};
    DebugTextHost debug = {0, 2, 0, &font};
    DebugTextEnv debug_env = {DrawDebug};
    assert(DebugText_Printf(&debug, &debug_env, 0xff00ff00u,
                            "No.%03d %s", 7, "ok") == 1);
    assert(std::strcmp(debug_draw.text, "No.007 ok") == 0);
    assert(debug_draw.font_size == 17 && debug_draw.line_height == 24);
    assert(debug_draw.centered_x == 64);
    assert(debug_draw.color == 0xff00ff00u && debug_draw.shadow == 1);

    std::puts("recovery_batch43_test passed");
}
