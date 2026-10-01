#include <string.h>
#include "th10/game/score_archive_manager_0042ae60.hpp"
extern "C" void *__cdecl asm_malloc_00452706(unsigned int);
extern "C" void __cdecl asm_free_00452422(void *);
unsigned char * __stdcall Dat_Decrypt(unsigned char *,int,unsigned char,unsigned char,int,int);
unsigned char *__stdcall DecompressDatLzss_00435dc0(unsigned char *,int,unsigned char *,unsigned int);
#pragma code_seg(".text$04b")
int ScoreArchiveManager_0042ae60::LoadSections() {
    if(file) {
        if(file->magic==0x30314854 && file->version==3) {
            Dat_Decrypt((unsigned char *)file+0x18,file->compressed_size,0xAC,0x35,0x10,file->compressed_size);
            unsigned char *packed=(unsigned char *)file+0x18;
            sections=(unsigned char *)asm_malloc_00452706(file->decompressed_size*4);
            DecompressDatLzss_00435dc0(packed,file->compressed_size,sections,file->decompressed_size);
            int remaining=(int)file->decompressed_size;
            unsigned char *record=sections;
            if(remaining<1) return 0;
            do {
                ScoreSectionHeader *section=(ScoreSectionHeader *)record;
                if(section->tag==0x5243) {
                    if(section->version==0) {
                        unsigned int sum=0;
                        unsigned char *bytes=record+0x0C;
                        int count=0xB3E;
                        do {
                            sum=bytes[-4]+bytes[-3]+bytes[-2]+bytes[-1]+bytes[1]+bytes[0]+sum;
                            bytes+=6;
                        } while(--count);
                        if(sum==section->checksum && section->size==0x437C)
                            memcpy((char *)this+8+*(unsigned int *)(record+0x0C)*0x437C,record,0x437C);
                    }
                } else if(section->tag==0x5453) {
                    if(section->version==0) {
                        unsigned int sum=0;
                        unsigned char *bytes=record+0x0A;
                        int count=0x110;
                        do {
                            sum=bytes[-2]+bytes[-1]+bytes[1]+bytes[0]+sum;
                            bytes+=4;
                        } while(--count);
                        if(sum==section->checksum && section->size==0x448)
                            memcpy(&settings,record,0x448);
                    }
                } else break;
                remaining-=(int)section->size;
                if(remaining<0) break;
                record+=section->size;
                if(remaining<1) return 0;
            } while(true);
        }
        if(file) { asm_free_00452422(file); file=0; }
    }
    file=(ScoreFileHeader *)asm_malloc_00452706(0x18);
    memset(file,0,0x18);
    file->magic=0x30314854;
    file->version=3;
    file->flags=0x100;
    return 0;
}
#pragma code_seg()
