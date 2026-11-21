// 0x00403850: cache and copy an ECL file, load its animation, relocate tables.
#include <string.h>
#include <stdlib.h>
#include "th10/platform/archive_file.hpp"
#include "th10/game/background.hpp"
#include "th10/platform/text_log.hpp"
extern "C" {
extern char g_archive_load_path[];

void* __cdecl malloc(unsigned int);
void* __fastcall LoadCachedResource(int slot, void* manager, const char* name);
}
#pragma code_seg(".text$03stage")
int BackGround::Load(const char* name) {
    if (!original) {
        g_archive_load_path[0] = 0;
        strcat(g_archive_load_path, name);
        original = Archive_LoadFile(g_archive_load_path, &file_size, 0);
        if (!original) return -1;
    }
    // Reuse the size temporary for both allocations (retail LTCG register shape).
    int allocation_size = file_size;
    file = (BackGroundFile*)malloc(allocation_size);
    memcpy(file, original, file_size);
    animation = LoadCachedResource((stage_flags & 1) + 4, g_sprt_ctrl,
                                           file->animation_name);
    if (!animation) {
        ((TextLog*)0x474F70)->Append((char*)0x46CBC0);
        return -1;
    }
    BackGroundFile* data = file;
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
