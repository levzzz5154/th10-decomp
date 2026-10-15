// 0x00431BA0: draw the title's replay browser.
//
// The list page shows the 25 replay slots, one line each. The detail page
// shows the chosen replay's line sliding up to the top and then the stages it
// can be started from, each with the score the player entered it with.
//
// The menu arrives on the stack; native LTCG passes the text position to the
// formatter in EBX.
#include "th10/game/title_draw.hpp"

extern "C" int __stdcall TitleMenu_DrawReplayBrowser_00431ba0(TitleDrawView* menu);

#pragma code_seg(".text$05s_browser")
extern "C" __declspec(noinline) int __stdcall TitleMenu_DrawReplayBrowser_00431ba0(
        TitleDrawView* menu) {
    switch (menu->phase) {
    case 4: {
        ReplayHeader_00431ba0* header = menu->replays[menu->selected_replay]->header;
        Vec3_00401530 position = {80.0f, 80.0f, 0.0f};
        if (menu->phase_frames < 10)
            position.y = (10.0f - menu->phase_elapsed) * (menu->selected_replay * 15) * 0.1f + 80.0f;
        g_ascii_manager->current_64 = 1;
        tm* date = localtime(&header->date);
        AsciiManager_AddFormatted(
            g_ascii_manager, &position, "No.%.2d %s %.2d/%.2d/%.2d %.2d:%.2d %s %s %s %2.1f%%",
            menu->selected_replay + 1, header->name, date->tm_year % 100, date->tm_mon + 1,
            date->tm_mday, date->tm_hour, date->tm_min,
            g_shot_names[header->character * 3 + header->shot_type],
            g_difficulty_names[header->difficulty], g_stage_names_short[header->stage], header->slowdown);
        if (menu->phase_frames >= 10) {
            position.x = 220.0f;
            position.y = 128.0f;
            for (int stage = 1; stage < 8; ++stage) {
                g_ascii_manager->current_4c = menu->cursor == stage - 1 ? 0xFFFFFF00 : 0xFF808080;
                if (!menu->replays[menu->selected_replay]->stages[stage].data) {
                    AsciiManager_AddFormatted(g_ascii_manager, &position, "%s  ---------",
                                             g_stage_names_long[stage]);
                } else if (stage < 6 &&
                           menu->replays[menu->selected_replay]->stages[stage + 1].data) {
                    ReplayStage_00431ba0* next =
                        menu->replays[menu->selected_replay]->stages[stage + 1].data;
                    AsciiManager_AddFormatted(g_ascii_manager, &position, "%s  %.8d%d",
                                             g_stage_names_long[stage], next->score, next->value_1b4);
                } else {
                    AsciiManager_AddFormatted(g_ascii_manager, &position, "%s  %.8d%d",
                                             g_stage_names_long[stage], header->score,
                                             header->final_value_60);
                }
                position.y += 18.0f;
            }
        }
        break;
    }
    case 2: {
        Vec3_00401530 position = {58.0f, 80.0f, 0.0f};
        g_ascii_manager->current_64 = 1;
        for (int slot = 0; slot < 25; ++slot) {
            g_ascii_manager->current_4c = menu->cursor == slot ? 0xFFFFFF00 : 0xFF808080;
            if (menu->replays[slot]) {
                ReplayHeader_00431ba0* header = menu->replays[slot]->header;
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
