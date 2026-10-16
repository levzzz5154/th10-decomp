// 0x00433230: draw the high score name entry page.
//
// The table of the character being played is shown with the new row
// highlighted. Until the name is confirmed the name typed so far, its
// underscore cursor and the character grid (thirteen to a line) are drawn as
// well; the last three grid cells are the space, backspace and end symbols.
//
// The menu arrives on the stack; native LTCG passes the text position to the
// formatter in EBX.
//
// Source shapes the retail bytes depend on: the grid letters and the three
// trailing symbols are drawn by separate calls. With a single call the
// compiler builds an aligned EBP frame for the slowdown doubles instead of
// using EBP for the row shade and the cell count.
#include <string.h>

#include "th10/game/title_draw.hpp"

extern "C" int __stdcall TitleMenu_DrawScoreEntry2(TitleDrawView* menu);

#pragma code_seg(".text$08entry")
extern "C" __declspec(noinline) int __stdcall TitleMenu_DrawScoreEntry2(
        TitleDrawView* menu) {
    switch (menu->phase) {
    case 2: {
        Vec32 position = {48.0f, 160.0f, 0.0f};
        int selected = g_globals_character.difficulty;
        g_ascii_manager->current_64 = 1;
        for (int row = 0; row < 10; ++row) {
            int shade = 0xFF - row * 0x10;
            int rank = row + 1;
            if (menu->name_confirmed)
                g_ascii_manager->current_4c = 0xFF0000FF | ((shade << 8 | shade) << 8);
            else
                g_ascii_manager->current_4c = menu->cursor != row ? 0xFF404040 : 0xFFFFFFFF;
            if (g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                    .table.rows[selected][row].date != 0) {
                ScoreTable2* table =
                    &g_score[g_globals_character.character + g_globals_character.shot_type * 3].table;
                tm* date = localtime(&table->rows[selected][row].date);
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position,
                    "%2d  %s  %9ld%d  %.4d/%.2d/%.2d %.2d:%.2d  %s  %2.1f%%", rank,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].name,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].score,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].continues,
                    date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour,
                    date->tm_min,
                    g_stage_names_long[g_score[g_globals_character.character +
                                                g_globals_character.shot_type * 3]
                                      .table.rows[selected][row].stage],
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].slowdown);
            } else {
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position,
                    "%2d  %s  %9ld%d  ----/--/-- --:--  Stage -  ---%%", rank,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].name,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].score,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].continues,
                    g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                        .table.rows[selected][row].slowdown);
            }
            position.y += 18.0f;
        }
        if (!menu->name_confirmed) {
            int count = strlen(g_name_entry_grid);
            position.x = 84.0f;
            position.y = menu->cursor * 18.0f + 160.0f;
            position.z = 0.0f;
            g_ascii_manager->current_4c = 0xFFFFFFFF;
            AsciiManager_AddFormatted(g_ascii_manager, &position, "%s", menu->name);
            position.x = (float)(menu->name_length * 9) + 84.0f;
            if (menu->name_length == 8)
                position.x -= 9.0f;
            g_ascii_manager->current_4c = 0xFFFFFF00;
            AsciiManager_AddFormatted(g_ascii_manager, &position, "_");
            g_ascii_manager->current_4c = 0xFFFFFFFF;
            position.x = 212.0f;
            position.y = 360.0f;
            position.z = 0.0f;
            for (int cell = 0; cell < count; ++cell) {
                g_ascii_manager->current_4c = menu->name_cell == cell ? 0xFFFFFF00 : 0xFF808080;
                if (cell < count - 3)
                    AsciiManager_AddFormatted(g_ascii_manager, &position, "%c",
                                             g_name_entry_grid[cell]);
                else
                    AsciiManager_AddFormatted(
                        g_ascii_manager, &position, "%c",
                        cell == count - 3 ? 0x81 : cell == count - 2 ? 0x7F : 0x80);
                if ((unsigned int)cell % 13 == 12) {
                    position.x = 212.0f;
                    position.y += 16.0f;
                } else {
                    position.x += 18.0f;
                }
            }
            g_ascii_manager->current_4c = 0xFFFFFFFF;
        }
        break;
    }
    }
    return 1;
}
#pragma code_seg()
