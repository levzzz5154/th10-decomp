// 0x0042ACB0: fill one shot type's score records with their defaults.
//
// Every difficulty gets the ten placeholder ranks 1,000,000 down to 100,000
// under the name "--------", and every spell card slot gets its own index and
// the difficulty it belongs to.
#include <string.h>
#include <stddef.h>
#include "th10/game/score_file.hpp"
#pragma code_seg(".text$00b")
extern "C" void __stdcall ScoreFile_Defaults2(ScoreRecordSection *file) {
    int difficulty;
    int rank;
    int spell;

    memset(file, 0, sizeof(ScoreRecordSection));
    file->header.tag = SCORE_SECTION_RECORDS;
    file->header.version = 0;
    file->header.size = sizeof(ScoreRecordSection);
    for (difficulty = 0; difficulty < SCORE_DIFFICULTY_COUNT; difficulty++) {
        for (rank = 0; rank < SCORE_RANKS_PER_DIFFICULTY; rank++) {
            file->ranks[difficulty][rank].score = 1000000 - rank * 100000;
            file->ranks[difficulty][rank].stage = 1;
            strcpy(file->ranks[difficulty][rank].name, "--------");
            file->ranks[difficulty][rank].date = 0;
            file->ranks[difficulty][rank].continues = 0;
        }
    }
    for (spell = 0; spell < SCORE_SPELL_COUNT; spell++) {
        file->spells[spell].spell_id = spell;
        file->spells[spell].difficulty = g_spell_difficulty[spell];
    }
}
#pragma code_seg()
