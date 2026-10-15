// 0x00421FA0..0x004220DB: enter the current score into a high-score table.
//
// The table (in EDI) holds ten descending records per difficulty. The first
// record the current score reaches or beats gives the rank; with none the
// result is -1. The records from there down move one place, and the freed one
// gets the score, its suffix digit and stage, the current time, a blank name
// and the share of slowed-down frames in percent. Returns the rank.
//
// Every statement indexes the table with the difficulty again: the counters
// at 0x00474C44 are one address-taken object, so each store through the table
// makes the compiler reload it, as retail does.
#include "th10/game/score_table_insert_00421fa0.hpp"

extern "C" char* __cdecl strcpy(char* destination, const char* source);
#pragma intrinsic(strcpy)

#pragma code_seg(".text$00421fa0_fn")
int ScoreTable_00421fa0::InsertScore() {
    int rank;
    for (rank = 0; rank < 10; ++rank) {
        if (records[g_globals_score.difficulty][rank].score <= g_globals_score.score)
            break;
    }
    if (rank >= 10)
        return -1;
    for (int place = 9; place > rank; --place)
        records[g_globals_score.difficulty][place] = records[g_globals_score.difficulty][place - 1];
    records[g_globals_score.difficulty][rank].score = g_globals_score.score;
    records[g_globals_score.difficulty][rank].suffix = g_globals_score.suffix;
    records[g_globals_score.difficulty][rank].stage = (unsigned char)g_globals_score.stage;
    time_00452b71(&records[g_globals_score.difficulty][rank].time);
    strcpy(records[g_globals_score.difficulty][rank].name, "        ");
    records[g_globals_score.difficulty][rank].slow_rate =
        100.0f - (float)(g_fps->slow_frames / g_fps->frames) * 100.0f;
    return rank;
}
#pragma code_seg()
