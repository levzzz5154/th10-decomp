// 0x4350D0: complete native C++ packed-index parser, including its actual
// array construction EH. The real Version -> Open -> LoadIndex caller graph
// establishes all three stack inputs and RET12. No register adapter is used.
#include <string.h>
#include "../../../build_support/layout/ltcg/native_archive_index/parser.hpp"
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
#pragma code_seg(".text$a18ctor")
ArchiveEntry::ArchiveEntry(): name(0) {}
#pragma code_seg(".text$a16release")
ArchiveEntry::~ArchiveEntry() {
    if(name) { asm_free_00452422(name); name=0; }
}
#pragma code_seg()
inline int NameBytes(const char* name) {
    return int(strlen(name))+1;
}
inline void CopyName(char* out,const char* in) {
    while((*out++=*in++)!=0) {}
}
#pragma code_seg(".text$a12parser")
__declspec(noinline) DatArchiveEntry* __stdcall BuildIndex(const unsigned char* packed,int count,unsigned int terminal) {
    ArchiveEntry* entries=new ArchiveEntry[unsigned(count)+1];
    if(!entries) return 0;
    const unsigned char* cursor=packed;
    ArchiveEntry* entry=entries;
    for(int remaining=count;remaining>0;--remaining,++entry) {
        const char* name=(const char*)cursor;
        char* copy=(char*)asm_malloc_00452706(NameBytes(name));
        if(copy) CopyName(copy,name);
        entry->name=copy;
        int bytes=NameBytes(name);
        int rest=bytes%4;
        if(rest) bytes+=4-rest;
        cursor+=bytes;
        entry->offset=*(const unsigned int*)cursor; cursor+=4;
        entry->size=*(const unsigned int*)cursor; cursor+=4;
        entry->metadata=*(const unsigned int*)cursor; cursor+=4;
    }
    entries[count].offset=terminal;
    entries[count].size=0;
    return reinterpret_cast<DatArchiveEntry*>(entries);
}
#pragma code_seg()
