// 0x00401A50 - prints the game thread's late text queue.
//
// The same loop as the main queue's draw at 0x00401760 without the small
// font and the shadow: every record is a string with a position, colour and
// scale, '\n' starts a new line 14 scaled pixels down and ' ' only advances.
// Unscaled text takes the plain quad draw and scaled text the anchored one.
//
// The receiver arrives in EBX, the batch manager goes to the flush in ESI and
// the stage camera to its apply in EDI, all from the whole-program pass, so
// this unit is compiled in the cluster layout/ltcg/anm_batch_flush_00442f50.json.
#include "th10/game/game_thread_text.hpp"

#pragma code_seg(".text$000m3late")
int GameThreadText::DrawLateRecords() {
    int in_game_view = 1;
    glyph.flags = (glyph.flags & 0xFFD7FFFFu) | 0x00140001u;
    GameThreadTextRecord* record = late_records;
    for (int i = 0; i < late_record_count; ++i, ++record) {
        glyph.base_position = record->position;
        GlyphSetScale(&glyph, record->scale_x, record->scale_y);
        float advance = glyph_advance * record->scale_x;
        const char* text = record->text;
        if (in_game_view != record->in_game_view) {
            in_game_view = record->in_game_view;
            data_00491c10->Flush();
            if (in_game_view)
                data_00491c28.SelectStage(0);
            else
                data_00491c28.SelectStage(1);
        }
        for (; *text != 0; ++text) {
            if (*text == '\n') {
                glyph.base_position.y += record->scale_y * 14.0f;
                glyph.base_position.x = record->position.x;
                continue;
            }
            if (*text == ' ') {
                glyph.base_position.x += advance;
            } else {
                glyph.texture = reinterpret_cast<RenderTexture*>(
                    &font->sprites[static_cast<unsigned char>(*text) - ' ']);
                glyph.color = record->color;
                if (glyph.scale_x != 1.0f)
                    EntityDraw_00443290(&glyph, data_00491c10);
                else
                    EntityDraw_00443080(&glyph, data_00491c10);
                glyph.base_position.x += advance;
            }
        }
    }
    if (in_game_view) {
        data_00491c10->Flush();
        data_00491c28.SelectStage(1);
    }
    return 1;
}
#pragma code_seg()
