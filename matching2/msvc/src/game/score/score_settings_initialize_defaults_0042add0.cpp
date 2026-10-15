// 0x0042ADD0: initialize the score settings section and its 512 random words.
// The actual constructor passes one section pointer; native LTCG keeps it in EDX.
#include <string.h>
extern "C" unsigned char g_score_blank_string[];
extern "C" unsigned char g_rng[4], g_rng_generation[4];
#pragma code_seg(".text$01b")
extern "C" void __stdcall Recovery_InitializeRandomTable(char* table) {
    memset(table, 0, 0x448);
    *(unsigned short*)(table + 2) = 0;
    *(unsigned short*)table = 0x5453;
    *(unsigned int*)(table + 8) = 0x448;
    memcpy(table + 12, &g_score_blank_string, 9);
    char* out = table + 70;
    int remaining = 512;
    do {
        unsigned int value = *(unsigned int*)&g_rng;
        unsigned int calls = *(unsigned int*)g_rng_generation;
        value ^= 0x9630;
        value -= 0x6553;
        unsigned short high = (unsigned short)value;
        high >>= 14;
        unsigned short word = (unsigned short)(high + (value << 2));
        *(unsigned short*)&g_rng = word;
        *(unsigned int*)g_rng_generation = calls + 1;
        *(unsigned short*)out = word;
        out += 2;
        --remaining;
    } while (remaining);
}

#pragma code_seg()
