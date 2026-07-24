#include "th10/game/game_thread_queue.hpp"

#include <cassert>
#include <cstring>
#include <vector>


struct DrawEvent {
    float x, y, z;
    unsigned int color;
    const GameThreadGlyph* glyph;
};
static std::vector<unsigned int> g_views;
static std::vector<const GameThreadGlyph*> g_bound_glyphs;
static std::vector<DrawEvent> g_draws;

static void TestDrawQueuedText() {
    GameThreadGlyph glyphs[196] = {};
    GameThreadTextRecord records[2] = {};
    std::strcpy(records[0].text, "A B\nC");
    records[0].x = 10.0f;
    records[0].y = 20.0f;
    records[0].z = 3.0f;
    records[0].color = 0x80402010u;
    records[0].horizontal_scale = 1.5f;
    records[0].vertical_scale = 2.0f;
    records[0].view_mode = 0;
    records[0].font_mode = 0;
    records[0].shadow = 1;

    std::strcpy(records[1].text, "!");
    records[1].x = 1.0f;
    records[1].y = 2.0f;
    records[1].z = 4.0f;
    records[1].color = 0xFFABCDEFu;
    records[1].horizontal_scale = 99.0f; // ignored by fixed-width mode
    records[1].vertical_scale = 1.0f;
    records[1].view_mode = 1;
    records[1].font_mode = 1;
    records[1].shadow = 0;

    g_views.clear();
    g_bound_glyphs.clear();
    g_draws.clear();
    GameThreadTextDrawEnvironment env = {};
    env.switch_view = [](void*, unsigned int view) { g_views.push_back(view); };
    env.bind_glyph = [](void*, const GameThreadGlyph* glyph) {
        g_bound_glyphs.push_back(glyph);
    };
    env.draw_glyph = [](void*, float x, float y, float z,
                        unsigned int color) {
        g_draws.push_back({x, y, z, color, 0});
    };

    assert(GameThread_DrawQueuedText(records, 2, 4, glyphs, &env) == 1);
    // Initial view is 1: record 0 switches to 0, record 1 to 1, exit to 0.
    assert(g_views.size() == 3);
    assert(g_views[0] == 0 && g_views[1] == 1 && g_views[2] == 0);
    // A, B, and C each bind once; spaces/newlines do not. Final ! uses the
    // second 98-entry font bank.
    assert(g_bound_glyphs.size() == 4);
    assert(g_bound_glyphs[0] == &glyphs['A' - 0x20]);
    assert(g_bound_glyphs[1] == &glyphs['B' - 0x20]);
    assert(g_bound_glyphs[2] == &glyphs['C' - 0x20]);
    assert(g_bound_glyphs[3] == &glyphs[98 + '!' - 0x20]);
    // Three shadowed glyphs produce six draws; the final glyph produces one.
    assert(g_draws.size() == 7);
    assert(g_draws[0].x == 12.0f && g_draws[0].y == 22.0f);
    assert(g_draws[0].color == 0x40000000u);
    assert(g_draws[1].x == 10.0f && g_draws[1].y == 20.0f);
    // Advance is 4*1.5=6. Space consumes one advance. B starts at x=22.
    assert(g_draws[3].x == 22.0f && g_draws[3].y == 20.0f);
    // Newline resets x then consumes one advance; C starts at x=16 and y=48.
    assert(g_draws[5].x == 16.0f && g_draws[5].y == 48.0f);
    assert(g_draws[6].x == 1.0f && g_draws[6].y == 2.0f);

    g_views.clear();
    assert(GameThread_DrawQueuedText(records, 0, 4, glyphs, &env) == 1);
    // Empty queue still restores view 0 from the retail initial view 1.
    assert(g_views.size() == 1 && g_views[0] == 0);
}

int main() {
    unsigned char storage[0x8A00] = {};
    GameThread* thread = (GameThread*)storage;
    *(uint32_t*)(storage + 0x8974) = 11;
    *(uint32_t*)(storage + 0x8978) = 22;
    *(uint32_t*)(storage + 0x897C) = 33;
    *(uint32_t*)(storage + 0x8980) = 44;
    *(uint32_t*)(storage + 0x8988) = 55;
    const GameThreadQueueWord vector[3] = {101, 202, 303};
    GameThread_AppendRecord(thread, "capture", vector);
    unsigned char* record = storage + 0x76C;
    assert(*(uint32_t*)(storage + 0x896C) == 1);
    assert(std::strcmp((char*)record, "capture") == 0);
    assert(*(uint32_t*)(record + 0x40) == 101);
    assert(*(uint32_t*)(record + 0x44) == 202);
    assert(*(uint32_t*)(record + 0x48) == 303);
    assert(*(uint32_t*)(record + 0x4C) == 11);
    assert(*(uint32_t*)(record + 0x50) == 22);
    assert(*(uint32_t*)(record + 0x54) == 33);
    assert(*(uint32_t*)(record + 0x5C) == 44);
    assert(*(uint32_t*)(record + 0x60) == 0);
    assert(*(uint32_t*)(record + 0x64) == 55);

    GameThread_AppendFormatted(thread, vector, "stage-%d", 7);
    assert(std::strcmp((char*)(storage + 0x76C + 0x68), "stage-7") == 0);
    GameThread_AppendFormattedMarked(thread, vector, "marked-%s", "ok");
    assert(std::strcmp((char*)(storage + 0x76C + 2 * 0x68), "marked-ok") == 0);
    assert(*(uint32_t*)(storage + 0x764 + 2 * 0x68) == 1);

    *(uint32_t*)(storage + 0x896C) = 0x100;
    GameThread_AppendRecord(thread, "ignored", vector);
    assert(*(uint32_t*)(storage + 0x896C) == 0x100);
    TestDrawQueuedText();
    return 0;
}
