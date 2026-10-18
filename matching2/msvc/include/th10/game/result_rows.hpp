#ifndef TH10_GAME_RESULT_ROWS_00422660_HPP
#define TH10_GAME_RESULT_ROWS_00422660_HPP

#include <stddef.h>
#include <time.h>

#include "th10/game/game_thread_queue_native.hpp"
#include "th10/game/title_draw.hpp"

// The result screen's menu state: the same object the name entry at
// 0x00423570 prepares. Its phase word picks which of the three row views
// this callback draws, and the replay slots it lists are the ones the run
// just filled.
struct ResultMenu {
    unsigned char reserved_00[0x04];
    int phase;                          // +0x04
    unsigned char reserved_08[0x14 - 0x08];
    int timer;                          // +0x14: frames since the view opened
    unsigned char reserved_18[0x24 - 0x18];
    int cursor;                         // +0x24: the selected row
    unsigned char reserved_28[0x1E8 - 0x28];
    int no_entry;                       // +0x1E8: the final score missed the table
    ReplayFile2* records[25];   // +0x1EC: the 25 replay slots
};

// 0x00422660: draw the result screen's rows.
extern "C" int __stdcall ResultScreen_DrawRows(ResultMenu* state);

// 0x004224C0: the name entry overlay (state, position by value; RET16).
extern "C" void __stdcall DrawNameEntry2(
    ResultMenu* state, Vec32 position);

extern "C" {
extern int g_globals_difficulty;             // the difficulty the run was played on
extern int g_globals_stage;             // the stage the run ended on
extern const char* g_difficulty_initials[];   // "E", "N", "H", "L", "X": difficulty initials
extern const char str_score_row_unplayed_format[];    // "%2d %s %.9ld%d --/--/-- Stage -"
extern const char str_score_row_format[];    // "%2d %s %.9ld%d %.2d/%.2d/%.2d %s"
extern const char str_score_ranking_title[];    // "            Score Ranking!!"
extern const char str_ranking_row_format[];    // "No.%.2d          %.2d/%.2d/%.2d %s %s %s"
extern const char str_ranking_row_empty_format[];    // "No.%.2d -------- --/--/-- ------- - St-"
extern const char str_ranking_row_named_format[];    // "No.%.2d %s %.2d/%.2d/%.2d %s %s %s"
}

// Run-selection words. Their addresses escape in the compiler context, as
// members of the global game state do in the complete program.
extern "C" int data_00474c68_shot;    // 0x00474C68
extern "C" int data_00474c68_char;    // 0x00474C6C

typedef char ResultMenu_phase_is_04[offsetof(ResultMenu, phase) == 0x04 ? 1 : -1];
typedef char ResultMenu_timer_is_14[offsetof(ResultMenu, timer) == 0x14 ? 1 : -1];
typedef char ResultMenu_cursor_is_24[offsetof(ResultMenu, cursor) == 0x24 ? 1 : -1];
typedef char ResultMenu_no_entry_is_1e8[offsetof(ResultMenu, no_entry) == 0x1E8 ? 1 : -1];
typedef char ResultMenu_records_is_1ec[offsetof(ResultMenu, records) == 0x1EC ? 1 : -1];

#endif
