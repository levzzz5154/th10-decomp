// 0x0042B030: unpack scoreth10.dat into the manager.
//
// The file is a header followed by an encrypted, LZSS-compressed stream of
// tagged sections. Every section whose version, checksum and size are right
// replaces the manager's default one. A file with the wrong magic or version,
// an unknown section tag or a section running past the end of the stream is
// discarded as a whole. In every case the manager ends up owning a file
// header to save with: the loaded one, or a fresh empty one.
#include <string.h>
#include "th10/game/score_archive_manager_0042ae60.hpp"
extern "C" void *__cdecl asm_malloc_00452706(unsigned int);
extern "C" void __cdecl asm_free_00452422(void *);
unsigned char * __stdcall Dat_Decrypt(unsigned char *,int,unsigned char,unsigned char,int,int);
unsigned char *__stdcall DecompressDatLzss_00435dc0(unsigned char *,int,unsigned char *,unsigned int);
#pragma code_seg(".text$04b")
int ScoreArchiveManager_0042ae60::LoadSections() {
    if (file) {
        if (file->magic == SCORE_FILE_MAGIC && file->version == 3) {
            unsigned char* packed = (unsigned char*)(file + 1);
            Dat_Decrypt(packed, file->compressed_size, 0xAC, 0x35, 0x10, file->compressed_size);
            packed = (unsigned char*)(file + 1);
            sections = (unsigned char*)asm_malloc_00452706(file->decompressed_size * 4);
            DecompressDatLzss_00435dc0(packed, file->compressed_size, sections, file->decompressed_size);
            int remaining = file->decompressed_size;
            ScoreSectionHeader* section = (ScoreSectionHeader*)sections;
            while (remaining > 0) {
                if (section->tag == SCORE_SECTION_RECORDS) {
                    if (section->version == 0) {
                        unsigned int sum = 0;
                        unsigned char* bytes = (unsigned char*)section;
                        for (int i = 8; i < sizeof(ScoreRecordSection); i++)
                            sum += bytes[i];
                        if (sum == section->checksum && section->size == sizeof(ScoreRecordSection))
                            memcpy(&records[((ScoreRecordSection*)section)->shot_type], section, sizeof(ScoreRecordSection));
                    }
                } else if (section->tag == SCORE_SECTION_SETTINGS) {
                    if (section->version == 0) {
                        unsigned int sum = 0;
                        unsigned char* bytes = (unsigned char*)section;
                        for (int i = 8; i < sizeof(ScoreSettingsSection); i++)
                            sum += bytes[i];
                        if (sum == section->checksum && section->size == sizeof(ScoreSettingsSection))
                            memcpy(&settings, section, sizeof(ScoreSettingsSection));
                    }
                } else {
                    goto invalid;
                }
                remaining -= section->size;
                if (remaining < 0)
                    goto invalid;
                section = (ScoreSectionHeader*)((unsigned char*)section + section->size);
            }
            return 0;
        }
invalid:
        if (file) {
            asm_free_00452422(file);
            file = 0;
        }
    }
    file = (ScoreFileHeader*)asm_malloc_00452706(sizeof(ScoreFileHeader));
    memset(file, 0, sizeof(ScoreFileHeader));
    file->magic = SCORE_FILE_MAGIC;
    file->version = 3;
    file->flags = 0x100;
    return 0;
}
#pragma code_seg()
