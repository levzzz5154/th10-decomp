#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "th10/types.h"
#include "th10/entity.h"
#include "th10/renderer.h"
#include "th10/msg_decoder.h"
#include "th10/ecl_vm.h"
#include "th10/stage_loader.h"
#include "th10/dat_reader.h"
#include "th10/anm_loader.h"
#include "th10/bns_loader.h"
#include "th10/menu.h"
#include "th10/replay.h"
#include "th10/sht_loader.h"
#include "lzss.h"
#include "th_decrypt.h"
#include <SDL2/SDL.h>

using namespace th10;

// ─── Font texture (procedural 8×16 glyphs in 16×16 grid) ────────────────────

struct Font {
    int tex_id = 0;
    int glyph_w = 8, glyph_h = 16;
    int cols = 16;

    int build() {
        const int tw = 256, th = 256;
        uint8_t* pixels = new uint8_t[tw * th * 4]();
        for (int y = 0; y < th; y++)
            for (int x = 0; x < tw; x++) {
                int i = (y * tw + x) * 4;
                pixels[i+3] = 0;
            }

        // Bitmap font for 0x20-0x7F (printable ASCII)
        static const uint8_t glyph[96][16] = {
            // Space
            {0},
            // !
            {0,0,0x18,0x3C,0x3C,0x18,0x18,0x00,0x18,0x18,0x00,0,0,0,0,0},
            // "
            {0,0,0x66,0x66,0x66,0x24,0,0,0,0,0,0,0,0,0,0},
            // #
            {0,0,0x36,0x36,0x7F,0x36,0x7F,0x36,0x36,0,0,0,0,0,0,0},
            // $
            {0x08,0x08,0x3E,0x69,0x68,0x3E,0x0B,0x4B,0x3E,0x08,0x08,0,0,0,0,0},
            // %
            {0,0,0x61,0x93,0x66,0x0C,0x18,0x33,0x65,0,0,0,0,0,0,0},
            // &
            {0,0,0x1C,0x36,0x36,0x1C,0x6E,0x33,0x7B,0xCE,0x7F,0,0,0,0,0},
            // '
            {0,0,0x18,0x18,0x18,0x0C,0,0,0,0,0,0,0,0,0,0},
            // (,
            {0,0,0x06,0x0C,0x18,0x18,0x18,0x18,0x18,0x0C,0x06,0,0,0,0,0},
            // )
            {0,0,0x30,0x18,0x0C,0x0C,0x0C,0x0C,0x0C,0x18,0x30,0,0,0,0,0},
            // *
            {0,0,0,0x66,0x3C,0xFF,0x3C,0x66,0,0,0,0,0,0,0,0},
            // +
            {0,0,0,0x08,0x08,0x3E,0x08,0x08,0,0,0,0,0,0,0,0},
            // ,
            {0,0,0,0,0,0,0,0x18,0x18,0x0C,0,0,0,0,0,0},
            // -
            {0,0,0,0,0,0x3E,0,0,0,0,0,0,0,0,0,0},
            // .
            {0,0,0,0,0,0,0,0x18,0x18,0,0,0,0,0,0,0},
            // /
            {0,0,0x03,0x06,0x0C,0x18,0x30,0x60,0x40,0,0,0,0,0,0,0},
            // 0
            {0,0,0x3C,0x66,0x6E,0x7E,0x76,0x66,0x3C,0,0,0,0,0,0,0},
            // 1
            {0,0,0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0,0,0,0,0,0,0},
            // 2
            {0,0,0x3C,0x66,0x06,0x0C,0x18,0x30,0x7E,0,0,0,0,0,0,0},
            // 3
            {0,0,0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0,0,0,0,0,0,0},
            // 4
            {0,0,0x0C,0x1C,0x2C,0x4C,0x7E,0x0C,0x0C,0,0,0,0,0,0,0},
            // 5
            {0,0,0x7E,0x60,0x7C,0x06,0x06,0x66,0x3C,0,0,0,0,0,0,0},
            // 6
            {0,0,0x1C,0x30,0x60,0x7C,0x66,0x66,0x3C,0,0,0,0,0,0,0},
            // 7
            {0,0,0x7E,0x06,0x0C,0x18,0x30,0x30,0x30,0,0,0,0,0,0,0},
            // 8
            {0,0,0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0,0,0,0,0,0,0},
            // 9
            {0,0,0x3C,0x66,0x66,0x3E,0x06,0x0C,0x38,0,0,0,0,0,0,0},
            // :
            {0,0,0,0x18,0x18,0,0x18,0x18,0,0,0,0,0,0,0,0},
            // ;
            {0,0,0,0x18,0x18,0,0x18,0x18,0x0C,0,0,0,0,0,0,0},
            // <
            {0,0,0x06,0x0C,0x18,0x30,0x18,0x0C,0x06,0,0,0,0,0,0,0},
            // =
            {0,0,0,0,0x7E,0,0,0x7E,0,0,0,0,0,0,0,0},
            // >
            {0,0,0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0,0,0,0,0,0,0},
            // ?
            {0,0,0x3C,0x66,0x06,0x0C,0x18,0,0x18,0x18,0,0,0,0,0,0},
            // @
            {0,0,0x3C,0x66,0x6E,0x6A,0x6E,0x60,0x3C,0,0,0,0,0,0,0},
            // A-P (0x41-0x50)
            {0,0,0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0,0,0,0,0,0,0},
            {0,0,0x7C,0x66,0x66,0x7C,0x66,0x66,0x7C,0,0,0,0,0,0,0},
            {0,0,0x3C,0x66,0x60,0x60,0x60,0x66,0x3C,0,0,0,0,0,0,0},
            {0,0,0x78,0x6C,0x66,0x66,0x66,0x6C,0x78,0,0,0,0,0,0,0},
            {0,0,0x7E,0x60,0x60,0x7C,0x60,0x60,0x7E,0,0,0,0,0,0,0},
            {0,0,0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0,0,0,0,0,0,0},
            {0,0,0x3C,0x66,0x60,0x6E,0x66,0x66,0x3E,0,0,0,0,0,0,0},
            {0,0,0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0,0,0,0,0,0,0},
            {0,0,0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0,0,0,0,0,0,0},
            {0,0,0x1E,0x0C,0x0C,0x0C,0x0C,0x6C,0x38,0,0,0,0,0,0,0},
            {0,0,0x66,0x6C,0x78,0x70,0x78,0x6C,0x66,0,0,0,0,0,0,0},
            {0,0,0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0,0,0,0,0,0,0},
            {0,0,0x63,0x77,0x7F,0x6B,0x63,0x63,0x63,0,0,0,0,0,0,0},
            {0,0,0x66,0x76,0x7E,0x6E,0x66,0x66,0x66,0,0,0,0,0,0,0},
            {0,0,0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0,0,0,0,0,0,0},
            // P-Z (0x50-0x5A)
            {0,0,0x7C,0x66,0x66,0x7C,0x60,0x60,0x60,0,0,0,0,0,0,0},
            {0,0,0x3C,0x66,0x66,0x66,0x6E,0x3C,0x06,0,0,0,0,0,0,0},
            {0,0,0x7C,0x66,0x66,0x7C,0x78,0x6C,0x66,0,0,0,0,0,0,0},
            {0,0,0x3C,0x66,0x70,0x3C,0x0E,0x66,0x3C,0,0,0,0,0,0,0},
            {0,0,0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0,0,0,0,0,0,0},
            {0,0,0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0,0,0,0,0,0,0},
            {0,0,0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0,0,0,0,0,0,0},
            {0,0,0x63,0x63,0x63,0x6B,0x7F,0x36,0x22,0,0,0,0,0,0,0},
            {0,0,0x66,0x66,0x3C,0x18,0x3C,0x66,0x66,0,0,0,0,0,0,0},
            {0,0,0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0,0,0,0,0,0,0},
            // Z
            {0,0,0x7E,0x06,0x0C,0x18,0x30,0x60,0x7E,0,0,0,0,0,0,0},
            // [
            {0,0,0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0,0,0,0,0,0,0},
            // \
            {0,0,0x40,0x60,0x30,0x18,0x0C,0x06,0x03,0,0,0,0,0,0,0},
            // ]
            {0,0,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0,0,0,0,0,0,0},
            // ^
            {0,0,0x18,0x3C,0x66,0,0,0,0,0,0,0,0,0,0,0},
            // _
            {0,0,0,0,0,0,0,0,0x7E,0,0,0,0,0,0,0},
            // `
            {0,0,0x18,0x0C,0,0,0,0,0,0,0,0,0,0,0,0},
            // a-z
            {0,0,0,0,0x3C,0x06,0x3E,0x66,0x3E,0,0,0,0,0,0,0},
            {0,0,0x60,0x60,0x7C,0x66,0x66,0x66,0x7C,0,0,0,0,0,0,0},
            {0,0,0,0,0x3C,0x66,0x60,0x66,0x3C,0,0,0,0,0,0,0},
            {0,0,0x06,0x06,0x3E,0x66,0x66,0x66,0x3E,0,0,0,0,0,0,0},
            {0,0,0,0,0x3C,0x66,0x7E,0x60,0x3C,0,0,0,0,0,0,0},
            {0,0,0x0E,0x18,0x3E,0x18,0x18,0x18,0x18,0,0,0,0,0,0,0},
            {0,0,0,0,0x3E,0x66,0x66,0x3E,0x06,0x66,0x3C,0,0,0,0,0},
            {0,0,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0,0,0,0,0,0,0},
            {0,0,0x18,0,0x38,0x18,0x18,0x18,0x3C,0,0,0,0,0,0,0},
            {0,0,0x0C,0,0x1C,0x0C,0x0C,0x0C,0x6C,0x6C,0x38,0,0,0,0,0},
            {0,0,0x60,0x60,0x6C,0x78,0x70,0x78,0x6C,0,0,0,0,0,0,0},
            {0,0,0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0,0,0,0,0,0,0},
            {0,0,0,0,0x36,0x7F,0x6B,0x63,0x63,0,0,0,0,0,0,0},
            {0,0,0,0,0x7C,0x66,0x66,0x66,0x66,0,0,0,0,0,0,0},
            {0,0,0,0,0x3C,0x66,0x66,0x66,0x3C,0,0,0,0,0,0,0},
            {0,0,0,0,0x7C,0x66,0x66,0x7C,0x60,0x60,0,0,0,0,0,0},
            {0,0,0,0,0x3E,0x66,0x66,0x3E,0x06,0x06,0,0,0,0,0,0},
            {0,0,0,0,0x7C,0x66,0x60,0x60,0x60,0,0,0,0,0,0,0},
            {0,0,0,0,0x3E,0x60,0x3C,0x06,0x7C,0,0,0,0,0,0,0},
            {0,0,0x18,0x18,0x7E,0x18,0x18,0x18,0x0E,0,0,0,0,0,0,0},
            {0,0,0,0,0x66,0x66,0x66,0x66,0x3E,0,0,0,0,0,0,0},
            {0,0,0,0,0x66,0x66,0x66,0x3C,0x18,0,0,0,0,0,0,0},
            {0,0,0,0,0x63,0x63,0x6B,0x7F,0x36,0,0,0,0,0,0,0},
            {0,0,0,0,0x66,0x3C,0x18,0x3C,0x66,0,0,0,0,0,0,0},
            {0,0,0,0,0x66,0x66,0x66,0x3E,0x0C,0x78,0,0,0,0,0,0},
            // z
            {0,0,0,0,0x7E,0x0C,0x18,0x30,0x7E,0,0,0,0,0,0,0},
            // {
            {0,0,0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0,0,0,0,0,0,0},
            // |
            {0,0,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0,0,0,0,0,0,0},
            // }
            {0,0,0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0,0,0,0,0,0,0},
            // ~
            {0,0,0x73,0x5B,0,0,0,0,0,0,0,0,0,0,0,0},
        };

        for (int ch = 0; ch < 95; ch++) {
            int gx = (ch % cols) * glyph_w;
            int gy = (ch / cols) * glyph_h;
            for (int row = 0; row < glyph_h; row++) {
                uint8_t bits = glyph[ch][row];
                for (int col = 0; col < glyph_w; col++) {
                    int px = gx + col, py = gy + row;
                    int pi = (py * tw + px) * 4;
                    bool on = (bits >> (glyph_w - 1 - col)) & 1;
                    pixels[pi+0] = on ? 255 : 0;
                    pixels[pi+1] = on ? 255 : 0;
                    pixels[pi+2] = on ? 255 : 0;
                    pixels[pi+3] = on ? 255 : 0;
                }
            }
        }

        glGenTextures(1, (GLuint*)&tex_id);
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        delete[] pixels;
        return tex_id;
    }

    void draw_text(Renderer& r, float x, float y, const char* text, uint32_t color = 0xFFFFFFFF,
                   float scale = 1.0f) {
        if (!tex_id) return;
        float cw = glyph_w * scale, ch = glyph_h * scale;
        float tcw = 1.0f / cols;
        float tch = 1.0f / 16.0f; // 16 rows
        for (const char* p = text; *p; p++) {
            int idx = *p - 0x20;
            if (idx < 0 || idx >= 95) idx = 0;
            float u0 = (idx % cols) * tcw;
            float v0 = (idx / cols) * tch;
            r.draw_sprite(tex_id, x, y, cw, ch, u0, v0, u0 + tcw, v0 + tch, color,
                          BlendMode::Normal, FilterMode::Point);
            x += cw;
        }
    }

    float text_width(const char* text, float scale = 1.0f) {
        return strlen(text) * glyph_w * scale;
    }
};

// ─── Main ────────────────────────────────────────────────────────────────────

enum class AppState { MENU, STAGE_PLAYING, STAGE_CLEAR, QUIT };

int main(int argc, char* argv[]) {
    const char* game_path = "/home/levzzz/Games/TH10 - Mountain of Faith";

    // Open th10.dat
    char dat_path[512];
    snprintf(dat_path, sizeof(dat_path), "%s/th10.dat", game_path);
    DatArchive dat(dat_path);
    if (!dat.open()) { fprintf(stderr, "Cannot open %s\n", dat_path); return 1; }

    // Renderer
    Renderer renderer;
    if (!renderer.init(GAME_WIDTH, GAME_HEIGHT, "TH10: Mountain of Faith")) return 1;

    // Font
    Font font;
    font.build();

    // Load ANM textures
    AnmLoader anm_player(&renderer);
    AnmLoader anm_enemy(&renderer);
    AnmLoader anm_font(&renderer);
    anm_player.load("/home/levzzz/Games/th10Decomp/extracted/th10_dat/pl00.anm");
    anm_enemy.load("/home/levzzz/Games/th10Decomp/extracted/th10_dat/enemy.anm");
    printf("Textures: player=%zu enemy=%zu\n",
           anm_player.textures().size(), anm_enemy.textures().size());

    // Background fallback texture
    int bg_tex = 0;
    {
        glGenTextures(1, (GLuint*)&bg_tex);
        glBindTexture(GL_TEXTURE_2D, bg_tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        uint8_t bg[64*64*4];
        for (int y = 0; y < 64; y++)
            for (int x = 0; x < 64; x++) {
                int i = (y*64+x)*4;
                float fx = x/64.0f, fy = y/64.0f;
                bg[i+0] = (uint8_t)(20 + 30*fx + 10*fy);
                bg[i+1] = (uint8_t)(10 + 15*fx + 5*fy);
                bg[i+2] = (uint8_t)(40 + 20*fy);
                bg[i+3] = 255;
            }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, bg);
    }

    // Game state
    auto* gs = new GameStateManager();
    gs->gameoverFlag = -1;
    gs->activeScene = -1;
    gs->flagFF = 0xFF;
    Entity* player = nullptr;
    Entity* enemy  = nullptr;

    // ECL
    auto ecl_data = dat.read_file("stage01.ecl");
    EclFile ecl; ecl.open(ecl_data);
    EclVM vm; vm.load(&ecl);

    // Stage
    StageEntry stageTable[STAGE_ENTRY_COUNT];
    InitStageTable(stageTable);
    StageScriptVM stageVM;
    StageFlowController stageFlow;

    // Menu
    MenuStateMachine menu;
    menu.init();

    // Game state vars
    uint32_t score = 0, high_score = 5000000;
    int lives = 3, bombs = 3, power = 100, fps_count = 0;
    float graze = 0;

    AppState app = AppState::MENU;
    bool running = true;
    SDL_Event event;
    uint32_t frame = 0;

    while (running) {
        uint32_t now = SDL_GetTicks();
        bool z_pressed = false, esc_pressed = false;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_z || event.key.keysym.sym == SDLK_RETURN) z_pressed = true;
                if (event.key.keysym.sym == SDLK_ESCAPE) esc_pressed = true;
            }
        }

        const uint8_t* kb = SDL_GetKeyboardState(nullptr);

        switch (app) {
        case AppState::MENU: {
            renderer.begin_frame();
            renderer.clear(0x08, 0x0A, 0x20);

            // Draw tiled background
            for (int ty = 0; ty < GAME_HEIGHT; ty += 64)
                for (int tx = 0; tx < GAME_WIDTH; tx += 64) {
                    float alpha = 0.15f + 0.05f * sinf((tx + ty + frame*0.5f) * 0.01f);
                    uint8_t a = (uint8_t)(alpha * 255);
                    renderer.draw_sprite(bg_tex, (float)tx, (float)ty, 64, 64, 0,0,1,1,
                                         0x01010101 | (a << 24),
                                         BlendMode::Normal, FilterMode::Linear);
                }

            // Title
            font.draw_text(renderer, GAME_WIDTH/2 - font.text_width("TH10")/2, 30,
                          "TH10", 0xFFFFD700, 3.0f);
            font.draw_text(renderer, GAME_WIDTH/2 - font.text_width("Mountain of Faith")/2, 80,
                          "Mountain of Faith", 0xFFFFFFFF, 1.5f);
            font.draw_text(renderer, GAME_WIDTH/2 - font.text_width("Decompilation Project")/2, 110,
                          "Decompilation Project", 0xFF808080, 1.0f);

            // Menu items
            struct { const char* label; int y; } items[] = {
                {"Start Game",    200},
                {"Practice",      240},
                {"Replay",        280},
                {"Options",       320},
                {"Exit",          360},
            };

            int cursor = 0;
            float pulse = 0.5f + 0.5f * sinf(frame * 0.1f);
            uint32_t cursor_color = (uint32_t)(0xFF * pulse) * 0x10000 +
                                     (uint32_t)(0xD7 * pulse) * 0x100 +
                                     (uint32_t)(0x00 * pulse);

            for (int i = 0; i < 5; i++) {
                uint32_t col = (i == cursor) ? 0xFFFFD700 : 0xFFC0C0C0;
                if (i == cursor) {
                    font.draw_text(renderer, 180, (float)items[i].y, ">", cursor_color, 1.2f);
                    font.draw_text(renderer, 200, (float)items[i].y, items[i].label, 0xFFFFD700, 1.2f);
                } else {
                    font.draw_text(renderer, 200, (float)items[i].y, items[i].label, 0xFFC0C0C0, 1.0f);
                }
            }

            // Footer
            font.draw_text(renderer, GAME_WIDTH/2 - font.text_width("Press Z to select  ESC to quit")/2,
                          GAME_HEIGHT - 30, "Press Z to select  ESC to quit", 0xFF606060, 0.8f);

            // Handle input
            menu.update(kb, z_pressed, esc_pressed);

            if (!menu.is_active()) { running = false; }
            if (menu.wants_to_play()) {
                printf("Starting stage...\n");
                app = AppState::STAGE_PLAYING;

                if (!player) { player = AllocEntity(gs); if (player) LinkEntity(gs, player); }
                if (player) {
                    player->entityType = (int)EntityType::Player;
                    player->posX = GAME_WIDTH/2.0f; player->posY = GAME_HEIGHT-80.0f;
                    player->renderFlags = RENDER_VISIBLE;
                }
                if (!enemy) { enemy = AllocEntity(gs); if (enemy) LinkEntity(gs, enemy); }
                if (enemy) {
                    enemy->entityType = (int)EntityType::Enemy;
                    enemy->posX = GAME_WIDTH/2.0f; enemy->posY = 120.0f;
                    enemy->renderFlags = RENDER_VISIBLE;
                    enemy->halfW = 32; enemy->halfH = 32;
                }
                vm.load(&ecl); vm.execute(2);
                score = 0; lives = 3; bombs = 3; power = 100; graze = 0;
            }

            renderer.end_frame();
            break;
        }

        case AppState::STAGE_PLAYING: {
            // Input
            if (player) {
                float spd = 5.0f;
                if (kb[SDL_SCANCODE_UP])    player->posY -= spd;
                if (kb[SDL_SCANCODE_DOWN])  player->posY += spd;
                if (kb[SDL_SCANCODE_LEFT])  player->posX -= spd;
                if (kb[SDL_SCANCODE_RIGHT]) player->posX += spd;
                player->posX = std::max(16.0f, std::min(GAME_WIDTH-16.0f, player->posX));
                player->posY = std::max(32.0f, std::min(GAME_HEIGHT-16.0f, player->posY));
                score += 10;
            }

            if (esc_pressed) { app = AppState::MENU; menu.init(); break; }

            stageFlow.update();
            vm.tick();

            renderer.begin_frame();
            renderer.clear(0x00, 0x10, 0x30);

            // Background
            for (int ty = 0; ty < GAME_HEIGHT; ty += 64)
                for (int tx = 0; tx < GAME_WIDTH; tx += 64) {
                    float a = 0.3f;
                    renderer.draw_sprite(bg_tex, (float)tx, (float)ty, 64, 64, 0,0,1,1,
                                         (uint32_t)(a*255) << 24, BlendMode::Normal, FilterMode::Linear);
                }

            // Enemy
            if (enemy && !anm_enemy.textures().empty()) {
                auto& et = anm_enemy.textures()[0];
                if (et.gl_texture_id && !et.frames.empty()) {
                    enemy->posX = vm.pos_x(); enemy->posY = vm.pos_y();
                    int fi = (frame/8) % (int)et.frames.size();
                    auto& f = et.frames[fi];
                    float w = (f.u1-f.u0)*et.width, h = (f.v1-f.v0)*et.height;
                    renderer.draw_sprite(et.gl_texture_id,
                                         enemy->posX-w/2, enemy->posY-h/2, w, h,
                                         f.u0,f.v0,f.u1,f.v1, 0xFFFFFFFF,
                                         BlendMode::Normal, FilterMode::Linear);
                }
            }

            // Player
            if (player && !anm_player.textures().empty()) {
                auto& pt = anm_player.textures()[0];
                if (pt.gl_texture_id && !pt.frames.empty()) {
                    int fi = (frame/6) % (int)pt.frames.size();
                    auto& f = pt.frames[fi];
                    float w = (f.u1-f.u0)*pt.width, h = (f.v1-f.v0)*pt.height;
                    renderer.draw_sprite(pt.gl_texture_id,
                                         player->posX-w/2, player->posY-h/2, w, h,
                                         f.u0,f.v0,f.u1,f.v1, 0xFFFFFFFF,
                                         BlendMode::Normal, FilterMode::Linear);
                    // Hitbox
                    renderer.draw_sprite(bg_tex,
                                         player->posX-2.5f, player->posY-2.5f, 5, 5,
                                         0,0,1,1, 0x80FFFFFF, BlendMode::Additive, FilterMode::Linear);
                }
            }

            // HUD
            char hud[128];
            int hud_y = 4;
            snprintf(hud, sizeof(hud), "Score:%08d", score);
            font.draw_text(renderer, 8, hud_y, hud, 0xFFFFFFFF, 0.8f);
            hud_y += 18;
            snprintf(hud, sizeof(hud), "Lives:%d  Bombs:%d  Power:%d.%02d", lives, bombs, power/100, power%100);
            font.draw_text(renderer, 8, hud_y, hud, 0xFFFFFFFF, 0.8f);

            // FPS
            snprintf(hud, sizeof(hud), "FPS:%d", fps_count);
            font.draw_text(renderer, GAME_WIDTH - font.text_width(hud, 0.7f) - 8,
                          GAME_HEIGHT - 20, hud, 0x80FFFFFF, 0.7f);

            renderer.end_frame();
            break;
        }

        case AppState::STAGE_CLEAR:
        case AppState::QUIT:
        default:
            running = false;
            break;
        }

        frame++;
        if ((frame % 60) == 0) {
            static uint32_t lf = 0, lt = 0;
            if (lt == 0) { lf = frame; lt = SDL_GetTicks(); }
            else {
                float dt = (SDL_GetTicks() - lt) / 1000.0f;
                fps_count = (int)((frame - lf) / dt);
                lf = frame; lt = SDL_GetTicks();
            }
        }

        uint32_t elapsed = SDL_GetTicks() - now;
        if (elapsed < 16) SDL_Delay(16 - elapsed);
    }

    if (player) UnlinkEntity(gs, player);
    if (enemy) UnlinkEntity(gs, enemy);
    renderer.shutdown();
    dat.close();
    delete gs;
    return 0;
}
