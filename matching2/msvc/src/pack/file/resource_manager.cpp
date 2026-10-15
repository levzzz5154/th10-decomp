#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"
// Resource loading is owned by resource_load_00435800.cpp.

#include <string.h>

// 0x004356F0: find the packed-archive entry whose stored name matches the name
// this string object holds, with everything from the first '/' on replaced by
// the five-byte marker at 0x0046F274. The helper at 0x00452730 finds the first
// matching byte; nested suffixes belong to the selected archive's entry name.

struct ArchiveEntry_004356f0 {
    unsigned int field_00;   // +0x00
    unsigned int field_04;   // +0x04
    const char* name;        // +0x08
    unsigned int field_0C;   // +0x0C
};

extern "C" ArchiveEntry_004356f0 g_archive_entries[];

struct ArchiveName_004356f0 {
    char text[1];

    __declspec(noinline) const ArchiveEntry_004356f0* Find() const;
};

#pragma code_seg(".text$01find")
const ArchiveEntry_004356f0* ArchiveName_004356f0::Find() const {
    char buffer[0x104];
    const char* name = text;
    const char* slash = ((char* (__cdecl*)(const char*, int))asm_FUN_00452730_00452730)(name, '/');
    const char* base = slash ? slash + 1 : name;
    int length = (int)(base - name) - 1;
    strcpy(buffer, name);
    if (length >= 0) {
        char* suffix = buffer + length;
        *(unsigned int*)suffix = *(unsigned int*)&g_resource_dat_suffix;
        suffix[4] = (char)*(unsigned char*)&g_resource_dat_last_char;
    }
    ArchiveEntry_004356f0* entry = g_archive_entries;
    for (int index = 0; index < *(int*)&g_archive_entry_count; index++, entry++) {
        if (strcmp(entry->name, buffer) == 0)
            return entry;
    }
    return 0;
}
#pragma code_seg()
