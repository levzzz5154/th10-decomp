#include "th10/game/floating_text_draw.hpp"

namespace {

const int kTextRecordCount = 723;
const unsigned int kPreserveAlphaBlend = 4;
const float kScreenOffsetX = 224.0f;
const float kScreenOffsetY = 16.0f;

int GlyphIndex(int mode, int character) {
    if (mode < 52 || character == 10) {
        return character + 196;
    }
    if (mode < 56) {
        return character + 207;
    }
    return character + 217;
}

unsigned char DistanceAlpha(float dx, float dy) {
    const int distance_squared = static_cast<int>(dx * dx + dy * dy);
    if (distance_squared <= 1024) {
        return 80;
    }
    if (distance_squared <= 4096) {
        return static_cast<unsigned char>(
            (distance_squared - 1024) * 128 / 3072 + 80);
    }
    return 208;
}

}  // namespace

// 0x0042B780 - Draw every active text record from its final character back to
// its first, applying mode-dependent spacing, glyph-bank selection, and player
// distance alpha.
int TextBatch_DrawReverseGlyphs(
        const FloatingTextRecord records[kTextRecordCount],
        const FloatingTextEnv* env) {
    if (!(env->view_flags & kPreserveAlphaBlend) &&
        *env->alpha_blend_state) {
        env->disable_alpha_blend();
        *env->alpha_blend_state = 0;
    }

    for (int record_index = 0;
         record_index < kTextRecordCount; ++record_index) {
        const FloatingTextRecord& record = records[record_index];
        if (!record.active) {
            continue;
        }

        const float spacing =
            record.mode >= 8 ? 8.0f : 8.0f / record.divisor;
        float x = record.x - record.count * spacing * 0.5f +
                  kScreenOffsetX;
        const float y = record.y + kScreenOffsetY;
        const float dx = env->player_position[0] - record.x;
        const float dy = env->player_position[1] - record.y;
        const unsigned char alpha = DistanceAlpha(dx, dy);

        for (int character_index = record.count - 1;
             character_index >= 0; --character_index) {
            const int character = record.text[character_index];
            FloatingGlyphDraw glyph = {
                x,
                y,
                record.color,
                alpha,
                GlyphIndex(record.mode, character)
            };
            env->draw_glyph(&glyph);
            x += spacing;
        }
    }
    return 1;
}
