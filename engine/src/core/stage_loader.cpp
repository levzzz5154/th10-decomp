#include "th10/stage_loader.h"
#include <cstring>
#include <cstdio>

namespace th10 {

// ========================================
// Hardcoded path strings for stage entries
// ========================================

static char kStdPath00[] = "stage00.std";
static char kStdPath01[] = "stage01.std";
static char kStdPath02[] = "stage02.std";
static char kStdPath03[] = "stage03.std";
static char kStdPath04[] = "stage04.std";
static char kStdPath05[] = "stage05.std";
static char kStdPath06[] = "stage06.std";
static char kStdPath07[] = "stage07.std";

static char kAnmPath00[] = "stgenm00.anm";
static char kAnmPath01[] = "stgenm01.anm";
static char kAnmPath02[] = "stgenm02.anm";
static char kAnmPath03[] = "stgenm03.anm";
static char kAnmPath04[] = "stgenm04.anm";
static char kAnmPath05[] = "stgenm05.anm";
static char kAnmPath06[] = "stgenm06.anm";
static char kAnmPath07[] = "stgenm07.anm";

static char kEclPath00[] = "stage00.ecl";
static char kEclPath01[] = "stage01.ecl";
static char kEclPath02[] = "stage02.ecl";
static char kEclPath03[] = "stage03.ecl";
static char kEclPath04[] = "stage04.ecl";
static char kEclPath05[] = "stage05.ecl";
static char kEclPath06[] = "stage06.ecl";
static char kEclPath07[] = "stage07.ecl";

static char kBgm00_0[] = "bgm/th10_02.wav";
static char kBgm00_1[] = "bgm/th10_03.wav";
static char kBgm01_0[] = "bgm/th10_04.wav";
static char kBgm01_1[] = "bgm/th10_05.wav";
static char kBgm02_0[] = "bgm/th10_06.wav";
static char kBgm02_1[] = "bgm/th10_07.wav";
static char kBgm03_0[] = "bgm/th10_08.wav";
static char kBgm03_1[] = "bgm/th10_09.wav";
static char kBgm04_0[] = "bgm/th10_10.wav";
static char kBgm04_1[] = "bgm/th10_11.wav";
static char kBgm05_0[] = "bgm/th10_12.wav";
static char kBgm05_1[] = "bgm/th10_13.wav";
static char kBgm06_0[] = "bgm/th10_14.wav";
static char kBgm06_1[] = "bgm/th10_14.wav";
static char kBgm07_0[] = "bgm/th10_15.wav";
static char kBgm07_1[] = "bgm/th10_15.wav";

static char kMsg00_0[] = "st00_00.msg";
static char kMsg00_1[] = "st00_01.msg";
static char kMsg01_0[] = "st01_00.msg";
static char kMsg01_1[] = "st01_01.msg";
static char kMsg02_0[] = "st02_00.msg";
static char kMsg02_1[] = "st02_01.msg";
static char kMsg03_0[] = "st03_00.msg";
static char kMsg03_1[] = "st03_01.msg";
static char kMsg04_0[] = "st04_00.msg";
static char kMsg04_1[] = "st04_01.msg";
static char kMsg05_0[] = "st05_00.msg";
static char kMsg05_1[] = "st05_01.msg";
static char kMsg06_0[] = "st06_00.msg";
static char kMsg06_1[] = "st06_01.msg";
static char kMsg07_0[] = "st07_00.msg";
static char kMsg07_1[] = "st07_01.msg";

static char kLogo00[] = "st00logo.anm";
static char kLogo01[] = "st01logo.anm";
static char kLogo02[] = "st02logo.anm";
static char kLogo03[] = "st03logo.anm";
static char kLogo04[] = "st04logo.anm";
static char kLogo05[] = "st05logo.anm";
static char kLogo06[] = "st06logo.anm";
static char kLogo07[] = "st07logo.anm";

// Stage path lookup table (indexed by stage ID)
struct StagePathStrings {
    const char* stdPath;
    const char* anmPath;
    const char* eclPath;
    const char* bgmPath0;
    const char* bgmPath1;
    const char* msgPath0;
    const char* msgPath1;
    const char* logoAnimPath;
};

static const StagePathStrings kStagePaths[STAGE_ENTRY_COUNT] = {
    { kStdPath00, kAnmPath00, kEclPath00, kBgm00_0, kBgm00_1, kMsg00_0, kMsg00_1, kLogo00 },
    { kStdPath01, kAnmPath01, kEclPath01, kBgm01_0, kBgm01_1, kMsg01_0, kMsg01_1, kLogo01 },
    { kStdPath02, kAnmPath02, kEclPath02, kBgm02_0, kBgm02_1, kMsg02_0, kMsg02_1, kLogo02 },
    { kStdPath03, kAnmPath03, kEclPath03, kBgm03_0, kBgm03_1, kMsg03_0, kMsg03_1, kLogo03 },
    { kStdPath04, kAnmPath04, kEclPath04, kBgm04_0, kBgm04_1, kMsg04_0, kMsg04_1, kLogo04 },
    { kStdPath05, kAnmPath05, kEclPath05, kBgm05_0, kBgm05_1, kMsg05_0, kMsg05_1, kLogo05 },
    { kStdPath06, kAnmPath06, kEclPath06, kBgm06_0, kBgm06_1, kMsg06_0, kMsg06_1, kLogo06 },
    { kStdPath07, kAnmPath07, kEclPath07, kBgm07_0, kBgm07_1, kMsg07_0, kMsg07_1, kLogo07 },
};

void InitStageTable(StageEntry* table) {
    if (!table) return;

    for (int i = 0; i < STAGE_ENTRY_COUNT; i++) {
        table[i].stageId     = i;
        table[i].stdPathOff  = i;
        table[i].anmPathOff  = i;
        table[i].eclPathOff  = i;
        table[i].bgmPath0Off = i;
        table[i].bgmPath1Off = i;
        table[i].msgPath0Off = i;
        table[i].msgPath1Off = i;
        table[i].logoAnimOff = i;
        table[i].flags0      = 0;
        table[i].flags1      = 0;
        table[i].flags2      = 0;
    }

    printf("[StageLoader] Initialized %d stage entries\n", STAGE_ENTRY_COUNT);
}

// Resolve offset to actual string pointer via the path table
static const StagePathStrings* ResolveEntry(const StageEntry* entry) {
    int idx = entry->stageId;
    if (idx < 0 || idx >= STAGE_ENTRY_COUNT) return nullptr;
    return &kStagePaths[idx];
}

const char* StageEntry_GetStdPath(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->stdPath : nullptr;
}

const char* StageEntry_GetAnmPath(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->anmPath : nullptr;
}

const char* StageEntry_GetEclPath(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->eclPath : nullptr;
}

const char* StageEntry_GetBgmPath0(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->bgmPath0 : nullptr;
}

const char* StageEntry_GetBgmPath1(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->bgmPath1 : nullptr;
}

const char* StageEntry_GetMsgPath0(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->msgPath0 : nullptr;
}

const char* StageEntry_GetMsgPath1(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->msgPath1 : nullptr;
}

const char* StageEntry_GetLogoAnimPath(const StageEntry* entry) {
    auto* p = ResolveEntry(entry);
    return p ? p->logoAnimPath : nullptr;
}

bool LoadStdFile(StdHeader* hdr, const uint8_t* data, size_t size) {
    if (!hdr || !data || size < sizeof(StdHeader)) {
        fprintf(stderr, "[StageLoader] STD data too small: %zu bytes (need >= %zu)\n",
                size, sizeof(StdHeader));
        return false;
    }

    memcpy(hdr, data, sizeof(StdHeader));

    if (hdr->magic != 0x00100003) {
        fprintf(stderr, "[StageLoader] Invalid STD magic: 0x%08X (expected 0x00100003)\n",
                hdr->magic);
        return false;
    }

    bool valid = true;
    for (int i = 0; i < 6; i++) {
        if (hdr->validation[i] >= 2) {
            fprintf(stderr, "[StageLoader] Validation byte %d out of range: %d (must be < 2)\n",
                    i, hdr->validation[i]);
            valid = false;
        }
    }

    if (!valid) return false;

    printf("[StageLoader] STD file loaded: magic=0x%08X, config=%zu bytes\n",
           hdr->magic, sizeof(hdr->stage_config));
    return true;
}

} // namespace th10
