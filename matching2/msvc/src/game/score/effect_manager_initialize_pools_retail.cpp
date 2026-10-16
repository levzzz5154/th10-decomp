// 0x0042AE60 is the score manager constructor, despite its historical filename.
#include <string.h>
#include "th10/game/score_archive_manager.hpp"
char* __stdcall Archive_LoadFile(const char*,int*,int);
extern "C" char str_score_file[];
extern "C" void __stdcall Recovery_InitializeRandomTable(char *);
extern "C" void __stdcall ScoreFile_Defaults2(ScoreRecordSection *);
#pragma code_seg(".text$02b")
ScoreArchiveManager::ScoreArchiveManager() {
    memset(this, 0, sizeof(*this));
    int file_size;
    file = (ScoreFileHeader *)Archive_LoadFile(str_score_file, &file_size, 1);
    Recovery_InitializeRandomTable((char *)&settings);
    ScoreRecordSection *record = records;
    while ((unsigned int)(((char *)record - (char *)this - 8) / 0x437C) < 7) {
        ScoreFile_Defaults2(record);
        ++record;
    }
    LoadSections();
}
#pragma code_seg()

// Complete original allocating caller and private compiler-visible helpers.
#include "score_manager_create.cpp"

#include "../../../build_support/layout/ltcg/score_manager_dependencies/decrypt.cpp"
#include "../../../build_support/layout/ltcg/score_manager_dependencies/archive_load.cpp"
