#pragma once
#include <stddef.h>
#include "th10/game/score_file.hpp"
struct ScoreArchiveManager_0042ae60 {
    ScoreFileHeader *file;
    unsigned char *sections;
    ScoreRecordSection records[7];
    ScoreSettingsSection settings;
    __declspec(noinline) ScoreArchiveManager_0042ae60();
    ~ScoreArchiveManager_0042ae60();
    __declspec(noinline) int LoadSections();
};
typedef char ScoreArchiveManager_size_check[sizeof(ScoreArchiveManager_0042ae60)==0x1DCB4?1:-1];
typedef char ScoreArchiveManager_records_check[offsetof(ScoreArchiveManager_0042ae60,records)==8?1:-1];
typedef char ScoreArchiveManager_settings_check[offsetof(ScoreArchiveManager_0042ae60,settings)==0x1D86C?1:-1];
