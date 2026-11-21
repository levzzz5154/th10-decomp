#pragma once
#include "th10/archive/dat_archive_types.hpp"
#include <string.h>
struct DatCryptParameters {
    unsigned char key, step;
    int block_size, byte_limit;
};
extern "C" DatCryptParameters g_dat_read_crypt_parameters[8];
extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" int __cdecl crt_stricmp(const char*, const char*);
extern "C" __declspec(noinline) DatArchiveEntry* __stdcall ArchiveFind(DatArchive*,const char*);
extern "C" __declspec(noinline) unsigned char* __stdcall DatArchiveRead(DatArchive*,const char*,unsigned char*);
extern "C" __declspec(noinline) unsigned char* __stdcall DatDecrypt(unsigned char*,int,unsigned char,unsigned char,int,int);
extern "C" unsigned char* __stdcall DecompressDatLzss2(const unsigned char*,int,unsigned char*,unsigned int);
