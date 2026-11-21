#pragma once
#include "score_table_insert.hpp"

struct PracticeScore {
    unsigned char reserved_00[5];
    unsigned char unlocked;
    unsigned char reserved_06[2];
};

// One character and shot type's high scores, clear counts and practice unlocks.
struct TitleShotScore {
    unsigned char reserved_0000[8];
    ScoreTable table;                  // +0x008
    unsigned char reserved_04c8[8];
    int clears[5];                     // +0x4D0, by difficulty
    PracticeScore practice[5][6];      // by difficulty and stage
    unsigned char reserved_05d4[0x437C - 0x5D4];
};

struct TitleScoreFile {
    TitleShotScore shots[2][3];
    unsigned char reserved_194e8[0x1D878 - 0x194E8];
    char last_name[9];
    unsigned char reserved_1d881[7];
    unsigned char cleared[2][3];
};

typedef char TitleShotScoreSize[sizeof(TitleShotScore) == 0x437C ? 1 : -1];
typedef char TitleClearCountsOffset[offsetof(TitleShotScore, clears) == 0x4D0 ? 1 : -1];
typedef char TitleLastNameOffset[offsetof(TitleScoreFile, last_name) == 0x1D878 ? 1 : -1];
typedef char TitleClearedShotsOffset[offsetof(TitleScoreFile, cleared) == 0x1D888 ? 1 : -1];

extern "C" TitleScoreFile* g_score;
