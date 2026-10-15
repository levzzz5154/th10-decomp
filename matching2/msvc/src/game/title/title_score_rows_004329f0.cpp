// 0x004329F0: draw the title's high score table for one character.
//
// Ten rows fade from white to grey down the table. A row with a recorded date
// shows it together with the stage reached and the slowdown rate; an empty
// row shows placeholders. The play count, total play time and clear count for
// the selected difficulty follow below the table.
//
// Native LTCG passes the menu in EDI and the text position to the formatter
// in EBX.
//
// Source shapes the retail bytes depend on: the single-case switch, the
// position declared ahead of the selected difficulty, the shade defined ahead
// of the rank, and the dated row reaching its date through a table pointer
// while every other access spells out the whole path.
#include "th10/game/title_draw.hpp"

#pragma code_seg(".text$06scores")
int TitleDrawView::DrawScoreRows() {
    switch (phase) {
    case 2: {
        Vec3_00401530 position = {48.0f, 160.0f, 0.0f};
        int selected = difficulty;
        g_ascii_manager->current_64 = 1;
        if (!spell_page) {
            for (int row = 0; row < 10; ++row) {
                int shade = 0xFF - row * 0x10;
                int rank = row + 1;
                g_ascii_manager->current_4c = 0xFF0000FF | ((shade << 8 | shade) << 8);
                if (data_0047783c[cursor].table.rows[selected][row].date != 0) {
                    ScoreTable_004329f0* table = &data_0047783c[cursor].table;
                    tm* date = localtime(&table->rows[selected][row].date);
                    AsciiManager_AddFormatted(
                        g_ascii_manager, &position,
                        "%2d  %s  %9ld%d  %.4d/%.2d/%.2d %.2d:%.2d  %s  %2.1f%%", rank,
                        data_0047783c[cursor].table.rows[selected][row].name,
                        data_0047783c[cursor].table.rows[selected][row].score,
                        data_0047783c[cursor].table.rows[selected][row].continues,
                        date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour,
                        date->tm_min, data_0047471c[data_0047783c[cursor].table.rows[selected][row].stage],
                        data_0047783c[cursor].table.rows[selected][row].slowdown);
                } else {
                    AsciiManager_AddFormatted(
                        g_ascii_manager, &position,
                        "%2d  %s  %9ld%d  ----/--/-- --:--  Stage -  ---%%", rank,
                        data_0047783c[cursor].table.rows[selected][row].name,
                        data_0047783c[cursor].table.rows[selected][row].score,
                        data_0047783c[cursor].table.rows[selected][row].continues,
                        data_0047783c[cursor].table.rows[selected][row].slowdown);
                }
                position.y += 18.0f;
            }
        }
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        position.x = 328.0f;
        position.y = 378.0f;
        AsciiManager_AddFormatted(g_ascii_manager, &position, "    %5d", data_0047783c[cursor].play_count);
        position.y = 396.0f;
        AsciiManager_AddFormatted(g_ascii_manager, &position, "%3d:%.2d:%.2d",
                                 data_0047783c[cursor].play_time / 216000,
                                 data_0047783c[cursor].play_time / 3600 % 60,
                                 data_0047783c[cursor].play_time / 60 % 60);
        position.y = 414.0f;
        AsciiManager_AddFormatted(g_ascii_manager, &position, "    %5d",
                                 data_0047783c[cursor].clear_count[selected]);
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        g_ascii_manager->current_64 = 0;
        break;
    }
    }
    return 1;
}
#pragma code_seg()
