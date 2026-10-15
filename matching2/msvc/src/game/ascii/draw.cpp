// The ASCII manager's draw tasks and the two string-queue printers, compiled
// in the anm_batch_flush native-LTCG cluster with the quad batch.
#include "th10/game/ascii_manager.hpp"

// 0x00401520 - scheduler callback that prints the ASCII manager's late string
// queue. The task's context arrives in ECX and is handed to the draw at
// 0x00401A50, whose whole-program convention takes it in EBX.

#pragma code_seg(".text$000lb1task")
int __fastcall AsciiManager_OnDrawLate(AsciiManager* thread) {
    return thread->DrawLateRecords();
}
#pragma code_seg()

// 0x00401760 - prints the ASCII manager's main string queue.
//
// Every record is a string with a position, colour and scale. Characters are
// drawn one sprite at a time: '\n' starts a new line and ' ' only advances.
// A record picks one of two fonts (the small one has a fixed 7-pixel advance
// and 9-pixel lines) and may ask for a shadow, which is the same glyph drawn
// first two pixels down and right in black at half the alpha. A record also
// chooses the render stage it is drawn in, so the batch is flushed and the
// stage reselected whenever that changes; the second stage is restored
// before returning.
//
// The batch manager goes to the flush in ESI, the stage camera to its apply
// in EDI and the glyph to the quad draw in ESI, all from the whole-program
// pass, so this unit is compiled in the cluster
// layout/ltcg/anm_batch_flush_00442f50.json.

#pragma code_seg(".text$000m1records")
int __stdcall AsciiManager_DrawStrings(AsciiManager* thread) {
    int in_game_view = 1;
    thread->glyph.flags = (thread->glyph.flags & 0xFFD7FFFFu) | 0x00140001u;
    AsciiString* record = thread->records;
    for (int i = 0; i < thread->record_count; ++i, ++record) {
        thread->glyph.base_position = record->position;
        GlyphSetScale(&thread->glyph, record->scale_x, record->scale_y);
        const char* text = record->text;
        float advance;
        float line_height;
        if (record->font == 1) {
            advance = 7.0f;
            line_height = 9.0f;
        } else {
            advance = thread->glyph_advance * record->scale_x;
            line_height = 14.0f;
        }
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
                thread->glyph.base_position.y += line_height * record->scale_y;
                thread->glyph.base_position.x = record->position.x;
                continue;
            }
            if (*text == ' ') {
                thread->glyph.base_position.x += advance;
            } else {
                thread->glyph.texture = reinterpret_cast<RenderTexture*>(&thread->font->sprites[
                    record->font * 0x62 + static_cast<unsigned char>(*text) - ' ']);
                GlyphSetSpriteSize(&thread->glyph,
                    reinterpret_cast<AsciiFontSprite*>(thread->glyph.texture)->width,
                    reinterpret_cast<AsciiFontSprite*>(thread->glyph.texture)->height);
                if (record->shadow) {
                    thread->glyph.color = record->color & 0xFF000000u;
                    reinterpret_cast<unsigned char*>(&thread->glyph.color)[3] = (record->color >> 24) / 2;
                    thread->glyph.base_position.x += 2.0f;
                    thread->glyph.base_position.y += 2.0f;
                    EntityDraw_00443080(&thread->glyph, data_00491c10);
                    thread->glyph.base_position.x -= 2.0f;
                    thread->glyph.base_position.y -= 2.0f;
                }
                thread->glyph.color = record->color;
                EntityDraw_00443080(&thread->glyph, data_00491c10);
                thread->glyph.base_position.x += advance;
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

// 0x00401A50 - prints the ASCII manager's late string queue.
//
// The same loop as the main queue's draw at 0x00401760 without the small
// font and the shadow: every record is a string with a position, colour and
// scale, '\n' starts a new line 14 scaled pixels down and ' ' only advances.
// Unscaled text takes the plain quad draw and scaled text the anchored one.
//
// The receiver arrives in EBX, the batch manager goes to the flush in ESI and
// the stage camera to its apply in EDI, all from the whole-program pass, so
// this unit is compiled in the cluster layout/ltcg/anm_batch_flush_00442f50.json.

#pragma code_seg(".text$000m3late")
int AsciiManager::DrawLateRecords() {
    int in_game_view = 1;
    glyph.flags = (glyph.flags & 0xFFD7FFFFu) | 0x00140001u;
    AsciiString* record = late_records;
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
