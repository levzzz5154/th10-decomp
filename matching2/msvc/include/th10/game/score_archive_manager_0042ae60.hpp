#pragma once
#include <stddef.h>
#include "th10/game/score_file.hpp"
struct ScoreArchiveManager {
    ScoreFileHeader *file;
    unsigned char *sections;
    ScoreRecordSection records[7];
    ScoreSettingsSection settings;
    __declspec(noinline) ScoreArchiveManager();
    ~ScoreArchiveManager();
    __declspec(noinline) int LoadSections();
};
typedef char ScoreArchiveManager_size_check[sizeof(ScoreArchiveManager)==0x1DCB4?1:-1];
typedef char ScoreArchiveManager_records_check[offsetof(ScoreArchiveManager,records)==8?1:-1];
typedef char ScoreArchiveManager_settings_check[offsetof(ScoreArchiveManager,settings)==0x1D86C?1:-1];
