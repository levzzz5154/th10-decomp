#include "th10/game/score_file.hpp"

#include <cstring>

// Default player name (9 bytes, retail 0x0046E858).
extern const char DAT_0046e858[9];
// Practice/spell unlock table (retail 0x004743BF, byte-indexed).
extern const char DAT_004743bf[];

// Pending-result globals consumed by the insert path.
extern int32_t DAT_00474c74;   // current difficulty block
extern int32_t DAT_00474c44;   // pending score
extern uint8_t DAT_00474c90;   // pending stage byte
extern int32_t DAT_00474c7c;   // pending shot/difficulty byte source
extern uint8_t DAT_0046e354[9];  // current player name
// Gameplay stats object (retail 0x00477708): doubles at +0x24 and +0x2C
// hold the remaining/total ratio for the completion percentage.
extern uint8_t* DAT_00477708;
extern double DAT_00470b44;    // completion scale constant

namespace {

int32_t ReadI32(const uint8_t* bytes) {
    int32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteI32(uint8_t* bytes, int32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

void WriteF32(uint8_t* bytes, float value) {
    memcpy(bytes, &value, sizeof(value));
}

double ReadF64(const uint8_t* bytes) {
    double value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

}  // namespace

// 0x0042ACB0 - Reset a score file to the retail defaults. The store
// order follows the retail function: full wipe, header, the five
// score blocks (scores 1000000, 900000, ..., 100000 with flag byte 1
// and the default name), then the practice/spell groups, where group k
// holds five {id = 5k + j, unlock = table[5k + j + 1]} pairs copied
// from the byte table at 0x004743BF.
void ScoreFile_InitializeDefaults(uint8_t* file) {
    memset(file, 0, kScoreFileBytes);
    file[0] = 'C';
    file[1] = 'R';
    file[2] = 0;
    file[3] = 0;
    WriteI32(file + 8, (int32_t)kScoreFileBytes);

    for (int block = 0; block < 5; ++block) {
        for (int slot = 0; slot < 10; ++slot) {
            uint8_t* record = file + 0x10 + (block * 10 + slot) * 0x18;
            WriteI32(record, 1000000 - slot * 100000);
            record[4] = 1;
            record[5] = 0;
            memcpy(record + 6, DAT_0046e858, 9);
            WriteI32(record + 0x10, 0);
        }
    }

    for (int group = 0; group < 22; ++group) {
        uint8_t* base = file + 0x624 + group * 0x2D0;
        for (int pair = 0; pair < 5; ++pair) {
            const int id = group * 5 + pair;
            WriteI32(base + pair * 0x90, id);
            WriteI32(base + pair * 0x90 + 4, (int32_t)DAT_004743bf[id + 1]);
        }
    }
}

// 0x00421FA0 - Insert the pending score into the current difficulty
// block. Retail carries the file base in EDI; the __time32 edge is
// injected so tests control the timestamp. The completion ratio is
// scale - (remaining / total) * scale with the doubles read from the
// gameplay stats object at 0x00477708.
int32_t ScoreFile_InsertHighScore(uint8_t* file, int32_t (*time32)(int32_t*)) {
    const int32_t block = DAT_00474c74;
    for (int32_t slot = 0; slot < 10; ++slot) {
        uint8_t* record = file + 0x10 + (block * 10 + slot) * 0x18;
        if (ReadI32(record) > DAT_00474c44) {
            continue;
        }
        for (int32_t moved = 9; moved > slot; --moved) {
            memcpy(file + 0x10 + (block * 10 + moved) * 0x18,
                   file + 0x10 + (block * 10 + moved - 1) * 0x18, 0x18);
        }
        WriteI32(record, DAT_00474c44);
        record[4] = (uint8_t)DAT_00474c7c;
        record[5] = DAT_00474c90;
        if (time32 != 0) {
            int32_t stamp = 0;
            time32(&stamp);
            WriteI32(record + 0x10, stamp);
        }
        memcpy(record + 6, DAT_0046e354, 9);
        const double remaining = ReadF64(DAT_00477708 + 0x24);
        const double total = ReadF64(DAT_00477708 + 0x2C);
        WriteF32(record + 0x14,
                 (float)(DAT_00470b44 - (remaining / total) * DAT_00470b44));
        return slot;
    }
    return -1;
}
