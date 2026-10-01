#include <string.h>
#include "th10/game/score_file.hpp"
extern "C" char data_0046e858[9];
extern "C" const signed char data_004743bf[111];
#pragma code_seg(".text$00b")
extern "C" __declspec(noinline) void __stdcall ScoreFile_Defaults_0042acb0(ScoreRecordSection *file) {
    memset(file,0,0x437C);
    file->header.tag=0x5243;
    file->header.version=0;
    file->header.size=0x437C;
    unsigned char *entry=(unsigned char *)file+0x14;
    for(int stage=5; stage>0; --stage) {
        int score=1000000;
        do {
            *(int *)(entry-4)=score;
            *entry=1;
            memcpy(entry+2,data_0046e858,9);
            *(int *)(entry+12)=0;
            entry[1]=0;
            score-=100000;
            entry+=0x18;
        } while(score>0);
    }
    unsigned char *sub=(unsigned char *)file+0x624;
    int base=0,second=1,third=3;
    do {
        *(int *)(sub+0x000)=base;
        *(int *)(sub+0x004)=data_004743bf[second];
        *(int *)(sub+0x090)=second;
        *(int *)(sub+0x094)=g_spell_difficulty[second];
        *(int *)(sub+0x120)=third-1;
        *(int *)(sub+0x124)=data_004743bf[third];
        *(int *)(sub+0x1B0)=third;
        *(int *)(sub+0x1B4)=g_spell_difficulty[third];
        *(int *)(sub+0x240)=base+4;
        *(int *)(sub+0x244)=g_spell_difficulty[base+4];
        second+=5; base+=5; third+=5; sub+=0x2D0;
    } while(second<0x6F);
}
#pragma code_seg()
