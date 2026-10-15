// 0x0042B780: draw every active floating number (score and graze popups)
// glyph by glyph, fading the text out as it nears the player. Native LTCG
// keeps the pool in EDI and the shared glyph entity in ESI.
// 0x0042B9B0: the scheduler callback, which forwards its ECX context.
// 0x0042B9C0: start a floating number in the next ring slot. Native LTCG
// passes the value in EAX, the pool in ESI and the position in EDI; only the
// colour is on the stack.
#include "th10/game/smoll_score_draw.hpp"
#include "th10/game/player.hpp"

// Draw one number's glyphs left to right, most significant digit first.
__forceinline void SmollScoreDrawView::DrawGlyphs(const FloatingText_0042b780* text, float advance, int alpha) {
    const unsigned char* glyph = &text->glyphs[text->length - 1];
    for (int remaining = text->length; remaining > 0; remaining--, glyph--) {
        if (text->timer.current >= 52 && *glyph != 10) {
            if (text->timer.current < 56) {
                sprite.glyph = &resource->sprites[*glyph + 0xCF];
                sprite.alpha = alpha;
            } else {
                sprite.glyph = &resource->sprites[*glyph + 0xD9];
                sprite.alpha = alpha;
            }
        } else {
            sprite.glyph = &resource->sprites[*glyph + 0xC4];
            sprite.alpha = alpha;
        }
        sprite.SetWidth(sprite.glyph->width);
        FloatingText_DrawEntity_00443080(g_sprt_ctrl, &sprite);
        sprite.x += advance;
    }
}

#pragma code_seg(".text$01draw")
int SmollScoreDrawView::Draw() {
    FloatingText_0042b780* text = texts;
    int alpha;
    if (!(g_application.options & 4) && g_application.fog_dirty) {
        g_sprt_ctrl->Flush();
        g_application.fog_dirty = 0;
        g_d3d_device->State(0x1C, 0);
    }
    for (int index = 0; index < 0x2D3; index++, text++) {
        if (text->active) {
            float advance;
            if (text->timer.current < 8)
                advance = 8.0f / text->timer.elapsed;
            else
                advance = 8.0f;
            sprite.x = text->position.x - text->length * advance * 0.5f + 224.0f;
            sprite.y = text->position.y + 16.0f;
            sprite.Color() = text->color;
            float dx = g_player->position.x - text->position.x;
            float dy = g_player->position.y - text->position.y;
            int distance = int(dy * dy + dx * dx);
            if (distance > 0x1000)
                alpha = 0xD0;
            else if (distance > 0x400)
                alpha = (distance - 0x400) * 0x80 / 0xC00 + 0x50;
            else
                alpha = 0x50;
            DrawGlyphs(text, advance, alpha);
        }
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$02task")
int __fastcall SmollScore_DrawTask_0042b9b0(SmollScoreDrawView* pool) {
    return pool->Draw();
}
#pragma code_seg()

#pragma code_seg(".text$03spawn")
void SmollScoreDrawView::Spawn(int value, const FloatingTextPosition_0042b780* position, unsigned int color) {
    if (next_text >= 0x2D0) next_text = 0;
    FloatingText_0042b780* text = &texts[next_text];
    int length = 0;
    text->active = 1;
    if (value >= 0) {
        while (value != 0) {
            text->glyphs[length++] = value % 10;
            value /= 10;
        }
    } else {
        text->glyphs[0] = 10;
        length = 1;
    }
    if (length == 0) {
        text->glyphs[0] = 0;
        length = 1;
    }
    text->length = length;
    text->color = color;
    FrameTimer_Restart(&text->timer);
    text->position = *position;
    next_text++;
}
#pragma code_seg()
