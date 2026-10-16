// 0x00431410: draw the six stage rows of the title's practice menu.
//
// Each row shows the stage name and, once the stage has been reached with the
// selected character and difficulty, its best practice score. The selected
// row is highlighted and blinks while the choice is being confirmed.
//
// Native LTCG passes the menu in EDI and the text position to the formatter
// in EBX.
#include "th10/game/title_draw.hpp"

#pragma code_seg(".text$05rows")
int TitleDrawView::DrawPracticeRows() {
    if (phase >= 2 && phase <= 3) {
        g_ascii_manager->current_64 = 1;
        Vec32 position = {80.0f, 80.0f, 0.0f};
        if (phase_frames >= 10 || phase == 3) {
            position.y = 216.0f;
            position.x = 168.0f;
            if (g_globals_character.shot_type != 0)
                position.x = 296.0f;
            for (int stage = 1; stage < 7; ++stage) {
                if (cursor == stage - 1) {
                    if (g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                            .practice[stage - 1 + g_globals_character.difficulty * 6].unlocked) {
                        if (phase == 3 && phase_frames % 4 >= 2)
                            g_ascii_manager->current_4c = 0xFF000000;
                        else
                            g_ascii_manager->current_4c = 0xFFFFFF00;
                    } else {
                        g_ascii_manager->current_4c = 0xFFDFDFDF;
                    }
                } else {
                    g_ascii_manager->current_4c = 0xFF808080;
                }
                if (!g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                         .practice[stage - 1 + g_globals_character.difficulty * 6].unlocked)
                    AsciiManager_AddFormatted(g_ascii_manager, &position, "%s  ---------",
                                             g_stage_names_long[stage]);
                else
                    AsciiManager_AddFormatted(
                        g_ascii_manager, &position, "%s  %.8d0", g_stage_names_long[stage],
                        g_score[g_globals_character.character + g_globals_character.shot_type * 3]
                            .practice[stage - 1 + g_globals_character.difficulty * 6].best_score);
                position.y += 18.0f;
            }
        }
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        g_ascii_manager->current_64 = 0;
    }
    return 1;
}
#pragma code_seg()
