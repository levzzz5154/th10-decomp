#include <string.h>
#include <stddef.h>
#include "th10/game/score_file.hpp"
extern "C" char data_0046e858[9];
extern "C" const signed char data_004743bf[111];
#pragma code_seg(".text$00b")
extern "C" __declspec(noinline) void __stdcall ScoreFile_Defaults_0042acb0(ScoreRecordSection *file) {
    memset(file,0,0x437C);
    file->header.tag=0x5243;
    file->header.version=0;
    file->header.size=0x437C;
    for(int difficulty=SCORE_DIFFICULTY_COUNT; difficulty>0; --difficulty) {
        for(int rank=0, score=1000000; score>0; ++rank, score-=100000) {
            ScoreRankEntry& row=file->ranks[SCORE_DIFFICULTY_COUNT-difficulty][rank];
            char* text=reinterpret_cast<char*>(&row)+offsetof(ScoreRankEntry,stage);
            row.score=score;
            text[0]=1;
            memcpy(text+2,data_0046e858,9);
            row.date=0;
            row.continues=0;
        }
    }
    for(int spell=0; spell<SCORE_SPELL_COUNT; ++spell) {
        file->spells[spell].spell_id=spell;
        file->spells[spell].difficulty=g_spell_difficulty[spell];
    }

}
#pragma code_seg()
