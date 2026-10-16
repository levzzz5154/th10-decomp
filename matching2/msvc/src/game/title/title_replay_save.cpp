// 0x00433B30: draw the replay save page.
//
// The list phase shows the 25 replay slots. Once a slot is chosen its line
// slides down to the name entry row, now describing the replay about to be
// saved, and the name typed so far, its underscore cursor and the character
// grid are drawn below it.
//
// The menu arrives on the stack; native LTCG passes the text position to the
// formatter in EBX.
//
// As on the high score name entry page, the grid is drawn by separate calls
// for the letters and for the three trailing symbols.
#include <string.h>

#include "th10/game/title_draw.hpp"

extern "C" int __stdcall TitleMenu_DrawReplaySave2(TitleDrawView* menu);

#pragma code_seg(".text$09save")
extern "C" __declspec(noinline) int __stdcall TitleMenu_DrawReplaySave2(
        TitleDrawView* menu) {
    switch (menu->phase) {
    case 3: {
        Vec32 position = {58.0f, 240.0f, 0.0f};
        int slot = menu->selected_replay;
        if (menu->phase_frames < 10)
            position.y = (10.0f - menu->phase_elapsed) * ((slot * 15 + 80) - 240.0f) * 0.1f + 240.0f;
        ReplayHeader5* header = g_replay->header;
        tm* date = localtime(&header->date);
        AsciiManager_AddFormatted(
            g_ascii_manager, &position, "No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%",
            slot + 1, "        ", date->tm_year % 100, date->tm_mon + 1, date->tm_mday,
            date->tm_hour, date->tm_min,
            g_shot_names[header->character * 3 + header->shot_type],
            g_difficulty_names[header->difficulty], g_stage_names_short[8], header->slowdown);
        if (menu->phase_frames >= 10) {
            int count = strlen(g_name_entry_grid);
            position.x = 112.0f;
            position.y = 240.0f;
            position.z = 0.0f;
            g_ascii_manager->current_4c = 0xFFFFFFFF;
            AsciiManager_AddFormatted(g_ascii_manager, &position, "%s", menu->name);
            position.x = (float)(menu->name_length * 9) + 112.0f;
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
    case 2: {
        Vec32 position = {58.0f, 80.0f, 0.0f};
        g_ascii_manager->current_64 = 1;
        for (int slot = 0; slot < 25; ++slot) {
            g_ascii_manager->current_4c = menu->cursor == slot ? 0xFFFFFF00 : 0xFF808080;
            if (menu->replays[slot]) {
                ReplayHeader5* header = menu->replays[slot]->header;
                tm* date = localtime(&header->date);
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position,
                    "No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%", slot + 1,
                    header->name, date->tm_year % 100, date->tm_mon + 1, date->tm_mday,
                    date->tm_hour, date->tm_min,
                    g_shot_names[header->character * 3 + header->shot_type],
                    g_difficulty_names[header->difficulty], g_stage_names_short[header->stage],
                    header->slowdown);
            } else {
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position,
                    "No.%.2d -------- --/--/-- --:-- ------- ------- --- ---%%", slot + 1);
            }
            position.y += 15.0f;
        }
        break;
    }
    default:
        return 1;
    }
    g_ascii_manager->current_4c = 0xFFFFFFFF;
    g_ascii_manager->current_64 = 0;
    return 1;
}
#pragma code_seg()
