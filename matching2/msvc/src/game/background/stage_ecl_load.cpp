// 0x00403850: cache and copy an ECL file, load its animation, relocate tables.
#include <string.h>
#include <stdlib.h>
#include "th10/platform/archive_file.hpp"
#include "th10/platform/stage_ecl_load_00403850.hpp"
struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};
extern "C" {
extern char data_00497c38[];
extern void* data_00491c10;
void* __cdecl malloc(unsigned int);
void* __fastcall LoadCachedResource_00447280(int slot, void* manager, const char* name);
}
#pragma code_seg(".text$00stage")
int StageEclLoader_00403850::Load(const char* name) {
    if (!original) {
        data_00497c38[0] = 0;
        strcat(data_00497c38, name);
        original = Archive_LoadFile(data_00497c38, &file_size, 0);
        if (!original) return -1;
    }
    // Reuse the size temporary for both allocations (retail LTCG register shape).
    int allocation_size = file_size;
    file = (StageEclFile_00403850*)malloc(allocation_size);
    memcpy(file, original, file_size);
    animation = LoadCachedResource_00447280((flags & 1) + 4, data_00491c10,
                                           file->animation_name);
    if (!animation) {
        ((TextLog_0044b810*)0x474F70)->Append((char*)0x46CBC0);
        return -1;
    }
    StageEclFile_00403850* data = file;
    subroutines = data->sub_offsets;
    timeline = (char*)data + data->timeline_offset;
    auxiliary = (char*)data + data->auxiliary_offset;
    for (int i = 0; i < file->sub_count; ++i)
        subroutines[i] += (unsigned int)file;
    allocation_size = file->instance_count;
    allocation_size *= 0x3AC;
    instances = malloc(allocation_size);
    return 0;
}
#pragma code_seg()
