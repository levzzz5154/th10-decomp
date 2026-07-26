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

uint16_t ReadU16(const uint8_t* bytes) {
    uint16_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

uint32_t ReadU32(const uint8_t* bytes) {
    uint32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteU16(uint8_t* bytes, uint16_t value) {
    memcpy(bytes, &value, sizeof(value));
}

void WriteU32(uint8_t* bytes, uint32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

uint32_t ByteSum(const uint8_t* bytes, uint32_t size) {
    uint32_t sum = 0;
    for (uint32_t index = 0; index < size; ++index) sum += bytes[index];
    return sum;
}

}  // namespace

// 0x0042B030 - Decode the outer TH10 container and accept individually
// checksummed CR (score) and ST (statistics) sections. The retail routine
// silently skips corrupt sections but replaces a malformed outer container
// with a fresh minimal header.
int ScoreArchive_LoadSections(ScoreArchiveLoadState* state,
                              const ScoreArchiveLoadHooks* hooks) {
    uint8_t* packed = state->packed;
    if (packed != 0 && ReadU32(packed) == 0x30314854u &&
        ReadU16(packed + 8) == 3) {
        const uint32_t packed_size = ReadU32(packed + 0x10);
        const uint32_t unpacked_words = ReadU32(packed + 0x14);
        // Retail: sub_44B0D0(172, packed + 0x18, packed_size, 53, 16,
        // packed_size), whose parameters are (key, data, size, step, block,
        // limit). The key is 172 and the step is 53; the 16 is the block
        // size, which the hook fixes. This previously passed 53 as the key
        // and 16 as the step, so the container never decoded and every score
        // section failed its checksum.
        hooks->decrypt(packed + 0x18, packed_size, 172, 53, packed_size);
        state->unpacked =
            static_cast<uint8_t*>(hooks->allocate(unpacked_words * 4));
        hooks->decompress(packed + 0x18, packed_size, state->unpacked,
                          unpacked_words);

        uint32_t remaining = unpacked_words;
        const uint8_t* section = state->unpacked;
        while (remaining != 0) {
            if (remaining < 12) break;
            const uint32_t section_size = ReadU32(section + 8);
            if (section_size < 12 || section_size > remaining) break;
            const uint16_t kind = ReadU16(section);
            const uint16_t version = ReadU16(section + 2);
            const uint32_t checksum = ReadU32(section + 4);
            if (version == 0 && checksum == ByteSum(section + 8,
                                                    section_size - 8)) {
                if (kind == 0x5243 && section_size == kScoreFileBytes) {
                    const uint32_t slot = ReadU32(section + 12);
                    memcpy(state->score_sections + slot * kScoreFileBytes,
                           section, kScoreFileBytes);
                } else if (kind == 0x5453 &&
                           section_size == kScoreStatsBytes) {
                    memcpy(state->stats_section, section, kScoreStatsBytes);
                }
            }
            remaining -= section_size;
            section += section_size;
        }
        return 0;
    }

    if (packed != 0) hooks->free_memory(packed);
    state->packed = static_cast<uint8_t*>(hooks->allocate(0x18));
    memset(state->packed, 0, 0x18);
    WriteU32(state->packed, 0x30314854u);
    WriteU16(state->packed + 8, 3);
    WriteU32(state->packed + 0x0C, 0x100);
    return 0;
}

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
