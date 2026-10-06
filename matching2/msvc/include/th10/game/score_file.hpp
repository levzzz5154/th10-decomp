#pragma once

// scoreth10.dat: an LZSS-compressed, encrypted stream of tagged sections.
// Each section starts with a 16-byte header; its checksum is the byte sum of
// everything after the first eight bytes.

enum {
    SCORE_FILE_MAGIC = 0x30314854,     // "TH10"
    SCORE_SECTION_RECORDS = 0x5243,    // "CR": one per player shot type
    SCORE_SECTION_SETTINGS = 0x5453,   // "ST"
    SCORE_RECORD_COUNT = 7,
    SCORE_DIFFICULTY_COUNT = 5,
    SCORE_RANKS_PER_DIFFICULTY = 10,
    SCORE_SPELL_COUNT = 110
};

struct ScoreFileHeader {
    unsigned int magic;                 // +0x00: SCORE_FILE_MAGIC
    unsigned int reserved_04;
    unsigned short version;             // +0x08: 3
    unsigned short reserved_0a;
    unsigned int flags;                 // +0x0C
    unsigned int compressed_size;       // +0x10
    unsigned int decompressed_size;     // +0x14
    // +0x18: encrypted, compressed section stream
};

struct ScoreSectionHeader {
    unsigned short tag;                 // +0x00
    unsigned short version;             // +0x02
    unsigned int checksum;              // +0x04: byte sum of [+0x08, size)
    unsigned int size;                  // +0x08: whole section, header included
};

struct ScoreRankEntry {
    int score;                          // +0x00
    unsigned char stage;                // +0x04
    unsigned char continues;            // +0x05
    char name[9];                       // +0x06
    unsigned char reserved_0f;
    int date;                           // +0x10
    float slowdown;                     // +0x14
};

// A card's capture and attempt counts. The title's spell list hands the pair
// to its text formatter as one by-value object.
struct ScoreSpellCounts {
    int captures;
    int attempts;
};

struct ScoreSpellRecord {
    char name[0x80];                    // +0x00
    union {
        struct {
            int captures;               // +0x80
            int attempts;               // +0x84
        };
        ScoreSpellCounts counts;        // +0x80
    };
    int spell_id;                       // +0x88
    int difficulty;                     // +0x8C
};

// One "CR" section per shot type.
struct ScoreRecordSection {
    ScoreSectionHeader header;          // +0x000
    int shot_type;                      // +0x00C: index into the manager's records
    ScoreRankEntry ranks[SCORE_DIFFICULTY_COUNT][SCORE_RANKS_PER_DIFFICULTY];  // +0x010
    unsigned char reserved_4c0[0xDC];
    ScoreSpellRecord spells[SCORE_SPELL_COUNT];  // +0x59C
};

struct ScoreSettingsSection {
    ScoreSectionHeader header;
    unsigned char payload[0x448 - sizeof(ScoreSectionHeader)];
};

// Global score manager (0x0047783C).
struct ScoreManager {
    ScoreFileHeader* file;              // +0x00000: raw file image, later a fresh header
    unsigned char* sections;            // +0x00004: decompressed section stream
    ScoreRecordSection records[SCORE_RECORD_COUNT];  // +0x00008
    ScoreSettingsSection settings;      // +0x1D86C
};

extern "C" const signed char g_spell_difficulty[SCORE_SPELL_COUNT];  // 0x004743C0

typedef char ScoreRankEntrySizeCheck[sizeof(ScoreRankEntry) == 0x18 ? 1 : -1];
typedef char ScoreRecordSectionSizeCheck[sizeof(ScoreRecordSection) == 0x437C ? 1 : -1];
typedef char ScoreManagerSizeCheck[sizeof(ScoreManager) == 0x1DCB4 ? 1 : -1];

void __stdcall ScoreRecordSection_InitializeDefaults(ScoreRecordSection* section);
