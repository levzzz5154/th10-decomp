#pragma once

#include <cstdint>

// The retail score file is a 0x437C-byte blob:
//   +0x00  : 'CR' signature half-word, then a zero half-word
//   +0x08  : total size (0x437C)
//   +0x10  : 5 difficulty blocks x 10 high-score records, 0x18 bytes each:
//            +0x00 score, +0x04 flag byte, +0x05 shot byte,
//            +0x06 9-byte name, +0x10 time, +0x14 progress float
//   +0x624 : 22 practice/spell groups of five {id, unlock byte} pairs
//            (0x90-byte pair stride, 0x2D0-byte group stride)
//
// Both recovered functions treat the file as raw bytes so the retail
// offsets hold on the 64-bit host as well.

constexpr uint32_t kScoreFileBytes = 0x437C;
constexpr uint32_t kScoreStatsBytes = 0x448;

struct ScoreArchiveLoadState {
    uint8_t* packed;
    uint8_t* unpacked;
    uint8_t* score_sections;
    uint8_t* stats_section;
};

struct ScoreArchiveLoadHooks {
    void (*decrypt)(uint8_t* data, uint32_t size, uint8_t key,
                    uint8_t step, uint32_t length);
    void (*decompress)(const uint8_t* source, uint32_t source_size,
                       uint8_t* destination, uint32_t destination_size);
    void* (*allocate)(uint32_t size);
    void (*free_memory)(void* memory);
};

// 0x0042B030 - Validate and unpack a TH10 score archive, copying valid
// checksummed CR sections into their indexed 0x437C-byte slots and the ST
// section into its 0x448-byte destination. Invalid input is replaced with a
// minimal 24-byte TH10/version-3 header.
int ScoreArchive_LoadSections(ScoreArchiveLoadState* state,
                              const ScoreArchiveLoadHooks* hooks);

// 0x0042ACB0 - Reset a score file to the retail defaults: wipe the
// whole blob, write the 'CR' header, seed each difficulty with scores
// 1000000 down to 100000 under the default name, and enumerate the
// practice/spell groups from the unlock table at 0x004743BF.
void ScoreFile_InitializeDefaults(uint8_t* file);

// 0x00421FA0 - Insert the pending score (global 0x00474C44) into the
// current difficulty block (global 0x00474C74): find the first slot
// whose score is not larger, shift lower slots down, and fill the slot
// with the score, shot/stage bytes, player name, timestamp (injected
// __time32 edge), and completion ratio. Returns the slot index, or -1
// when the score does not place.
int32_t ScoreFile_InsertHighScore(uint8_t* file, int32_t (*time32)(int32_t*));
