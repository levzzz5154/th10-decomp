#ifndef TH10_GAME_SCORE_TABLE_INSERT_00421FA0_HPP
#define TH10_GAME_SCORE_TABLE_INSERT_00421FA0_HPP
#include <stddef.h>

#pragma pack(push, 1)
// One line of a high-score table.
struct ScoreRecord2 {
    int score;                    // +0x00
    unsigned char stage;          // +0x04
    unsigned char suffix;         // +0x05: the digit printed after the score
    char name[9];                 // +0x06
    unsigned char reserved_0f;
    int time;                     // +0x10
    float slow_rate;              // +0x14: percent of frames lost
};

// Frame statistics at *0x00477708.
struct FrameCounters {
    unsigned char reserved_00[0x24];
    double slow_frames;           // +0x24
    double frames;                // +0x2C
};
#pragma pack(pop)

// The running game's counters at 0x00474C44. It is one object whose address
// is taken elsewhere, so stores through other pointers make the compiler
// reload its fields.
struct GameCounters2 {
    int score;                    // 0x00474C44
    unsigned char reserved_04[0x20];
    int character;                // 0x00474C68
    int shot_type;                // 0x00474C6C
    int reserved_2c;
    int difficulty;               // 0x00474C74
    int reserved_34;
    int stage;                    // 0x00474C7C
    int stage_shown;              // 0x00474C80: the stage the stage table is set to
    unsigned char reserved_40[0xC];
    unsigned char suffix;         // 0x00474C90
};
typedef char GameCountersSuffixOffset[offsetof(GameCounters2, suffix) == 0x4C ? 1 : -1];

// The high-score tables of one character and shot type: ten records per
// difficulty.
struct ScoreTable {
    unsigned char reserved_00[0x10];
    ScoreRecord2 records[5][10];   // +0x10

    // 0x00421FA0: enter the current score; returns its rank or -1.
    __declspec(noinline) int InsertScore();
};
typedef char ScoreRecordSize[sizeof(ScoreRecord2) == 0x18 ? 1 : -1];

extern "C" GameCounters2 g_globals_score;
extern "C" FrameCounters* g_fps;
extern "C" int __cdecl time2(int* out);

#endif
