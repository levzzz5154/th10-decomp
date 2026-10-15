// 0x00422660: draw the result screen's rows.
//
// After a run the pause layer's task callback reaches this routine every
// frame with the result menu. It marks the game thread busy, then draws one
// of three views chosen by the phase word: the 25 replay slots (phase 10 or
// 17), the replay just played with the name entry overlay (11 or 18), or the
// score ranking of the run's character with the new record highlighted (12
// or 19). Rows queue at 15 or 18 pixel pitch, the selected row draws in the
// highlight color, and the busy flag drops again on the way out.
//
// Native LTCG passes the text position to the formatter in EBX; the complete
// formatter and queue writer are part of this same translation unit so the
// compiler derives the retail private call ABI on its own.
#include "../../../build_support/layout/ltcg/result_rows_00422660/formatted.cpp"
#include "../../../build_support/layout/ltcg/result_rows_00422660/append.cpp"
#include "th10/game/result_rows_00422660.hpp"

#pragma code_seg(".text$04rows")
extern "C" __declspec(noinline) int __stdcall ResultScreen_DrawRows_00422660(
        ResultMenu_00422660* state) {
    g_ascii_manager->current_64 = 1;
    switch (state->phase) {
    case 10:
    case 17: {
        // The 25 replay slots, one line each; the chosen row is highlighted
        // and a filled slot shows its record's name, date and run summary.
        Vec3_00401530 position = {48.0f, 64.0f, 0.0f};
        for (int row = 0; row < 25; ++row) {
            g_ascii_manager->current_4c = state->cursor == row ? 0xFFFFFF00 : 0xFF808080;
            ReplayFile_00431ba0* file = state->records[row];
            if (file) {
                ReplayHeader_00431ba0* header = file->header;
                tm* date = localtime(&header->date);
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position, str_ranking_row_named_format, row + 1, header->name,
                    date->tm_year % 100, date->tm_mon + 1, date->tm_mday,
                    g_shot_names[header->character * 3 + header->shot_type],
                    g_difficulty_initials[header->difficulty], g_stage_names_short[header->stage]);
            } else {
                AsciiManager_AddFormatted(g_ascii_manager, &position, str_ranking_row_empty_format, row + 1);
            }
            position.y += 15.0f;
        }
        g_ascii_manager->current_4c = -1;
        break;
    }
    case 11:
    case 18: {
        // The replay just played: the name entry overlay slides up from its
        // row to the top over ten frames, then the record's date line shows.
        Vec3_00401530 position;
        position.z = 0.0f;
        int cursor = state->cursor;
        if (state->timer < 10) {
            float settled = cursor * 15.0f + 64.0f;
            position.y = settled + (224.0f - settled) * state->timer * 0.1f;
        } else {
            position.y = 224.0f;
        }
        position.x = 102.0f;
        DrawNameEntry_004224c0(state, position);
        position.x = 48.0f;
        ReplayHeader_00431ba0* header = g_replay->header;
        tm* date = localtime(&header->date);
        AsciiManager_AddFormatted(
            g_ascii_manager, &position, str_ranking_row_format, cursor + 1,
            date->tm_year % 100, date->tm_mon + 1, date->tm_mday,
            g_shot_names[header->character * 3 + header->shot_type],
            g_difficulty_initials[header->difficulty], g_stage_names_short[g_globals_stage]);
        break;
    }
    case 12:
    case 19: {
        // The score ranking: a header, the name entry drawn over the row the
        // new record landed in when it reached the table, then the ten rows.
        Vec3_00401530 position;
        position.x = 48.0f;
        position.z = 0.0f;
        int cursor = state->cursor;
        position.y = 64.0f;
        AsciiManager_AddFormatted(g_ascii_manager, &position, str_score_ranking_title);
        position.x = 75.0f;
        position.y = cursor * 18.0f + 96.0f;
        if (state->no_entry == 0) {
            DrawNameEntry_004224c0(state, position);
        } else {
            cursor = -1;
        }
        position.x = 48.0f;
        position.y = 96.0f;
        for (int row = 0; row < 10; ++row) {
            g_ascii_manager->current_4c = row == cursor ? 0xFFFFFF00 : 0xFF808080;
            if (g_score[data_00474c68_shot * 3 + data_00474c68_char]
                    .table.rows[g_globals_difficulty][row].date != 0) {
                ScoreTable_004329f0* table =
                    &g_score[data_00474c68_shot * 3 + data_00474c68_char].table;
                tm* date = localtime(&table->rows[g_globals_difficulty][row].date);
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position, str_score_row_format, row + 1,
                    g_score[data_00474c68_shot * 3 + data_00474c68_char]
                        .table.rows[g_globals_difficulty][row].name,
                    g_score[data_00474c68_shot * 3 + data_00474c68_char]
                        .table.rows[g_globals_difficulty][row].score,
                    g_score[data_00474c68_shot * 3 + data_00474c68_char]
                        .table.rows[g_globals_difficulty][row].continues,
                    date->tm_year % 100, date->tm_mon + 1, date->tm_mday,
                    g_stage_names_long[g_score[data_00474c68_shot * 3 + data_00474c68_char]
                                      .table.rows[g_globals_difficulty][row].stage]);
            } else {
                AsciiManager_AddFormatted(
                    g_ascii_manager, &position, str_score_row_unplayed_format, row + 1,
                    g_score[data_00474c68_shot * 3 + data_00474c68_char]
                        .table.rows[g_globals_difficulty][row].name,
                    g_score[data_00474c68_shot * 3 + data_00474c68_char]
                        .table.rows[g_globals_difficulty][row].score,
                    g_score[data_00474c68_shot * 3 + data_00474c68_char]
                        .table.rows[g_globals_difficulty][row].continues);
            }
            position.y += 18.0f;
        }
        g_ascii_manager->current_4c = -1;
        break;
    }
    }
    g_ascii_manager->current_64 = 0;
    return 1;
}
#pragma code_seg()
