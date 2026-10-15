#pragma once
#include "th10/archive/dat_archive_types.hpp"
void* __cdecl operator new(unsigned int);
void* __cdecl operator new[](unsigned int);
void __cdecl operator delete(void*);
void __cdecl operator delete[](void*);
struct ArchiveEntry {
    char* name;
    unsigned int offset,size,metadata;
    __declspec(noinline) ArchiveEntry();
    __declspec(noinline) ~ArchiveEntry();
};
DatArchiveEntry* __stdcall BuildIndex(const unsigned char*,int,unsigned int);
