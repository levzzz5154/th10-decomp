#pragma once
#include <stddef.h>
#include "th10/game/replay_stage_begin_0042a6a0.hpp"
#include "th10/game/replay_pool_append_0042aa50.hpp"

// The 0x24-byte replay file header, as the save routine stamps it.
struct ReplaySaveHeader {
    unsigned int magic;              // +0x00: "t10r"
    short version;                   // +0x04: 5
    unsigned char reserved_06[6];
    int packed_end;                  // +0x0C: header size plus the packed stream size
    unsigned char reserved_10[0x0C];
    int packed_size;                 // +0x1C
    int size;                        // +0x20: the unpacked size
};
typedef char ReplaySaveHeader_size[sizeof(ReplaySaveHeader) == 0x24 ? 1 : -1];

// The 0x64-byte summary block at the head of the unpacked replay.
struct ReplaySaveSummary {
    char name[8];                    // +0x00: the player name, space padded
    unsigned char reserved_08[4];
    int date;                        // +0x0C: when the run started
    int score;                       // +0x10
    unsigned char reserved_14[0x34];
    float slow_rate;                 // +0x48
    int stage_count;                 // +0x4C: how many stages have pool data
    int character;                   // +0x50
    int shot_type;                   // +0x54
    int difficulty;                  // +0x58
    int stage_reached;               // +0x5C
    unsigned char reserved_60[4];
};
typedef char ReplaySaveSummary_size[sizeof(ReplaySaveSummary) == 0x64 ? 1 : -1];

// The replay manager, as far as the save routine touches it.
struct ReplaySaveManager {
    unsigned char reserved_00[0x14];
    ReplaySaveHeader* header;       // +0x14
    ReplaySaveSummary* summary;     // +0x18
    ReplayStage_0042a6a0* stage_data[8];     // +0x1C
    ReplayPoolLink_0042aa50 pools[8];        // +0x3C: the stage pool lists

    // 0x00429B60: write the recorded replay into replay/<file_name>; the
    // player name arrives on the stack, the file name in EDX. Always
    // returns 0.
    int __fastcall Save(const char* file_name, const char* name);
};

// One aligned "USER" chunk appended after the packed replay stream.
struct ReplayUserChunk {
    unsigned int magic;                      // +0x00: "USER"
    unsigned int size;                       // +0x04: chunk bytes including this header
    unsigned char flag;                      // +0x08: 0 = header info, 1 = comment notice
    unsigned char reserved_09[3];
    char text[0xFFF0];                       // +0x0C
};
