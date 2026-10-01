#include <string.h>
extern "C" unsigned char data_0046e354[];
extern "C" unsigned char data_004918b0[4], data_004918b4[4];
#pragma code_seg(".text$01b")
extern "C" void __fastcall Recovery_InitializeRandomTable_0042add0(int unused, char* table) {
    memset(table, 0, 0x448);
    *(unsigned short*)(table + 2) = 0;
    *(unsigned short*)table = 0x5453;
    *(unsigned int*)(table + 8) = 0x448;
    memcpy(table + 12, &data_0046e354, 9);
    char* out = table + 70;
    int remaining = 512;
    do {
        unsigned int value = *(unsigned int*)&data_004918b0;
        unsigned int calls=*(unsigned int*)data_004918b4;
        value ^= 0x9630;
        value -= 0x6553;
        unsigned short high = (unsigned short)value;
        high >>= 14;
        unsigned short word = (unsigned short)(high + (value << 2));
        *(unsigned short*)&data_004918b0 = word;
        *(unsigned int*)data_004918b4=calls+1;
        *(unsigned short*)out = word;
        out += 2;
        --remaining;
    } while (remaining);
}


#pragma code_seg()
