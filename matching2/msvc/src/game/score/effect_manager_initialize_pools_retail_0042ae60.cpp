// 0x0042AE60 is the score manager constructor, despite its historical filename.
#include <string.h>
#include "th10/game/score_archive_manager_0042ae60.hpp"
char* __stdcall Archive_LoadFile(const char*,int*,int);
extern "C" char data_0046e848[];
extern "C" void __stdcall Recovery_InitializeRandomTable_0042add0(char *);
extern "C" void __stdcall ScoreFile_Defaults_0042acb0(ScoreRecordSection *);
#pragma code_seg(".text$02b")
ScoreArchiveManager_0042ae60::ScoreArchiveManager_0042ae60() {
    memset(this, 0, sizeof(*this));
    int file_size;
    file = (ScoreFileHeader *)Archive_LoadFile(data_0046e848, &file_size, 1);
    Recovery_InitializeRandomTable_0042add0((char *)&settings);
    ScoreRecordSection *record = records;
    while ((unsigned int)(((char *)record - (char *)this - 8) / 0x437C) < 7) {
        ScoreFile_Defaults_0042acb0(record);
        ++record;
    }
    LoadSections();
}
#pragma code_seg()

// Complete original allocating caller and private compiler-visible helpers.
#include "score_manager_create.cpp"

#include "../../../build_support/layout/ltcg/score_manager_dependencies/decrypt.cpp"
#include "../../../build_support/layout/ltcg/score_manager_dependencies/archive_load.cpp"
