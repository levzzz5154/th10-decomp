#pragma once
#include "th10/archive/dat_archive_types.hpp"
#include <string.h>
struct DatCryptParameters {
    unsigned char key, step;
    int block_size, byte_limit;
};
extern "C" DatCryptParameters g_dat_read_crypt_parameters[8];
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
extern "C" int __cdecl asm_stricmp_0046054e(const char*, const char*);
extern "C" __declspec(noinline) DatArchiveEntry* __stdcall ArchiveFind(DatArchive*,const char*);
extern "C" __declspec(noinline) unsigned char* __stdcall DatArchiveRead(DatArchive*,const char*,unsigned char*);
extern "C" __declspec(noinline) unsigned char* __stdcall DatDecrypt(unsigned char*,int,unsigned char,unsigned char,int,int);
extern "C" unsigned char* __stdcall DecompressDatLzss2(const unsigned char*,int,unsigned char*,unsigned int);
